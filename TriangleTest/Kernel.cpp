#include "Kernel.h"
#include <utility>

Kernel::Kernel(int cacheSize, int numberOfVectors)
	: currentCacheIndex(0)
{
	cacheData.reserve(cacheSize);
	//for (int i = 0; i < numberOfVectors; ++i)
		//kernelD.push_back(kernelFunction(i, i));
}


Kernel::~Kernel()
{
}

vector<float> Kernel::deleteFromCache(unsigned int index)
{
	if (index > cacheData.size())
		return vector<float>();
	vector<float> cacheCopy = cacheData[index];
	cacheData[index].clear();
	return cacheCopy;
}

int Kernel::getCacheData(vector<float>& data, int index, int size)
{
	if (index > cacheData.size())
		return -1;

	vector<float> aux;
	aux = cacheData[index];
	if (cacheData[index].size())
		aux = deleteFromCache(index);
	int extra = size - static_cast<int>(aux.size());

	if (extra > 0) {
		size = static_cast<int>(aux.size());
	}

	insertInCache(aux);
	data = aux;
	return size;
}

void Kernel::getColumn(int size, int columnIndex, vector<float>& column)
{
	vector<float> data;
	int i, j;
	if ((i = getCacheData(data, columnIndex, size)) < size) {
		for (j = i; j < size; ++j)
			data[j] = signs[i] * signs[j];// *kernelFunction(i, j);
	}
	column = data;
}

void Kernel::insertInCache(const vector<float>& data)
{
	if (currentCacheIndex == cacheData.size()) {
		cacheData.push_back(data);
		++currentCacheIndex;
	}
	else {
		cacheData[currentCacheIndex].clear();
		for (size_t i = 0; i < data.size(); ++i)
			cacheData[currentCacheIndex].push_back(data[i]);
		++currentCacheIndex;
	}
}

double Kernel::nodeDot(const SupportVector& v1, const SupportVector& v2)
{
	double result = 0.0;
	size_t vecSize = v1.size() > v2.size() ? v2.size() : v1.size();
	for (size_t i = 0; i < vecSize; ++i)
		result += v1[i].getValue() * v2[i].getValue();
	return result;
}

void Kernel::swapIndices(int index1, int index2)
{
	std::swap(nodes[index1], nodes[index2]);
	std::swap(squaredNodes[index1], squaredNodes[index2]);
	std::swap(signs[index1], signs[index2]);
	std::swap(kernelD[index1], kernelD[index2]);
}
