#ifndef EXPRESSION_H
#define EXPRESSION_H

template<typename E> class Transpose; ///< Forward declaration of `Trasnpose` class

/**
 * Class template for any matrix expression
 */
template<typename E>
class Expression
{
public:
	/**
	 * @brief Get element with indeces i and j
	 * @param i - row index
	 * @param j - column index
	 * @return Element value
	 *
	 * This is const overload
	 */
	double operator()(int i, int j) const
	{
		// TODO
	}

	/**
	 * @brief Get element with indeces i and j
	 * @param i - row index
	 * @param j - column index
	 * @return Element value
	 *
	 * This is non-const overload
	 */
	double& operator()(int i, int j)
	{
		// TODO
	}

	/**
	 * @brief Get number of columns
	 */
	int getXsize() const noexcept
	{
		// TODO
	}

	/**
	 * @brief Get number of rows
	 */
	int getYsize() const noexcept
	{
		// TODO
	}

	/**
	 * @brief Return expression that corresponds to transposed matrix
	 */
	Transpose<E> transpose() const noexcept
	{
		// TODO
	}
};

#endif // EXPRESSION_H
