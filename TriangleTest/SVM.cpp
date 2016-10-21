#include "SVM.h"
#include <iostream>

using std::cout;
using std::endl;

SVM::SVM(int numberOfClasses, double cacheSize, double stopCondition, 
	bool shrinking, double regParameter, int numberOfWeights, Kernel* kernel)
	: numberOfClasses(numberOfClasses), cacheSize(cacheSize), 
	  stopCondition(stopCondition), shrinking(shrinking), 
	  regularizationParameter(regParameter), 
	  numberOfWeights(numberOfWeights), kernel(kernel)
{

}


SVM::~SVM()
{
}

void SVM::solve(int numberOfElements, double* values, double& cp, double& cn,
	vector<double>& alpha, double& rho)
{
	vector<char> signs(numberOfElements);
	vector<double> minusOnes(numberOfElements, -1.0);

	for (int i = 0; i < numberOfElements; ++i)
		signs[i] = (values[i] > 0) ? 1 : -1;

	SMOSolver solver(numberOfElements, kernel, minusOnes, signs, cp, cn);
	solver.solve(shrinking);
	alpha = solver.getAlpha();

	for (int i = 0; i < numberOfElements; ++i) {
		alpha[i] *= signs[i];
	}

	cp = solver.getPositiveUpperBound();
	cn = solver.getNegativeUpperBound();
	rho = solver.getRho();
}

double SVM::getCacheSize()
{
	return cacheSize;
}

void SVM::setCacheSize(double size)
{
	this->cacheSize = size;
}

const Kernel* SVM::getKernel()
{
	return kernel;
}

void SVM::setKernel(Kernel* kernel)
{
	this->kernel = kernel;
}

int SVM::getNumberOfClasses()
{
	return numberOfClasses;
}

void SVM::setNumberOfClasses(int numberOfClasses)
{
	this->numberOfClasses = numberOfClasses;
}

double SVM::getStopCondition()
{
	return stopCondition;
}

void SVM::setStopCondition(double condition)
{
	this->stopCondition = condition;
}

vector<double>& SVM::getWeights()
{
	return weights;
}

void SVM::setWeights(const vector<double>& weights)
{
	this->weights = weights;
}

vector<int>& SVM::getWeightLabels()
{
	return weightLabels;
}

void SVM::setWeights(const vector<int>& weightLabels)
{
	this->weightLabels = weightLabels;
}

bool SVM::isShrinking()
{
	return shrinking;
}

void SVM::setShrinking(bool shrinking)
{
	this->shrinking = shrinking;
}

void SVM::groupClasses(int numberOfElements, double* values, vector<int>&
	startVector, vector<int>& classCount, vector<int>& originalIndices)
{
	this->numberOfClasses = 0;
	int maxNumberOfClasses = 16;
	classLabels.reserve(maxNumberOfClasses);
	classCount.reserve(maxNumberOfClasses);
	vector<int> dataLabel;
	dataLabel.reserve(numberOfElements);

	for (int i = 0; i < numberOfElements; ++i) {
		int label = static_cast<int>(values[i]);
		int j;
		for (j = 0; j < numberOfClasses; ++j) {
			if (label == classLabels[j]) {
				++classCount[j];
				break;
			}
		}
		dataLabel[i] = j;
		if (j == numberOfClasses) {
			if (numberOfClasses == maxNumberOfClasses) {
				maxNumberOfClasses *= 2;
				classCount.reserve(maxNumberOfClasses);
				classLabels.reserve(maxNumberOfClasses);
			}
		}
		classLabels[numberOfClasses] = label;
		classCount[numberOfClasses] = 1;
		++numberOfClasses;
	}

	if (numberOfClasses == 2 && classLabels[0] == -1 && classLabels[1] == 1) {
		std::swap(classLabels[0], classLabels[1]);
		std::swap(classCount[0], classCount[1]);
		for (int i = 0; i < numberOfElements; ++i)
			dataLabel[i] = (dataLabel[i] == 0) ? 1 : 0;
	}

	startVector.reserve(numberOfClasses);

	startVector[0] = 0;
	for (int i = 1; i < numberOfClasses; ++i)
		startVector[i] = startVector[i - 1] + classCount[i - 1];

	for (int i = 0; i < numberOfElements; ++i) {
		originalIndices[startVector[dataLabel[i]]] = i;
		++startVector[dataLabel[i]];
	}

	startVector[0] = 0;
	for (int i = 1; i < numberOfClasses; ++i)
		startVector[i] = startVector[i - 1] + classCount[i - 1];
}

void SVM::train(int numberOfElements, double* values, SupportVector* nodes)
{
	vector<int> startVector;
	vector<int> classCount;
	vector<int> originalIndices(numberOfElements);
	vector<SupportVector> svsCopy;
	groupClasses(numberOfElements, values, startVector, classCount, 
		originalIndices);
	svsCopy.reserve(numberOfElements);
	for (int i = 0; i < numberOfElements; ++i)
		svsCopy[i] = nodes[originalIndices[i]];

	vector<double> weightedRegPar(numberOfClasses);
	for (int i = 0; i < numberOfClasses; ++i)
		weightedRegPar[i] = regularizationParameter;

	for (int i = 0; i < numberOfWeights; ++i) {
		int j;

		for (j = 0; j < numberOfClasses; ++j)
			if (weightLabels[i] == classLabels[j])
				break;

		if (j != numberOfClasses)
			weightedRegPar[j] *= weights[i];
	}

	vector<bool> nonZero(numberOfElements, false);
	int decisionSize = numberOfClasses * (numberOfClasses - 1) / 2;
	vector< vector<double> > alphas(decisionSize);
	vector<double> rho(decisionSize);
	int p = 0;
	for (int i = 0; i < numberOfClasses; ++i) {
		for (int j = i + 1; j < numberOfClasses; ++j) {
			int size;
			double* indicators;
			SupportVector* svs;
			int istart = startVector[i];
			int jstart = startVector[j];
			int icount = classCount[i];
			int jcount = classCount[j];
			size = icount + jcount;
			svs = new SupportVector[size];
			indicators = new double[size];

			for (int k = 0; k < icount; ++k) {
				svs[k] = svsCopy[istart + k];
				indicators[k] = 1;
			}

			for (int k = 0; k < jcount; ++k) {
				svs[istart + k] = svsCopy[jstart + k];
				indicators[istart + k] = -1;
			}

			train(numberOfElements, values, weightedRegPar[i],
				weightedRegPar[j], alphas[p], rho[p]);

			for (int k = 0; k < icount; ++k)
				if (!nonZero[istart + k] && fabs(alphas[p][k]) > 0)
					nonZero[istart + k] = true;

			for (int k = 0; k < icount; ++k)
				if (!nonZero[jstart + k] && fabs(alphas[p][istart + k]) > 0)
					nonZero[jstart + k] = true;

			++p;
			delete svs;
			delete indicators;
		}
	}

	int numberOfSV = 0;
	vector<int> nonZeroCount(numberOfClasses);
	svPerClass.reserve(numberOfClasses);
	for (int i = 0; i < numberOfClasses; ++i) {
		svPerClass[i] = 0;

		for (int j = 0; j < classCount[i]; ++j) {
			if (nonZero[startVector[i] + j]) {
				svPerClass[i]++;
				++numberOfSV;
			}
		}

		nonZeroCount[i] = svPerClass[i];
	}

	supportVectors.reserve(numberOfSV);
	trainingSetIndices.reserve(numberOfSV);
	p = 0;
	for (int i = 0; i < numberOfElements; ++i) {
		if (nonZero[i]) {
			supportVectors[p] = svsCopy[i];
			trainingSetIndices[p++] = originalIndices[i] + 1;
		}
	}

	vector<int> nonZeroStart(numberOfClasses, 0);
	nonZeroStart[0] = 0;
	for (int i = 1; i < numberOfClasses; ++i)
		nonZeroStart[i] = nonZeroStart[i - 1] + nonZeroCount[i - 1];

	supportVectorCoefs.reserve(numberOfClasses - 1);
	for (int i = 0; i < numberOfClasses - 1; ++i)
		supportVectorCoefs[i].reserve(numberOfSV);

	p = 0;
	for (int i = 0; i < numberOfClasses; ++i) {
		for (int j = i + 1; j < numberOfClasses; ++j) {
			int istart = startVector[i];
			int jstart = startVector[j];
			int icount = classCount[i];
			int jcount = classCount[j];
			int q = nonZeroStart[i];
			for (int k = 0; k < icount; ++k)
				if (nonZero[istart + k])
					supportVectorCoefs[j - 1][q++] = alphas[p][k];
			q = nonZeroStart[j];
			for (int k = 0; k < jcount; ++k)
				if (nonZero[jstart + k])
					supportVectorCoefs[i][q++] = alphas[p][icount + k];
			++p;
		}
	}
}

void SVM::train(int numberOfElements, double* values, double cp, double cn,
	vector<double>& alphas, double& rho)
{
	solve(numberOfElements, values, cp, cn, alphas, rho);
	int numberOfSupportVectors = 0;
	int numberOfBoundSupportVectors = 0;

	for (int i = 0; i < numberOfElements; ++i) {
		if (alphas[i] != 0) {
			++numberOfSupportVectors;
			if (values[i] > 0 && fabs(alphas[i]) >= cp)
				++numberOfBoundSupportVectors;
			else if (values[i] <= 0 && fabs(alphas[i]) >= cn)
				++numberOfBoundSupportVectors;
		}
	}

	cout << "Number of support vectors: " << numberOfSupportVectors << endl;
	cout << "Number of bound support vectors: " << numberOfBoundSupportVectors << endl;
}

void SVM::crossValidate(int numberOfElements, double* values, SupportVector* nodes,
	int numberOfFolds, vector<double>& output)
{
	vector<int> perm(numberOfElements);
	if (numberOfFolds > numberOfElements)
		numberOfFolds = numberOfElements;
	vector<int> foldStart(numberOfFolds + 1);

	if (numberOfFolds < numberOfElements) {
		vector<int> startVector, countVector;
		groupClasses(numberOfElements, values, startVector, countVector, 
			perm);
		vector<int> foldCount(numberOfFolds, 0);
		vector<int> index(numberOfElements);

		for (int i = 0; i < numberOfElements; ++i)
			index[i] = perm[i];

		for (int i = 0; i < numberOfClasses; ++i) {
			for (int j = 0; j < countVector[i]; ++i) {
				int randomIndex = j + rand() % (countVector[i] - j);
				std::swap(index[startVector[i] + randomIndex], 
					index[startVector[i] + j]);
			}
		}

		for (int i = 0; i < numberOfFolds; ++i) {
			for (int j = 0; j < numberOfClasses; ++j) {
				foldCount[i] += (i + 1) * countVector[j] / numberOfFolds - i *
					countVector[j] / numberOfFolds;
			}
		}

		foldStart[0] = 0;
		for (int i = 1; i <= numberOfFolds; ++i)
			foldStart[i] = foldStart[i - 1] + foldCount[i - 1];

		for (int i = 0; i < numberOfClasses; ++i) {
			for (int j = 0; j < numberOfFolds; ++i) {
				int begin = startVector[i] + j * countVector[i] / numberOfFolds;
				int end = startVector[i] + (j + 1) * countVector[i] /
					numberOfFolds;
				for (int k = begin; k < end; ++k) {
					perm[foldStart[j]] = index[k];
					++foldStart[j];
				}
			}
		}

		foldStart[0] = 0;
		for (int i = 1; i <= numberOfFolds; ++i)
			foldStart[i] = foldStart[i - 1] + foldCount[i - 1];
	}
	else {
		for (int i = 0; i < numberOfElements; ++i)
			perm[i] = i;

		for (int i = 0; i < numberOfElements; ++i) {
			int j = i + rand() % (numberOfElements - 1);
			std::swap(perm[i], perm[j]);
		}

		for (int i = 0; i < numberOfFolds; ++i)
			foldStart[i] = i * numberOfElements / numberOfFolds;
	}

	int k;
	for (int i = 0; i < numberOfFolds; ++i) {
		int begin = foldStart[i];
		int end = foldStart[i + 1];

		//Creating a subset of the problem
		int subSize = numberOfElements - (end - begin);
		double* subValues = new double[subSize];
		SupportVector* subVectors = new SupportVector[subSize];

		k = 0;
		for (int j = 0; j < begin; ++j) {
			subVectors[k] = nodes[perm[j]];
			subValues[k] = values[perm[j]];
			++k;
		}

		for (int j = end; j < numberOfElements; ++j) {
			subVectors[k] = nodes[perm[j]];
			subValues[k] = values[perm[j]];
			++k;
		}

		train(subSize, subValues, subVectors);
		for (int j = begin; j < end; ++j)
			output[perm[j]] = predict(subSize, nodes[perm[j]]);
	}
}

double SVM::predict(int numberOfElements, SupportVector& sv)
{
	vector<double> decValues(numberOfClasses * (numberOfClasses - 1) / 2);
	double result = predictValues(numberOfElements, sv, decValues);
	return result;
}

double SVM::predictValues(int numberOfElements, SupportVector& sv, 
	vector<double>& predictedValues)
{
	vector<double> kernelValues(numberOfElements);
	for (int i = 0; i < numberOfElements; ++i)
		kernelValues[i] = kernel->kernelFunction(sv, supportVectors[i]);

	vector<int> startVector(numberOfClasses);
	vector<int> votes(numberOfClasses, 0);
	startVector[0] = 0;
	for (int i = 1; i < numberOfClasses; ++i)
		startVector[i] = startVector[i - 1] * svPerClass[i - 1];

	int l = 0;
	for (int i = 0; i < numberOfClasses; ++i) {
		int istart = startVector[i];
		int icount = svPerClass[i];
		for (int j = i + 1; j < numberOfClasses; ++j) {
			double sum = 0;
			int jstart = startVector[j];
			int jcount = svPerClass[j];

			vector<double>& coef1 = supportVectorCoefs[j - 1];
			vector<double>& coef2 = supportVectorCoefs[i];
			for (int k = 0; k < icount; ++k)
				sum += coef1[istart + k] * kernelValues[istart + k];

			for (int k = 0; k < jcount; ++k)
				sum += coef2[jstart + k] * kernelValues[jstart + k];

			sum -= rho[l];
			predictedValues[l] = sum;
			int predictedClass = (predictedValues[l] > 0) ? i : j;
			++votes[predictedClass];
			++l;
		}
	}

	int mostVotedIndex = 0;
	for (int i = 1; i < numberOfClasses; ++i)
		if (votes[i] > votes[mostVotedIndex])
			mostVotedIndex = i;
	return classLabels[mostVotedIndex];
}