#pragma once

#include <vector>

using std::vector;

typedef vector< vector<float> > CircularList;

class SVMCache
{
public:
	SVMCache(int numberOfObjects, unsigned int size);
	~SVMCache();

private:
	int numberOfObjects;
	unsigned int size; //maximum cache size in bytes
	CircularList data;
	unsigned int current;

	//Circular list functions
	void insert(const vector<float>& newData);
	void remove(unsigned int index);
};

