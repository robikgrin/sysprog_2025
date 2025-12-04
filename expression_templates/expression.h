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
		return static_cast<const E&>(*this)(i, j);
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
		return static_cast<E&>(*this)(i, j);
	}

	/**
	 * @brief Get number of columns
	 */
	int getXsize() const noexcept
	{
		// перекастовываемся в тип E, чтобы получить данные о размерах
		return static_cast<const E&>(*this).getXsize();
	}

	/**
	 * @brief Get number of rows
	 */
	int getYsize() const noexcept
	{
		return static_cast<const E&>(*this).getYsize();
	}

	/**
	 * @brief Return expression that corresponds to transposed matrix
	 */
	Transpose<E> transpose() const noexcept
	{
		return Transpose<E>(static_cast<const E&>(*this));
	}
};

#endif // EXPRESSION_H
