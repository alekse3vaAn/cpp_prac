#include "../include/DynamicArray.h"
#include <iostream>

int main() {
    DynamicArray a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);

    std::cout << "Array a: ";
    a.print();
    std::cout << "a[1] = " << a.get(1) << '\n';

    a.set(0, 150);
    a.get(5);

    DynamicArray copy(a);
    copy.set(0, -10);
    std::cout << "Copy: ";
    copy.print();
    std::cout << "Original: ";
    a.print();

    a.pushBack(40);
    std::cout << "After pushBack: ";
    a.print();

    DynamicArray b(2);
    b.set(0, 3);
    b.set(1, 5);
    std::cout << "Array b: ";
    b.print();

    a.add(b);
    std::cout << "After add: ";
    a.print();

    a.sub(b);
    std::cout << "After sub: ";
    a.print();

    return 0;
}
