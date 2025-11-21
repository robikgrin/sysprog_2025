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
	List(const List &other) {
		Node *current = other.first;

		while (current != nullptr) {
			this->push_back(current->value);
			current = current->next;
		}
	}; 

	/* Перемещающий конструктор не производит копирования, то есть
	 * в любой момент времени существует только одна копия узлов
	 * списка. После перемещения other должен стать пустым списком.
	 */
	List(List &&other) :
    first(other.first),
    last(other.last),
    cached_size(other.cached_size) // занимаем все необходимое у oher
	{
		other.first = nullptr;
		other.last = nullptr;
		other.cached_size = 0; // обнуляем other
	}	

	~List() { clear();} // Деструктор

	void push_before(Iterator it, double value) {
		if (it.n == nullptr) {
			return;
		} else if (it.n == first) {
			push_front(value);
			return;
		}

		Node *new_node = new Node; // новый узел в памяти
		new_node->value = value; // добавляем value как значение
		new_node->next = it.n; // вставляем элемент: до итератора
		new_node->prev = it.n->prev; // перед последующим за итератором

		it.n->prev = new_node; // указываем на предыдущий за итератором - вставляемый элемент
		new_node->prev->next = new_node; // указываем, что следующий и предыдущего это вставляемый элемент
		cached_size++;

	};
	void push_after(Iterator it, double value) {
		if (it.n == nullptr) {
			return;
		}
		else if (it.n == last) {
			push_back(value);
			return;
		}
		
		Node *new_node = new Node; //новый узел в памяти
		new_node->value = value; //добавляем value как значение
		new_node->prev = it.n; // вставляем элемент: после итератора
		new_node->next = it.n->next; // до следующего за итератором

		it.n->next = new_node; // указатель на вставленный элемент от предыдущего
		new_node->next->prev = new_node; // указатель на вставленный элемент от следующего
		cached_size++;

	}; 

	void pop(Iterator it) {
		if (it.n == first){
			pop_front();
			return;
		}else if (it.n == last){
			pop_back();
			return;
		}

		Node *next_node = it.n->next; // указываем на следующий от удалаемого
		Node *prev_node = it.n->prev; // на предыдущий

		prev_node->next = next_node; // стираем информацию об удалаемом элементе
		next_node->prev = prev_node;
		delete(it.n); // удаляем
		cached_size--;
	};

	void push_back(double value) {
		Node *new_node = new Node; //новый узел в памяти
		new_node->value = value; //присваиваем значение
		new_node->next = nullptr;
		new_node->prev = last; //предыдущий узел - был последний

		if (first == nullptr) {
			first = new_node; // если список был пуст, новый узел - первый
			last = new_node;
		}
		else {
			last->next = new_node; //связываем последний узел с новым
			last = new_node; //обновляем указатель на последний узел
		}
		cached_size++; //увеличиваем размер списка, так как добавили новый элемент
	}

	void push_front(double value){
		Node *new_node = new Node; //новый узел в памяти
		new_node->value = value; //присваиваем значение
		new_node->prev = nullptr;
		new_node->next = first; //предыдущий узел - был последний

		if (first == nullptr) {
			first = new_node; // если список был пуст, новый узел - первый
			last = new_node;
		}
		else {
			first->prev = new_node; //связываем последний узел с новым
			first = new_node; //обновляем указатель на последний узел
		
		cached_size++; //увеличиваем размер списка, так как добавили новый элемент
		}
	}

	void pop_back() {
		if (last == nullptr) {
			return; // список пуст, нечего удалять
		}
		Node *node_to_delete = last; // сохраняем указатель на последний узел
		last = last->prev; // обновляем указатель на последний узел
		if (last == nullptr) {
			first = nullptr; // если список стал пустым, обновляем указатель на первый узел
		} else {
			last->next = nullptr; // обнуляем указатель на следующий узел нового последнего узла
		}
		delete node_to_delete;
		cached_size--; // уменьшаем размер списка
	}; 

	void pop_front(){
		if (first == nullptr) {
			return; // список пуст, нечего удалять
		}
		Node *node_to_delete = first; // сохраняем указатель на первый узел
		first = first->next; // обновляем указатель на первый узел

		if (first == nullptr) {
			last = nullptr; // если список стал пустым, обновляем указатель на последний узел
		} else {
			first->prev = nullptr; // обнуляем указатель на предыдущий узел нового первого узла
		}
		delete node_to_delete; // удаляем
		cached_size--; // уменьшаем размер списка
	}; 

	void clear(){
		Node* current = first;
		while (current != nullptr) {
			Node* next_node = current->next; // сохраняем указатель на следующий узел
			delete current; // удаляем текущий узел
			current = next_node; // переходим к следующему узлу
		}
		first = nullptr; // обнуляем указатели на первый и последний узлы
		last = nullptr;
		cached_size = 0; // обнуляем размер списка
	}; 
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
