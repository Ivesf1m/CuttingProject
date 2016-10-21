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
		double regParameter = 0.0, int numberOfWeights = 0,
		Kernel* kernel = NULL);
	~SVM();

	void crossValidate(int numberOfElements, double* values, SupportVector* nodes,
		int numberOfFolds, vector<double>& output);
	double predict(int numberOfElements, SupportVector& sv);
	void solve(int numberOfElements, double* values, double& cp, double& cn,
		vector<double>& alpha, double& rho);
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

	bool isShrinking();
	void setShrinking(bool shrinking);

	vector<double>& getWeights();
	void setWeights(const vector<double>& weights);

	vector<int>& getWeightLabels();
	void setWeights(const vector<int>& weightLabels);

private:
	vector<SupportVector> supportVectors;
	vector< vector<double> > supportVectorCoefs;
	vector<double> rho;
	vector<int> trainingSetIndices;
	int numberOfClasses;
	vector<int> classLabels;
	vector<int> svPerClass;
	Kernel* kernel;
	double cacheSize;
	int numberOfWeights;
	vector<int> weightLabels;
	vector<double> weights;
	double regularizationParameter;
	double stopCondition;
	bool shrinking;

	void groupClasses(int numberOfElements, double* values, vector<int>&
		startVector, vector<int>& classCount, vector<int>& originalIndices);
	double predictValues(int numberOfElements, SupportVector& sv, 
		vector<double>& predictedValues);
	void train(int numberOfElements, double* values, double cp, double cn,
		vector<double>& alphas, double& rho);

};

