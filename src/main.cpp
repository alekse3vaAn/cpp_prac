#include "../include/DynamicArray.h"
#include <new>
#include <string>

int main() {
    DynamicArray<int> a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);

    DynamicArray<int> b(2);
    b.set(0, 1);
    b.set(1, 2);

    std::cout << "Array a: " << a << '\n';
    a[1] = 25;
    std::cout << "a[1]: " << static_cast<int>(a[1]) << '\n';

    try {
        a[1] = 150;
    } catch (const std::invalid_argument& e) {
        std::cout << "invalid_argument: " << e.what() << '\n';
    }

    try {
        a[10] = 5;
    } catch (const std::out_of_range& e) {
        std::cout << "out_of_range: " << e.what() << '\n';
    }

    DynamicArray<int> copy(a);
    std::cout << "a == copy: " << (a == copy) << '\n';
    std::cout << "a != b: " << (a != b) << '\n';

    a += b;
    std::cout << "a += b: " << a << '\n';
    a -= b;
    std::cout << "a -= b: " << a << '\n';
    a += 5;
    std::cout << "a += 5: " << a << '\n';
    a -= 5;
    std::cout << "a -= 5: " << a << '\n';

    const DynamicArray<int>& constArray = a;
    std::cout << "Const range-for:";
    for (const auto& x : constArray) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';

    for (auto& x : a) {
        x += 1;
    }
    std::cout << "After range-for: " << a << '\n';

    std::cout << "Distance: " << a.distance(copy) << '\n';
    a.add(b);
    a.sub(b);
    a.pushBack(40);
    std::cout << "After add, sub and pushBack: " << a << '\n';

    try {
        a.distance(copy);
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
    numbers += 1.5;
    std::cout << "Double array: " << numbers << '\n';

    try {
        throw std::bad_alloc();
    } catch (const std::bad_alloc& e) {
        std::cout << "Simulated bad_alloc: " << e.what() << '\n';
    }

    return 0;
}
