#include "SMOSolver.h"
#include <cmath>
#include <utility>

SMOSolver::SMOSolver()
{
}


SMOSolver::~SMOSolver()
{
}

double SMOSolver::getRegularizationParameter(int index)
{
	if (y[index] > 0)
		return cp;
	return cn;
}

bool SMOSolver::isFree(int index)
{
	return (alphaStatus[index] == SolverStatus::FREE);
}

bool SMOSolver::isLowerBound(int index)
{
	return (alphaStatus[index] == SolverStatus::LOWER_BOUND);
}

bool SMOSolver::isUpperBound(int index)
{
	return (alphaStatus[index] == SolverStatus::UPPER_BOUND);
}

void SMOSolver::reconstructGradient()
{
	int numberofFrees = 0;

	if (activeSize == numberOfElements)
		return;

	for (int i = activeSize; i < numberOfElements; ++i)
		gradient[i] = freeGradient[i] + p[i];

	for (int i = 0; i < activeSize; ++i)
		if (isFree(i))
			++numberofFrees;

	long int freeTimesTotal = numberofFrees * numberOfElements;
	long int activeTimesInnactive = 2 * activeSize * (numberOfElements -
		activeSize);

	if (freeTimesTotal > activeTimesInnactive) {
		for (int i = activeSize; i < numberOfElements; ++i) {
			vector<float> column;
			kernel->getColumn(i, column);
			for (int j = 0; j < activeSize; ++j)
				if (isFree(j))
					gradient[j] += alpha[j] * column[j];
		}
	}
	else {
		for(int i = 0; i < activeSize; ++i)
			if (isFree(i)) {
				vector<float> column;
				kernel->getColumn(i, column);
				for (int j = activeSize; j < numberOfElements; ++j)
					gradient[j] = alpha[i] * column[j];
			}
	}

}

int SMOSolver::selectWorkingSet(int& index1, int& index2)
{
	double gmax = -HUGE_VAL; //maximum gradient
	double gmax2 = -HUGE_VAL;
	int gmaxIndex = -1;
	int gminIndex = -1;
	double minObjDifference = HUGE_VAL;

	//Finding the maximum gradient
	for (int i = 0; i < activeSize; ++i) {
		if (y[i] == 1){
			if ((!isUpperBound(i)) && (-gradient[i] >= gmax)) {
				gmax = -gradient[i];
				gmaxIndex = i;
			}
		}
		else {
			if ((!isLowerBound(i)) && (gradient[i] >= gmax)) {
				gmax = gradient[i];
				gmaxIndex = i;
			}
		}
	}

	vector<float> column;
	if (gmaxIndex != -1)
		kernel->getColumn(gmaxIndex, column);
	double tau = 1e-12;

	for (int i = 0; i < activeSize; ++i) {
		double objectDifference;
		if (y[i] == 1) {
			if (!isLowerBound(i)) {
				double gradientDifference = gmax + gradient[i];
				if (gradient[i] >= gmax2)
					gmax2 = gradient[i];
				if (gradientDifference > 0) {					
					double quadraticCoef = kernelD[i] + kernelD[gmaxIndex] -
						2.0 * y[gmaxIndex] * column[i];
					double squaredGradDiff = gradientDifference * 
						gradientDifference;
					if (quadraticCoef > 0)
						objectDifference = -squaredGradDiff / quadraticCoef;
					else
						objectDifference = -squaredGradDiff / tau;

					if (objectDifference < minObjDifference) {
						gminIndex = i;
						minObjDifference = objectDifference;
					}
				}
			}
		}
		else {
			if (!isUpperBound(i)) {
				double gradientDifference = gmax - gradient[i];
				if (-gradient[i] >= gmax2)
					gmax2 = -gradient[i];
				if (gradientDifference > 0) {
					double quadraticCoef = kernelD[i] + kernelD[gmaxIndex] -
						2.0 * y[gmaxIndex] * column[i];
					double squaredGradDiff = gradientDifference *
						gradientDifference;
					if (quadraticCoef > 0)
						objectDifference = -squaredGradDiff / quadraticCoef;
					else
						objectDifference = -squaredGradDiff / tau;

					if (objectDifference < minObjDifference) {
						gminIndex = i;
						minObjDifference = objectDifference;
					}
				}
			}
		}
	}

	if (gmax + gmax2 < eps || gminIndex == -1)
		return 1; //ideal case

	index1 = gmaxIndex;
	index2 = gminIndex;
	return 0;
}

void SMOSolver::shrink()
{
	double gmax1 = -HUGE_VAL;
	double gmax2 = -HUGE_VAL;

	for (int i = 0; i < activeSize; ++i) {
		if (y[i] == 1) {
			if (!isUpperBound(i) && (-gradient[i] >= gmax1))
				gmax1 = -gradient[i];

			if (!isLowerBound(i) && (gradient[i] >= gmax2))
				gmax2 = gradient[i];
		}
		else {
			if (!isUpperBound(i) && (-gradient[i] >= gmax2))
				gmax2 = -gradient[i];

			if (!isLowerBound(i) && (gradient[i] >= gmax1))
				gmax1 = gradient[i];
		}
	}

	if (!expand && (gmax1 + gmax2 <= eps * 10)) {
		expand = true;
		reconstructGradient();
		activeSize = numberOfElements;
	}

	for (int i = 0; i < activeSize; ++i) {
		if (shrinkFunction(i, gmax1, gmax2)) {
			--activeSize;
			while (activeSize > i) {
				if (!shrinkFunction(activeSize, gmax1, gmax2)) {
					swapIndex(i, activeSize);
					break;
				}
				--activeSize;
			}
		}
	}

}

bool SMOSolver::shrinkFunction(int index, double gmax1, double gmax2)
{
	if (isUpperBound(index)) {
		if (y[index] == 1)
			return (-gradient[index] > gmax1);
		else
			return (-gradient[index] > gmax2);
	}
	else if (isLowerBound(index)) {
		if (y[index] == 1)
			return (-gradient[index] > gmax2);
		else
			return (-gradient[index] > gmax1);
	}
	else return false;
}

void SMOSolver::swapIndex(int index1, int index2)
{
	std::swap(y[index1], y[index2]);
	std::swap(gradient[index1], gradient[index2]);
	//TERMINAR
}

void SMOSolver::updateAlphaStatus(int index)
{
	if (alpha[index] >= getRegularizationParameter(index))
		alphaStatus[index] = SolverStatus::UPPER_BOUND;
	else if (alpha[index] <= 0)
		alphaStatus[index] = SolverStatus::LOWER_BOUND;
	else
		alphaStatus[index] = SolverStatus::FREE;
}
