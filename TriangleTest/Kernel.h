#pragma once
#include "SVMNode.h"
#include <vector>

using std::vector;

typedef vector<SVMNode> SupportVector;

//Abstract class for svm kernels.
class Kernel
{
public:
	Kernel();
	~Kernel();

	//Every svm kernel must implement its function.
	virtual void kernelFunction() = 0;

	//Some matricial functions tat mut be implemented by subclasses
	virtual void getColumn(int columnIndex, vector<float>& column) const = 0;


protected:
	double nodeDot(const SupportVector& v1, const SupportVector& v2);
};

