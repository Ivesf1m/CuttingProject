#pragma once
//Superclass for Support Vector Machine (SVM)
//This project will only use SVM for classification.

#include <vector>
#include "SMOSolver.h"

using std::vector;

class SVM
{
public:
	SVM(int numberOfClasses = 0, double cacheSize = 0,
		double stopCondition = 0, bool shrinking = false,
		bool probability = false, double regParameters = 0.0,
		int numberOfWeights = 0, Kernel* kernel = NULL);
	~SVM();

	virtual void crossValidate(int numberOfFolds) = 0;
	void solve(int numberOfElements, double* values, SupportVector* nodes,
		SMOSolver& solver);
	void train(int numberOfElements, double* values, SupportVector* nodes);

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

	vector<double>& getWeights();
	void setWeights(const vector<double>& weights);

	vector<int>& getWeightLabels();
	void setWeights(const vector<int>& weightLabels);

private:
	vector<SupportVector> supportVectors;
	Kernel* kernel;
	int numberOfClasses;
	vector<int> classLabels;
	double cacheSize;
	int numberOfWeights;
	vector<int> weightLabels;
	vector<double> weights;
	double regularizationParameter;
	double stopCondition;
	bool shrinking;
	bool probability;

	void groupClasses(int numberOfElements, double* values, SupportVector*
		nodes, vector<int>& startVector, vector<int>& classCount, 
		vector<int>& originalIndices);
	void train(int numberOfElements, double* values, SupportVector* nodes,
		SMOSolver& solver);

};

