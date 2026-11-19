#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include <utility>

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

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) {
            return *this;
        }
        DynamicArray copy(other);
        std::swap(data, copy.data);
        std::swap(size, copy.size);
        return *this;
    }

    DynamicArray(DynamicArray&& other) noexcept : size(other.size), data(other.data) {
        other.size = 0;
        other.data = nullptr;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data;
        size = other.size;
        data = other.data;
        other.size = 0;
        other.data = nullptr;
        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    int getSize() const { return size; }

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

    class Reference {
    private:
        DynamicArray& array;
        int index;

    public:
        Reference(DynamicArray& array, int index) : array(array), index(index) {}

        Reference& operator=(const T& value) {
            array.set(index, value);
            return *this;
        }

        Reference& operator=(const Reference& other) {
            return *this = static_cast<T>(other);
        }

        operator T() const {
            return array.get(index);
        }
    };

    Reference operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return Reference(*this, index);
    }

    const T& operator[](int index) const {
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

    bool operator==(const DynamicArray& other) const {
        if (size != other.size) {
            return false;
        }
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

    DynamicArray& operator+=(const DynamicArray& other) {
        if constexpr (std::is_arithmetic_v<T>) {
            for (int i = 0; i < size && i < other.size; i++) {
                T value = data[i] + other.data[i];
                checkValue(value);
                data[i] = value;
            }
        } else {
            throw std::bad_typeid();
        }
        return *this;
    }

    DynamicArray& operator-=(const DynamicArray& other) {
        if constexpr (std::is_arithmetic_v<T>) {
            for (int i = 0; i < size && i < other.size; i++) {
                T value = data[i] - other.data[i];
                checkValue(value);
                data[i] = value;
            }
        } else {
            throw std::bad_typeid();
        }
        return *this;
    }

    DynamicArray& operator+=(const T& value) {
        if constexpr (std::is_arithmetic_v<T>) {
            for (int i = 0; i < size; i++) {
                T result = data[i] + value;
                checkValue(result);
                data[i] = result;
            }
        } else {
            throw std::bad_typeid();
        }
        return *this;
    }

    DynamicArray& operator-=(const T& value) {
        if constexpr (std::is_arithmetic_v<T>) {
            for (int i = 0; i < size; i++) {
                T result = data[i] - value;
                checkValue(result);
                data[i] = result;
            }
        } else {
            throw std::bad_typeid();
        }
        return *this;
    }

    void add(const DynamicArray& other) {
        *this += other;
    }

    void sub(const DynamicArray& other) {
        *this -= other;
    }

    T* begin() { return data; }
    T* end() { return data ? data + size : nullptr; }
    const T* begin() const { return data; }
    const T* end() const { return data ? data + size : nullptr; }

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
