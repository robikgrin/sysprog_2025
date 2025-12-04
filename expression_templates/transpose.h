#ifndef TRANSPOSE_H
#define TRANSPOSE_H

#include "expression.h"

/**
 * @brief Templated class representing transposed matrix expression
 */
template<typename E>
class Transpose: public Expression<Transpose<E>>
{
public:
	Transpose(const E& e) : el(e) {}

	int getXsize() const { return el.getYsize(); }
	int getYsize() const { return el.getXsize(); }

	double operator ()(int i, int j) const
	{
		return el(j,i);
	}

	/**
	 * @brief Optimized version of transpose of transposed expression.
	 *
	 * Useful for expressions like `m.transpose().transpose()`
	 */
	const E& transpose() const noexcept
	{
		return el;
	}

private:
	const E& el;
};

#endif // TRANSPOSE_H
