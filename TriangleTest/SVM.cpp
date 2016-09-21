#include "SVM.h"



SVM::SVM(int numberOfClasses, double cacheSize, double stopCondition, 
	bool shrinking, bool probability, Kernel* kernel)
	: numberOfClasses(numberOfClasses), cacheSize(cacheSize), 
	  stopCondition(stopCondition), shrinking(shrinking), 
	  probability(probability), kernel(kernel)
{

}


SVM::~SVM()
{
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

bool SVM::isShrinking()
{
	return shrinking;
}

void SVM::setShrinking(bool shrinking)
{
	this->shrinking = shrinking;
}