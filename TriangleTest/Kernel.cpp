#include "Kernel.h"

Kernel::Kernel()
{
}


Kernel::~Kernel()
{
}

double Kernel::nodeDot(const SupportVector& v1, const SupportVector& v2)
{
	double result = 0.0;
	size_t vecSize = v1.size() > v2.size() ? v2.size() : v1.size();
	for (size_t i = 0; i < vecSize; ++i)
		result += v1[i].getValue() * v2[i].getValue();
	return result;
}
