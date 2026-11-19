#include "../include/DynamicArray.h"
#include <new>
#include <string>

int main() {
    DynamicArray<int> a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);

    DynamicArray<int> b(3);
    b.set(0, 1);
    b.set(1, 2);
    b.set(2, 3);

    std::cout << "Array a: " << a << '\n';
    std::cout << "Array b: " << b << '\n';
    std::cout << "Distance: " << a.distance(b) << '\n';

    a.add(b);
    std::cout << "After add: " << a << '\n';
    a.sub(b);
    std::cout << "After sub: " << a << '\n';

    DynamicArray<int> copy(a);
    copy.set(0, -10);
    std::cout << "Copy: " << copy << '\n';
    std::cout << "Original: " << a << '\n';

    a.pushBack(40);
    std::cout << "After pushBack: " << a << '\n';

    try {
        a.set(0, 150);
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << '\n';
    }

    try {
        a.get(10);
    } catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << '\n';
    }

    try {
        a.distance(b);
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << '\n';
    }

    DynamicArray<std::string> words(2);
    words.set(0, "hello");
    words.set(1, "world");
    std::cout << "String array: " << words << '\n';

    try {
        words.distance(words);
    } catch (const std::bad_typeid& e) {
        std::cout << "bad_typeid: " << e.what() << '\n';
    }

    DynamicArray<double> numbers(2);
    numbers.set(0, 125.5);
    numbers.set(1, 2.5);
    std::cout << "Double array: " << numbers << '\n';

    try {
        throw std::bad_alloc();
    } catch (const std::bad_alloc& e) {
        std::cout << "Simulated bad_alloc: " << e.what() << '\n';
    }

    return 0;
}
