#pragma once
#include "SVMNode.h"
#include <vector>

using std::vector;

typedef vector<SVMNode> SupportVector;
typedef vector< vector<float> > Cache;

//Abstract class for svm kernels.
class Kernel
{
public:
	Kernel(int cacheSize, int numberOfVectors);
	~Kernel();

	//Every svm kernel must implement its function.
	virtual float kernelFunction(int i, int j) = 0;

	//Some matricial functions tat mut be implemented by subclasses
	void getColumn(int size, int columnIndex, vector<float>& column);

	void swapIndices(int index1, int index2);

	//Cache functions
	vector<float> deleteFromCache(unsigned int index);
	int getCacheData(vector<float>& data, int index, int size);
	void insertInCache(const vector<float>& data);

protected:
	double nodeDot(const SupportVector& v1, const SupportVector& v2);

	SVMNode** nodes;
	double* squaredNodes;
	vector<char> signs;
	vector<double> kernelD;

	Cache cacheData;
	int currentCacheIndex;
};

