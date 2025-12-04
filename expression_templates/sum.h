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
	Sum(const E1 &e1, const E2 &e2) : el_1(e1), el_2(e2)
	{
		// проверка на размеры
		if (e1.getXsize() != e2.getXsize() || e1.getYsize() != e2.getYsize())
    	{
			throw Exception("Sum operation: incompatible matrix sizes");
    	}
	}
	int getXsize() const { return el_1.getXsize(); }
	int getYsize() const { return el_2.getYsize(); }

	double operator ()(int i, int j) const
	{
		return el_1(i,j) + el_2(i,j);
	}

private:
	const E1& el_1;
	const E2& el_2;
};

/**
 * @brief Operator "+" for two matrix expressions
 */
template<typename E1, typename E2>
Sum<E1, E2> operator+(const Expression<E1> &e1, const Expression<E2> &e2)
{
	return Sum<E1, E2>(
		static_cast<const E1&>(e1),
		static_cast<const E2&>(e2)
	);
}

#endif // SUM_H
