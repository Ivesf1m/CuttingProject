#pragma once

//Support Vector Machine Node.

class SVMNode
{
public:
	SVMNode(int index, double value);
	~SVMNode();

	//Getters and setters
	int getIndex() const;
	void setIndex(int index);

	double getValue() const;
	void setValue(double value);

private:
	int index;
	double value;
};

