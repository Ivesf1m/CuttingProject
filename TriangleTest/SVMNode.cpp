#include "SVMNode.h"

SVMNode::SVMNode(int index, double value)
	: index(index), value(value)
{
}


SVMNode::~SVMNode()
{
}

int SVMNode::getIndex() const
{
	return index;
}

void SVMNode::setIndex(int index)
{
	this->index = index;
}

double SVMNode::getValue() const
{
	return value;
}

void SVMNode::setValue(double value)
{
	this->value = value;
}
