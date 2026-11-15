#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <new>

template<typename T>
class Vector {
    T* m_Buffer {};
    size_t m_Size {};
    size_t m_Capacity {};
public:
    Vector() = default;
    ~Vector();
    explicit Vector(size_t n);
    Vector(const Vector& other);

    void reserve(size_t n);
    void clear();

    Vector& operator=(const Vector& other);
    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    void push_back(const T& element);
    void pop_back();
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    bool full() const;
};

#include "vector.tpp"

#endif