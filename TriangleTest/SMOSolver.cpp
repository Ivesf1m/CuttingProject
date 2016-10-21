#include "SMOSolver.h"
#include <algorithm>
#include <cmath>
#include <utility>

SMOSolver::SMOSolver(int numberOfElements, Kernel* kernel, const
	vector<double>& p, const vector<char>& signs, 
	double cp, double cn, double stopCondition)
	: numberOfElements(numberOfElements), kernel(kernel), p(p),
	signs(signs), cp(cp), cn(cn), stopCondition(stopCondition),
	expand(false)
{
	alpha.reserve(numberOfElements);
	alphaStatus.reserve(numberOfElements);
	activeSet.reserve(numberOfElements);
	gradient.reserve(numberOfElements);
	freeGradient.reserve(numberOfElements);
	activeSize = numberOfElements;
	for (int i = 0; i < numberOfElements; ++i) {
		alpha[i] = 0.0;
		updateAlphaStatus(i);
		activeSet[i] = i;
		gradient[i] = p[i];
		freeGradient[i] = 0;
	}

	for (int i = 0; i < numberOfElements; ++i) {
		if (!isLowerBound(i)) {
			vector<float> column;
			kernel->getColumn(numberOfElements, i, column);
			double regPar = getRegularizationParameter(i);
			for (int j = 0; j < numberOfElements; ++j) {
				gradient[j] += alpha[i] * column[j];
				if (isUpperBound(i))
					freeGradient[j] =  regPar * column[j];
			}			
		}
	}
}


SMOSolver::~SMOSolver()
{
}

double SMOSolver::calculateRho()
{
	double upperBound = HUGE_VAL;
	double lowerBound = -HUGE_VAL;
	double totalFree = 0.0;
	int numberOfFrees = 0;
	for (int i = 0; i < activeSize; ++i) {
		double signedGradient = signs[i] * gradient[i];
		if (isUpperBound(i)) {
			if (signs[i] == -1)
				upperBound = std::min(upperBound, signedGradient);
			else
				lowerBound = std::max(lowerBound, signedGradient);
		}
		else if (isLowerBound(i)) {
			if (signs[i] == 1)
				upperBound = std::min(upperBound, signedGradient);
			else
				lowerBound = std::max(lowerBound, signedGradient);
		}
		else {
			++numberOfFrees;
			totalFree += signedGradient;
		}
	}

	if (numberOfFrees)
		return totalFree / numberOfFrees;
	else
		return (upperBound + lowerBound) / 2.0;
}

vector<double>& SMOSolver::getAlpha()
{
	return alpha;
}

double SMOSolver::getNegativeUpperBound()
{
	return negativeUpperBound;
}

double SMOSolver::getPositiveUpperBound()
{
	return positiveUpperBound;
}

double SMOSolver::getRegularizationParameter(int index)
{
	if (signs[index] > 0)
		return cp;
	return cn;
}

double SMOSolver::getRho()
{
	return rho;
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
			kernel->getColumn(activeSize, i, column);
			for (int j = 0; j < activeSize; ++j)
				if (isFree(j))
					gradient[j] += alpha[j] * column[j];
		}
	}
	else {
		for(int i = 0; i < activeSize; ++i)
			if (isFree(i)) {
				vector<float> column;
				kernel->getColumn(numberOfElements, i, column);
				for (int j = activeSize; j < numberOfElements; ++j)
					gradient[j] += alpha[i] * column[j];
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
		if (signs[i] == 1){
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
		kernel->getColumn(activeSize, gmaxIndex, column);
	double tau = 1e-12;

	for (int i = 0; i < activeSize; ++i) {
		double objectDifference;
		if (signs[i] == 1) {
			if (!isLowerBound(i)) {
				double gradientDifference = gmax + gradient[i];
				if (gradient[i] >= gmax2)
					gmax2 = gradient[i];
				if (gradientDifference > 0) {					
					double quadraticCoef = kernelD[i] + kernelD[gmaxIndex] -
						2.0 * signs[gmaxIndex] * column[i];
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
						2.0 * signs[gmaxIndex] * column[i];
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

	if (gmax + gmax2 < stopCondition || gminIndex == -1)
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
		if (signs[i] == 1) {
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

	if (!expand && (gmax1 + gmax2 <= stopCondition * 10)) {
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
		if (signs[index] == 1)
			return (-gradient[index] > gmax1);
		else
			return (-gradient[index] > gmax2);
	}
	else if (isLowerBound(index)) {
		if (signs[index] == 1)
			return (-gradient[index] > gmax2);
		else
			return (-gradient[index] > gmax1);
	}
	else return false;
}

void SMOSolver::solve(bool shrinking)
{
	long i = 0;
	long i_max = std::max(static_cast<long>(1e7), 100L * 
		static_cast<long>(numberOfElements));
	int count = std::min(numberOfElements, 1000) + 1;
	while (i < i_max) {
		if (--count == 0) {
			count = std::min(numberOfElements, 1000);
			if (shrinking) shrink();
		}

		int index1, index2;
		if (selectWorkingSet(index1, index2)) {
			reconstructGradient();
			activeSize = numberOfElements;
			if (selectWorkingSet(index1, index2))
				break;
			else
				count = 1;
		}

		++i;

		vector<float> index1Column, index2Column;
		kernel->getColumn(activeSize, index1, index1Column);
		kernel->getColumn(activeSize, index2, index2Column);

		double index1RegPar, index2RegPar;
		index1RegPar = getRegularizationParameter(index1);
		index2RegPar = getRegularizationParameter(index2);

		double index1PreviousAlpha, index2PreviousAlpha;
		index1PreviousAlpha = alpha[index1];
		index2PreviousAlpha = alpha[index2];

		double quadraticCoef = kernelD[index1] + kernelD[index2];
		double delta;

		if (signs[index1] != signs[index2]) {
			quadraticCoef += 2 * index1Column[index2];
			if (quadraticCoef < 0.0)
				quadraticCoef = 1e-12;
			delta = (-gradient[index1] - gradient[index2]) / 
				quadraticCoef;
			double difference = alpha[index1] - alpha[index2];
			alpha[index1] += delta;
			alpha[index2] += delta;

			if (difference > 0 && alpha[index2] < 0.0) {
				alpha[index1] = difference;
				alpha[index2] = 0.0;				
			}
			else if (difference <= 0 && alpha[index1] < 0.0) {
				alpha[index1] = 0.0;
				alpha[index2] = -difference;
			}

			double cdiff = index1RegPar - index2RegPar;

			if ((difference > cdiff) &&
				(alpha[index1] > index1RegPar)) {
				alpha[index1] = index1RegPar;
				alpha[index2] = index1RegPar - difference;
			}
			else if ((difference <= cdiff) &&
				(alpha[index2] > index2RegPar)) {
				alpha[index1] = index2RegPar + difference;
				alpha[index2] = index2RegPar;
			}
		}
		else {
			quadraticCoef -= 2 * index1Column[index2];
			if (quadraticCoef < 0)
				quadraticCoef = 1e-12;
			delta = (gradient[index1] - gradient[index2]) / quadraticCoef;
			double sum = alpha[index1] + alpha[index2];
			alpha[index1] -= delta;
			alpha[index2] += delta;
			if (sum > index1RegPar && alpha[index1] > index1RegPar) {
				alpha[index1] = index1RegPar;
				alpha[index2] = sum - index1RegPar;
			}
			else if (sum <= index1RegPar && alpha[index2] < 0.0) {
				alpha[index1] = sum;
				alpha[index2] = 0.0;
			}

			if (sum > index2RegPar && alpha[index2] > index2RegPar) {
				alpha[index1] = sum - index2RegPar;
				alpha[index2] = index2RegPar;
			}
			else if (sum <= index2RegPar && alpha[index1] < 0.0) {
				alpha[index1] = 0.0;
				alpha[index2] = sum;
			}
		}

		double index1AlphaDiff = alpha[index1] - index1PreviousAlpha;
		double index2AlphaDiff = alpha[index2] - index2PreviousAlpha;
		for (int j = 0; j < activeSize; ++j)
			gradient[j] = index1Column[j] * index1AlphaDiff +
			index2Column[j] * index2AlphaDiff;

		bool index1UpperBound = isUpperBound(index1);
		bool index2UpperBound = isUpperBound(index2);
		updateAlphaStatus(index1);
		updateAlphaStatus(index2);
		if (index1UpperBound != isUpperBound(index1)) {
			vector<float> column;
			kernel->getColumn(numberOfElements, index1, column);
			if (index1UpperBound)
				for (int j = 0; j < numberOfElements; ++j)
					freeGradient[j] -= index1RegPar * column[j];
			else
				for (int j = 0; j < numberOfElements; ++j)
					freeGradient[j] += index1RegPar * column[j];
		}

		if (index2UpperBound != isUpperBound(index2)) {
			vector<float> column;
			kernel->getColumn(numberOfElements, index2, column);
			if (index2UpperBound)
				for (int j = 0; j < numberOfElements; ++j)
					freeGradient[j] -= index2RegPar * column[j];
			else
				for (int j = 0; j < numberOfElements; ++j)
					freeGradient[j] += index2RegPar * column[j];
		}
	}

	if (i >= i_max && activeSize < numberOfElements) {
		reconstructGradient();
		activeSize = numberOfElements;
	}

	rho = calculateRho();
	double value = 0;
	for (int i = 0; i < numberOfElements; ++i)
		value += alpha[i] * (gradient[i] + p[i]);
	objectiveValue = value / 2.0;

	positiveUpperBound = cp;
	negativeUpperBound = cn;
}

void SMOSolver::swapIndex(int index1, int index2)
{
	std::swap(signs[index1], signs[index2]);
	std::swap(gradient[index1], gradient[index2]);
	std::swap(alphaStatus[index1], alphaStatus[index2]);
	std::swap(alpha[index1], alpha[index2]);
	std::swap(p[index1], p[index2]);
	std::swap(activeSet[index1], activeSet[index2]);
	std::swap(freeGradient[index1], freeGradient[index2]);
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
