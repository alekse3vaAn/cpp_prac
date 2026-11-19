#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

class DynamicArray {
private:
    int* data;
    int size;

public:
    explicit DynamicArray(int n);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    void print() const;
    void set(int index, int value);
    int get(int index) const;
    void pushBack(int value);
    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);
};

#endif
