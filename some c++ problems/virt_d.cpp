#include <iostream>

class A {
public:
    virtual ~A() {
        std::cout << "~A()\n";
    }
};

class B {
public:
    ~B() {
        std::cout << "~B()\n";
    }
};

class C : public A, public B {
public:
    ~C(){
        std::cout << "~C()\n";
    }
};

int main() {
    std::cout << "Создание и удаление через указатель A (виртуальный)" << std::endl;
    A* a_ptr = new C();
    delete a_ptr;

    std::cout << "Создание и удаление через указатель B (не виртуальный)" << std::endl;
    B* b_ptr = new C();
    delete b_ptr;

    return 0;
}