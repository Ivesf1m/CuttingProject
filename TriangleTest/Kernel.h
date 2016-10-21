#pragma once
#include "SVMNode.h"
#include <vector>

using std::vector;

typedef vector<SVMNode> SupportVector;

//Abstract class for svm kernels.
class Kernel
{
public:
	Kernel(int numberOfVectors);
	~Kernel();

	//Every svm kernel must implement its function.
	virtual double kernelFunction(int i, int j) = 0;
	virtual double kernelFunction(SupportVector& x, SupportVector& y) = 0;

	//Mandatory initialization function for the kernelDiagonal,
	//since calling virtual functions from construtor is a no-no
	virtual void calculateDiagonal() = 0;

	virtual void getColumn(int size, int columnIndex, vector<float>& column) = 0;
	vector<double>& getDiagonal();

	void setNodesReference(vector<SupportVector>* nodes);
	void setSignsReference(vector<char>* signs);

	virtual void swapIndices(int index1, int index2);

protected:
	double nodeDot(const SupportVector& v1, const SupportVector& v2);

	vector<SupportVector>* nodes;
	vector<char>* signs;
	vector<double> kernelDiagonal;
	int numberOfVectors;
};

class LinearKernel : public Kernel
{
	public:
		LinearKernel(int numberOfVectors)
			: Kernel(numberOfVectors)
		{
			
		}

		virtual void calculateDiagonal()
		{
			for (int i = 0; i < numberOfVectors; ++i)
				kernelDiagonal.push_back(kernelFunction(i, i));
		}

		virtual double kernelFunction(int i, int j)
		{
			return nodeDot(nodes->at(i), nodes->at(j));
		}

		virtual double kernelFunction(SupportVector& x, SupportVector& y) {
			return nodeDot(x, y);
		}

		virtual void getColumn(int size, int columnIndex, vector<float>& column)
		{
			for (int i = 0; i < size; ++i) {
				column[i] = static_cast<float>(signs->at(columnIndex) * 
					signs->at(i) * kernelFunction(columnIndex, i));
			}
		}
};

class PolynomialKernel : public Kernel
{
	public:
		PolynomialKernel(int numberOfVectors, double gamma, double coef0,
			double degree)
			: Kernel(numberOfVectors), gamma(gamma), coef0(coef0), 
			  degree(degree)
		{

		}

		virtual void calculateDiagonal()
		{
			for (int i = 0; i < numberOfVectors; ++i)
				kernelDiagonal.push_back(kernelFunction(i, i));
		}

		virtual double kernelFunction(int i, int j)
		{
			return kernelFunction(nodes->at(i), nodes->at(j));
		}

		virtual double kernelFunction(SupportVector& x, SupportVector& y) 
		{
			double base = gamma * nodeDot(x, y) + coef0;
			double result = 1.0f;
			for (int t = (int)degree; t > 0; t = t / 2) {
				if (t % 2)
					result *= base;
				base *= base;
			}
			return result;
		}

		virtual void getColumn(int size, int columnIndex, vector<float>& column)
		{
			for (int i = 0; i < size; ++i) {
				column[i] = static_cast<float>(signs->at(columnIndex) *
					signs->at(i) * kernelFunction(columnIndex, i));
			}
		}

	private:
		double gamma;
		double coef0;
		double degree;
};

class RadialBasisKernel : public Kernel
{
	public:
		RadialBasisKernel(int numberOfVectors, double gamma)
			: Kernel(numberOfVectors), gamma(gamma), 
			  squaredValues(numberOfVectors)
		{

		}

		virtual void calculateDiagonal()
		{
			for (int i = 0; i < numberOfVectors; ++i) {
				kernelDiagonal.push_back(kernelFunction(i, i));
				squaredValues[i] = nodeDot(nodes->at(i), nodes->at(i));
			}
		}

		virtual double kernelFunction(int i, int j)
		{
			double exponent = squaredValues[i] + squaredValues[j];
			exponent -= 2 * nodeDot(nodes->at(i), nodes->at(j));
			exponent *= gamma;
			return exp(exponent);
		}

		virtual double kernelFunction(SupportVector& x, SupportVector& y)
		{
			double xsquared = nodeDot(x, x);
			double ysquared = nodeDot(y, y);
			double exponent = xsquared + ysquared;
			exponent -= 2 * nodeDot(x, y);
			exponent *= gamma;
			return exp(exponent);
		}


		virtual void swapIndices(int index1, int index2)
		{
			Kernel::swapIndices(index1, index2);
			std::swap(squaredValues[index1], squaredValues[index1]);
		}

		virtual void getColumn(int size, int columnIndex, vector<float>& column)
		{
			for (int i = 0; i < size; ++i) {
				column[i] = static_cast<float>(signs->at(columnIndex) *
					signs->at(i) * kernelFunction(columnIndex, i));
			}
		}

	private:
		vector<double> squaredValues;
		double gamma;
};

class PukKernel : public Kernel
{
	public:
		PukKernel(int numberOfVectors, double omega, double sigma)
			: Kernel(numberOfVectors), omega(omega), sigma(sigma)
		{

		}

		virtual void calculateDiagonal()
		{
			for (int i = 0; i < numberOfVectors; ++i) {
				kernelDiagonal.push_back(kernelFunction(i, i));
				squaredValues[i] = nodeDot(nodes->at(i), nodes->at(i));
			}
		}

		//Equation 14 from (Ustun, Melssen, Buydens, 2006)
		virtual double kernelFunction(int i, int j)
		{
			double distance = squaredValues[i] + squaredValues[j] -
				2 * nodeDot(nodes->at(i), nodes->at(j));
			double invOmega = 1.0 / omega;
			double radical = pow(2.0, invOmega) - 1.0;
			radical *= distance;
			radical = 2.0 * sqrt(radical) / sigma;
			double denominator = pow(1.0 + pow(radical, 2.0), omega);
			return 1.0 / denominator;
		}

		virtual double kernelFunction(SupportVector& x, SupportVector& y)
		{
			double xsquared = nodeDot(x, x);
			double ysquared = nodeDot(y, y);
			double distance = xsquared + ysquared - 2 * nodeDot(x, y);
			double invOmega = 1.0 / omega;
			double radical = pow(2.0, invOmega) - 1.0;
			radical *= distance;
			radical = 2.0 * sqrt(radical) / sigma;
			double denominator = pow(1.0 + pow(radical, 2.0), omega);
			return 1.0 / denominator;
		}

		virtual void swapIndices(int index1, int index2)
		{
			Kernel::swapIndices(index1, index2);
			std::swap(squaredValues[index1], squaredValues[index1]);
		}

		virtual void getColumn(int size, int columnIndex, vector<float>& column)
		{
			for (int i = 0; i < size; ++i) {
				column[i] = static_cast<float>(signs->at(columnIndex) *
					signs->at(i) * kernelFunction(columnIndex, i));
			}
		}

	private:
		vector<double> squaredValues;
		double omega;
		double sigma;
};



