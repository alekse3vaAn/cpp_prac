#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

template <typename T>
class DynamicArray {
private:
    int size;
    T* data;

    void checkValue(const T& value) const {
        if constexpr (std::is_integral_v<T>) {
            if constexpr (std::is_signed_v<T>) {
                if (value < -100 || value > 100) {
                    throw std::invalid_argument("Value must be between -100 and 100");
                }
            } else if (value > 100) {
                throw std::invalid_argument("Value must be between 0 and 100");
            }
        }
    }

public:
    explicit DynamicArray(int n) : size(n > 0 ? n : 0), data(new T[size]()) {}

    DynamicArray(const DynamicArray& other) : size(other.size), data(new T[size]) {
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    void print() const {
        std::cout << *this << '\n';
    }

    void set(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        checkValue(value);
        data[index] = value;
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void pushBack(const T& value) {
        checkValue(value);

        T* newData = new T[size + 1];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        newData[size] = value;

        delete[] data;
        data = newData;
        size++;
    }

    void add(const DynamicArray& other) {
        if constexpr (std::is_arithmetic_v<T>) {
            for (int i = 0; i < size && i < other.size; i++) {
                data[i] += other.data[i];
            }
        } else {
            throw std::bad_typeid();
        }
    }

    void sub(const DynamicArray& other) {
        if constexpr (std::is_arithmetic_v<T>) {
            for (int i = 0; i < size && i < other.size; i++) {
                data[i] -= other.data[i];
            }
        } else {
            throw std::bad_typeid();
        }
    }

    double distance(const DynamicArray& other) const {
        if (size != other.size) {
            throw std::invalid_argument("Arrays must have the same size");
        }
        if constexpr (std::is_arithmetic_v<T>) {
            double sum = 0;
            for (int i = 0; i < size; i++) {
                double difference = static_cast<double>(data[i]) - static_cast<double>(other.data[i]);
                sum += difference * difference;
            }
            return std::sqrt(sum);
        } else {
            throw std::bad_typeid();
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const DynamicArray& array) {
        for (int i = 0; i < array.size; i++) {
            if (i > 0) {
                out << ' ';
            }
            out << array.data[i];
        }
        return out;
    }
};

#endif
