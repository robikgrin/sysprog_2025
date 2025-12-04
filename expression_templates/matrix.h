#ifndef MATRIX_H
#define MATRIX_H

#include "expression.h"
#include "exception.h"
#include <vector>

/**
 * @brief Class representing matrix
 */
class Matrix: public Expression<Matrix>
{
public:
	/**
	 * @brief Construct zero-initialized matrix with given sizes
	 * @param xsize - number of columns
	 * @param ysize - number of rows
	 */
	Matrix(int xsize, int ysize): xsize(xsize), ysize(ysize), data(xsize*ysize) {}

	/**
	 * @brief Templated constructor that performs evaluation of the given
	 * expression and assigns values to the `Matrix` object
	 * @param e - expression to evaluate
	 */
	template<typename E>
	Matrix(const Expression<E> &e)
	{
		int source_x = e.getXsize();
		int source_y = e.getYsize();

		this->xsize = source_x;
		this->ysize = source_y;

		this->data.resize(source_x * source_y);
		for (int i = 0; i < source_y; i++)
		{ 
			for (int j = 0; j < source_x; j++)
			{
				int k = i * source_x + j;
				data[k] = e(i,j);
			}
		}
	}

	int getXsize() const noexcept { return xsize; }
	int getYsize() const noexcept { return ysize; }

	/**
	 * @brief Get element with indeces i and j
	 * @param i - row index
	 * @param j - column index
	 * @return Element value
	 *
	 * This is const overload
	 */
	double operator ()(int i, int j) const
	{
		if (i < 0 || j < 0 || i >= ysize || j >= xsize){
			throw Exception("Index out of bounds");
		}

		int k = i * xsize + j; // индекс вызываемого элемента
		return data[k];
	}

	/**
	 * @brief Get element with indeces i and j
	 * @param i - row index
	 * @param j - column index
	 * @return Element value
	 *
	 * This is non-const overload
	 */
	double& operator ()(int i, int j)
	{
		if (i < 0 || j < 0 || i >= ysize || j >= xsize){
			throw Exception("Index out of bounds");
		}

		int k = i * xsize + j;

		return data[k];
	}

private:
	int xsize = 0;
	int ysize = 0;
	std::vector<double> data; ///< Data in row-major order
};

#endif // MATRIX_H
