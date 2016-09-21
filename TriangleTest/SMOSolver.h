#pragma once

#include "Kernel.h"
#include <vector>

using std::vector;

class SMOSolver
{
public:
	SMOSolver();
	~SMOSolver();

protected:
	//Solution variables
	double object;
	double rho;
	double upperBound;

	//Calculation variables
	enum SolverStatus {
		LOWER_BOUND,
		UPPER_BOUND,
		FREE
	};

	int activeSize;
	vector<char> y;
	vector<double> gradient;
	vector<SolverStatus> alphaStatus;
	vector<double> alpha;
	const Kernel* kernel;
	vector<double> kernelD;
	double eps;
	double cp; //positive regularization parameter
	double cn; //negative regularization parameter
	vector<double> p;
	vector<int> activeSet;
	vector<double> freeGradient;
	int numberOfElements;
	bool expand; //undo shrinking

	//Helper functions
	virtual double calculateRho();
	double getRegularizationParameter(int index);
	bool isFree(int index);
	bool isLowerBound(int index);
	bool isUpperBound(int index);
	void reconstructGradient();
	virtual int selectWorkingSet(int& index1, int& index2);
	virtual void shrink();
	void swapIndex(int index1, int index2);
	void updateAlphaStatus(int index);

private:
	bool shrinkFunction(int index, double gmax1, double gmax2);

};

