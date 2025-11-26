#include <iostream>

#include "linalg.h"

int main()
{
	try
	{
		const int xsize = 5;
		const int ysize = 6;
		Matrix A(xsize, ysize);
		Matrix B(xsize, ysize);
		A(1, 2) = 12;
		B(3, 4) = 34;
		Matrix M = (A + B).transpose();
		/* Заметьте, что использование auto здесь приведёт к ошибке:
		 * auto M = (A + B).transpose();
		 * Здесь auto будет равно Transpose<Sum<Matrix, Matrix>>, но класс
		 * Transpose будет хранить ссылку на временный объект Sum, который после
		 * точки с запятой будет уничтожен. Поэтому M будет хранить битую ссылку,
		 * что приведёт к неопределённому поведению (undefined behavior).
		 * Явное указание типа Matrix вызовет преобразующий конструктор
		 * Matrix(const Expression<E> &e), который вычислит выражение типа
		 * Transpose<Sum<Matrix, Matrix>> и запишет результаты в приватный член
		 * data.
		 *
		 * Подобное предостережение написано в документации Eigen в разделе
		 * "C++11 and the auto keyword"
		 * https://eigen.tuxfamily.org/dox/TopicPitfalls.html
		 */
		for(int i = 0; i < M.getXsize(); i++)
		{
			for(int j = 0; j < M.getYsize(); j++)
				std::cout << M(i, j) << " ";
			std::cout << "\n";
		}
	}
	catch(Exception &e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
