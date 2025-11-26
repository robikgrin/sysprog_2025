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
	Transpose(const E& e); // TODO

	int getXsize() const { /* TODO */ }
	int getYsize() const { /* TODO */ }

	double operator ()(int i, int j) const
	{
		// TODO
	}

	/**
	 * @brief Optimized version of transpose of transposed expression.
	 *
	 * Useful for expressions like `m.transpose().transpose()`
	 */
	const E& transpose() const noexcept
	{
		// TODO
	}

private:
	// TODO
};

#endif // TRANSPOSE_H
