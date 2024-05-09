#pragma once
template <class T>
class Vector {
public:
    Vector() : size_t(0), capacity(10) {
        arr = new T[capacity];
    }

    ~Vector() {
        delete[] arr;
    }

    void push_back(const T& value) {
        if (size_t >= capacity) {
            expandCapacity();
        }
        arr[size_t] = value;
        size_t++;
    }

    T& at(int index) {
        if (index < 0 || index >= size_t) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    int size() const {
        return size_t;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size_t) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size_t) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    void clear()
    {
        size_t = 0;
    }

private:
    T* arr;
    int size_t;
    int capacity;

    void expandCapacity() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < size_t; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
};
