#include "SVMCache.h"

SVMCache::SVMCache(int numberOfObjects, unsigned int size)
	: numberOfObjects(numberOfObjects), size(size), current(0)
{
	data.reserve(numberOfObjects);
}


SVMCache::~SVMCache()
{
}

void  SVMCache::insert(const vector<float>& newData)
{
	if (current == data.size())
		return;
	data[current] = newData;
	++current;
}

void SVMCache::remove(unsigned int index)
{
	if (index >= current)
		return;

	data.erase(data.begin() + index);
	current = (current == 0) ? 0 : current - 1;
}
