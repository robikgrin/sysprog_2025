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
    A* ptr = new C();
    delete ptr;
    return 0;
}