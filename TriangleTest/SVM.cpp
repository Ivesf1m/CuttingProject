#include "SVM.h"
#include <iostream>

using std::cout;
using std::endl;

SVM::SVM(int numberOfClasses, double cacheSize, double stopCondition, 
	bool shrinking, bool probability, double regParameters, int numberOfWeights, 
	Kernel* kernel)
	: numberOfClasses(numberOfClasses), cacheSize(cacheSize), 
	  stopCondition(stopCondition), shrinking(shrinking), 
	  probability(probability), regularizationParameter(regParameters), 
	  numberOfWeights(numberOfWeights), kernel(kernel)
{

}


SVM::~SVM()
{
}

void SVM::solve(int numberOfElements, double* values, SupportVector* nodes,
	SMOSolver& solver)
{
	vector<char> signs;
	signs.reserve(numberOfElements);
	vector<double>& alpha = solver.getAlpha();

	for (int i = 0; i < numberOfElements; ++i) {
		alpha[i] = 0;
		if (values[i] > 0)
			signs[i] = 1;
		else
			signs[i] = -1;
	}

	solver.solve(shrinking);
	double alphaSum = 0;
	for (int i = 0; i < numberOfElements; ++i) {
		alphaSum += alpha[i];
		alpha[i] *= signs[i];
	}
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

bool SVM::isProbability()
{
	return probability;
}

void SVM::setProbability(bool probability)
{
	this->probability = probability;
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

void SVM::groupClasses(int numberOfElements, double* values, SupportVector* 
	nodes, vector<int>& startVector, vector<int>& classCount, vector<int>&
	originalIndices)
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
			dataLabel[i] = dataLabel[i] == 0 ? 1 : 0;
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
	groupClasses(numberOfElements, values, nodes, startVector, classCount, 
		originalIndices);
	supportVectors.reserve(numberOfElements);
	for (int i = 0; i < numberOfElements; ++i)
		supportVectors[i] = nodes[originalIndices[i]];

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
	vector<double> prob1, prob2;
	/*if (probability) {
		prob1.reserve(numberOfClasses * (numberOfClasses - 1) / 2);
		prob2.reserve(numberOfClasses * (numberOfClasses - 1) / 2);
	}*/

	vector< vector<double> > alphas;
	vector<double> rhos;
	int p = 0;
	for (int i = 0; i < numberOfClasses; ++i) {
		for (int j = i + 1; j < numberOfClasses; ++j) {
			int size;
			double* y;
			SupportVector* svs;
			int istart = startVector[i];
			int jstart = startVector[j];
			int icount = classCount[i];
			int jcount = classCount[j];
			size = icount + jcount;
			svs = new SupportVector[size];
			y = new double[size];

			for (int k = 0; k < icount; ++k) {
				svs[k] = supportVectors[istart + k];
				y[k] = 1;
			}

			for (int k = 0; k < jcount; ++k) {
				svs[istart + k] = supportVectors[jstart + k];
				y[istart + k] = -1;
			}

			//CONTINUAR DEPOIS DO TRAIN ONE
		}
	}
}

void SVM::train(int numberOfElements, double* values, SupportVector* nodes,
	SMOSolver& solver)
{
	solve(numberOfElements, values, nodes, solver);
	int numberOfSupportVectors = 0;
	int numberOfBoundSupportVectors = 0;

	vector<double>& alpha = solver.getAlpha();

	for (int i = 0; i < numberOfElements; ++i) {
		if (alpha[i] != 0) {
			++numberOfSupportVectors;
			if (values[i] > 0 && fabs(alpha[i]) >=
				solver.getPositiveUpperBound())
				++numberOfBoundSupportVectors;
			else if (values[i] <= 0 && fabs(alpha[i]) >=
				solver.getNegativeUpperBound())
				++numberOfBoundSupportVectors;
		}
	}

	cout << "Number of support vectors: " << numberOfSupportVectors << endl;
	cout << "Number of bound support vectors: " << numberOfBoundSupportVectors << endl;
}