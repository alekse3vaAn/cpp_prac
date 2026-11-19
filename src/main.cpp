#include "../include/DynamicArray.h"
#include <iostream>
#include <stdexcept>
#include <new>

int main() {
    DynamicArray a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);

    std::cout << "Array a: ";
    a.print();
    std::cout << "a[1] = " << a.get(1) << '\n';

    try {
        a.set(0, 150);
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << '\n';
    }

    try {
        a.get(5);
    } catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << '\n';
    }

    try {
        a.pushBack(-150);
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << '\n';
    }

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

    // Проверка обработки bad_alloc без выделения огромного массива.
    try {
        throw std::bad_alloc();
    } catch (const std::bad_alloc& e) {
        std::cout << "Simulated bad_alloc: " << e.what() << '\n';
    }

    return 0;
}
