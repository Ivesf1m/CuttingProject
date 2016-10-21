#include "Kernel.h"
#include <utility>

Kernel::Kernel(int numberOfVectors)
	: nodes(NULL), signs(NULL), numberOfVectors(numberOfVectors)
{
}


Kernel::~Kernel()
{
}

vector<double>& Kernel::getDiagonal()
{
	return kernelDiagonal;
}

double Kernel::nodeDot(const SupportVector& v1, const SupportVector& v2)
{
	double result = 0.0;
	size_t vecSize = v1.size() > v2.size() ? v2.size() : v1.size();
	for (size_t i = 0; i < vecSize; ++i)
		result += v1[i].getValue() * v2[i].getValue();
	return result;
}

void Kernel::setNodesReference(vector<SupportVector>* nodes)
{
	this->nodes = nodes;
}

void Kernel::setSignsReference(vector<char>* signs)
{
	this->signs = signs;
}

void Kernel::swapIndices(int index1, int index2)
{
	std::swap(nodes->at(index1), nodes->at(index1));
	std::swap(signs->at(index1), signs->at(index1));
	std::swap(kernelDiagonal[index1], kernelDiagonal[index2]);
}
