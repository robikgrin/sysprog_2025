#include <ostream>

class List
{
private:
	// Узел списка
	struct Node
	{
		double value = 0.; // Значение узла
		Node *prev = nullptr; // Указатель на предыдущий узел
		Node *next = nullptr; // Указатель на следующий узел
	};
	
	Node *first = nullptr;
	Node *last = nullptr;
	size_t cached_size = 0;

public:
	/* Итератор двусвязного списка.
	 * В данном случае итератор представляет собой класс-обёртку над указателем
	 * на узел, но для других структур данных это может быть иначе.
	 */
	struct Iterator
	{
		explicit Iterator(List *list, Node *node): // Конструктор для удобства
			l(list), n(node)
		{} 

		Iterator& operator++() // Инкремент итератора
		{
			n = n->next;
			return *this;
		} 

		Iterator& operator--() // Декремент итератора
		{
			if(n)
				n = n->prev;
			else
				n = l->last;
			return *this;
		} 

		double& operator*() { return n->value; } // Оператор разыменования итератора
		
		const double& operator*() const { return n->value; } // То же, но константный
		
		bool operator==(const Iterator &other) const // Сравнение итераторов
		{
			return l == other.l && n == other.n;
		}
		
		bool operator!=(const Iterator &other) const
		{
			return l != other.l || n != other.n;
		}

		List *l; // Указатель на список, которому принадлежит узел
		Node *n; // Указатель на узел, куда ссылается итератор
	};

	/* Итератор на первый элемент.
	 */
	Iterator begin() { return Iterator(this, first); }

	/* Итератор на элемент, следующий за последним.
	 * Этот элемент не является валидным, поэтому nullptr здесь уместен.
	 */
	Iterator end() { return Iterator(this, nullptr); }

	size_t size() const { return cached_size; } // Число элементов в списке

	List() = default; // Попросить компилятор создать конструктор по умолчанию,
	                  // т.к. компилятор согласно стандарту C++ удаляет неявно
					  // созданный конструктор, потому что ниже объявлены
					  // явные копирующий и перемещающий конструкторы
	/* Копирующий конструктор должен создать полную копию списка
	 * вместе со всеми узлами. Исходный список при этом остаётся
	 * неизменным.
	 */
	List(const List &other); // TODO

	/* Перемещающий конструктор не производит копирования, то есть
	 * в любой момент времени существует только одна копия узлов
	 * списка. После перемещения other должен стать пустым списком.
	 */
	List(List &&other); // TODO

	~List() { clear(); } // Деструктор

	void push_before(Iterator it, double value); // TODO
	void push_after(Iterator it, double value); // TODO
	void pop(Iterator it); // TODO
	void push_back(double value); // TODO
	void push_front(double value); // TODO
	void pop_back(); // TODO
	void pop_front(); // TODO
	void clear(); // TODO
};

// Вывести все элементы списка в поток (вместо функции print)
static inline std::ostream& operator<<(std::ostream &stream, List &l)
{
	for(auto val: l)
		stream << val << " ";
	/* Явный эквивалент циклу выше:
	 * for(List::Iterator iter = l.begin(); iter != l.end(); ++iter)
	 *     s << *iter << " ";
	 * 
	 * Поэтому range-based цикл "for(auto val: l)" работает
	 * только потому, что у List объявлены метод begin() и end(),
	 * которые возвращают итератор, а у итератора присутствуют
	 * методы инкремента operator++, разыменовывания operator*
	 * и проверки на неравенство operator!=
	 */
	return stream;
}
