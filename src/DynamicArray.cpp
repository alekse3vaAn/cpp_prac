#include "../include/DynamicArray.h"
#include <iostream>

DynamicArray::DynamicArray(int n) {
    size = n > 0 ? n : 0;
    data = new int[size]();
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << '\n';
}

void DynamicArray::set(int index, int value) {
    if (index < 0 || index >= size) {
        std::cout << "Error: index out of range\n";
        return;
    }
    if (value < -100 || value > 100) {
        std::cout << "Error: value must be between -100 and 100\n";
        return;
    }
    data[index] = value;
}

int DynamicArray::get(int index) const {
    if (index < 0 || index >= size) {
        std::cout << "Error: index out of range\n";
        return 0;
    }
    return data[index];
}

void DynamicArray::pushBack(int value) {
    if (value < -100 || value > 100) {
        std::cout << "Error: value must be between -100 and 100\n";
        return;
    }

    int* newData = new int[size + 1];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    newData[size] = value;

    delete[] data;
    data = newData;
    size++;
}

void DynamicArray::add(const DynamicArray& other) {
    for (int i = 0; i < size && i < other.size; i++) {
        data[i] += other.data[i];
    }
}

void DynamicArray::sub(const DynamicArray& other) {
    for (int i = 0; i < size && i < other.size; i++) {
        data[i] -= other.data[i];
    }
}
