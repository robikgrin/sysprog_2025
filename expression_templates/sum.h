#ifndef SUM_H
#define SUM_H

#include "expression.h"
#include "exception.h"

/**
 * Templated class representing sum of two matrix expressions
 */
template<typename E1, typename E2>
class Sum: public Expression<Sum<E1, E2>>
{
public:
	Sum(const E1 &e1, const E2 &e2); // TODO

	int getXsize() const { /* TODO */ }
	int getYsize() const { /* TODO */ }

	double operator ()(int i, int j) const
	{
		// TODO
	}

private:
	// TODO
};

/**
 * @brief Operator "+" for two matrix expressions
 */
template<typename E1, typename E2>
Sum<E1, E2> operator+(const Expression<E1> &e1, const Expression<E2> &e2)
{
	// TODO
}

#endif // SUM_H
