#include "../include/DynamicArray.h"
#include <new>
#include <string>
#include <utility>

void passByValue(DynamicArray<int> array, const char* label, const int* address) {
    std::cout << label << ": " << array << '\n';
    std::cout << "Same data pointer: " << (array.begin() == address) << '\n';
}

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

    DynamicArray<int> original(3);
    original.set(0, 4);
    original.set(1, 5);
    original.set(2, 6);

    DynamicArray<int> assigned(1);
    assigned = original;
    std::cout << "Copy assignment: " << assigned << '\n';
    DynamicArray<int>& same = assigned;
    assigned = same;
    std::cout << "Self-assignment: " << assigned << '\n';

    DynamicArray<int> first(1);
    DynamicArray<int> second(1);
    first = second = original;
    std::cout << "Chain assignment: " << first << " / " << second << '\n';

    DynamicArray<int> moved(std::move(original));
    std::cout << "Move constructor: " << moved << '\n';
    std::cout << "Original after move, size: " << original.getSize() << '\n';

    DynamicArray<int> target(2);
    target = std::move(moved);
    std::cout << "Move assignment: " << target << '\n';
    std::cout << "Moved-from object size: " << moved.getSize() << '\n';

    DynamicArray<int> source(3);
    source.set(0, 10);
    source.set(1, 20);
    source.set(2, 30);
    const int* address = source.begin();
    passByValue(source, "Passing by copy", address);
    std::cout << "Source before move: " << source << '\n';
    passByValue(std::move(source), "Passing by move", address);
    std::cout << "Source after move, size: " << source.getSize() << '\n';

    return 0;
}
