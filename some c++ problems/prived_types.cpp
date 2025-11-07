#include <iostream>
#include <cstdint>

class A {
public:
    int a = 1;
};

class B {
public:
    int b = 2;
};

class C : public A, public B {
public:
    int c = 3;
};

int main() {
    C c;
    std::cout << "Address of c:          " << &c << '\n';
    std::cout << "static_cast<A*>(&c):   " << static_cast<A*>(&c) << '\n';
    std::cout << "static_cast<B*>(&c):   " << static_cast<B*>(&c) << '\n';
    std::cout << "reinterpret_cast<A*>(&c): " << reinterpret_cast<A*>(&c) << '\n';
    std::cout << "reinterpret_cast<B*>(&c): " << reinterpret_cast<B*>(&c) << '\n';

    // Разница в смещениях
    std::cout << "\nOffsets (in bytes):\n";
    std::cout << "A offset: " << (char*)static_cast<A*>(&c) - (char*)&c << '\n';
    std::cout << "B offset: " << (char*)static_cast<B*>(&c) - (char*)&c << '\n';

    return 0;
}