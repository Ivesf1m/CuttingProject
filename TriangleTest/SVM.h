#pragma once
//Superclass for Support Vector Machine (SVM)
//This project will only use SVM for classification.

#include <vector>
#include "Kernel.h"

using std::vector;

class SVM
{
public:
	SVM(int numberOfClasses = 0, double cacheSize = 0,
		double stopCondition = 0, bool shrinking = false,
		bool probability = false, Kernel* kernel = NULL);
	~SVM();

	virtual void crossValidate(int numberOfFolds) = 0;
	virtual void train() = 0;

	//Getters and Setters
	double getCacheSize();
	void setCacheSize(double size);

	const Kernel* getKernel();
	void setKernel(Kernel* kernel);

	int getNumberOfClasses();
	void setNumberOfClasses(int numberOfClasses);

	double getStopCondition();
	void setStopCondition(double condition);

	bool isProbability();
	void setProbability(bool probability);

	bool isShrinking();
	void setShrinking(bool shrinking);

private:
	vector<SupportVector> supportVectors;
	Kernel* kernel;
	int numberOfClasses;
	vector<int> classLabels;
	double cacheSize;
	double stopCondition;
	bool shrinking;
	bool probability;
};

