#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "vector.h"

template<typename T>
Vector<T>::Vector(const size_t n) {
    if (n == 0) return;

    T* new_buffer = static_cast<T*>(::operator new(n * sizeof(T)));
    try {
        std::uninitialized_default_construct_n(new_buffer, n);
    } catch (...) {
        ::operator delete(new_buffer);
        throw;
    }

    m_Buffer = new_buffer;
    m_Size = n;
    m_Capacity = n;
}

template<typename T>
Vector<T>::~Vector() {
    std::destroy_n(m_Buffer, m_Size);
    ::operator delete(m_Buffer);
    m_Size = 0;
    m_Capacity = 0;
}

template<typename T>
Vector<T>::Vector(const Vector &other) {
    if (&other == this) return;
    if (other.capacity() == 0) return;

    T* new_buffer = static_cast<T*>(::operator new(other.capacity() * sizeof(T)));

    try {
        std::uninitialized_copy_n(other.m_Buffer, other.size(), m_Buffer);
    } catch (...) {
        ::operator delete(new_buffer);
        throw;
    }

    m_Buffer = new_buffer;
    m_Capacity = other.capacity();
    m_Size = other.size();
}

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (&other == this) return *this;
    if (other.empty()) {
        clear();
        return *this;
    }

    if (other.capacity() > capacity()) {
        Vector temp(other);
        std::swap(m_Buffer, temp.m_Buffer);
        std::swap(m_Capacity, temp.m_Capacity);
        std::swap(m_Size, temp.m_Size);
        return *this;
    }

    std::destroy_n(m_Buffer, size());

    try {
        std::uninitialized_copy_n(other.m_Buffer, other.size(), m_Buffer);
    } catch (...) {
        m_Size = 0;
        throw;
    }

    m_Size = other.size();
    return *this;
}

template<typename T>
T &Vector<T>::operator[](const size_t pos) {
    if (pos >= size()) throw std::out_of_range("position out of bound");
    return m_Buffer[pos];
}

template<typename T>
const T &Vector<T>::operator[](size_t pos) const {
    if (pos >= size()) throw std::out_of_range("position out of bound");
    return m_Buffer[pos];
}

template<typename T>
void Vector<T>::push_back(const T& element) {
    if (capacity() == 0) {
        T* new_buffer = static_cast<T*>(::operator new(sizeof(T)));
        new (new_buffer + m_Size) T(element);
        m_Buffer = new_buffer;
        m_Size = 1;
        m_Capacity = 1;
        return;
    }

    if (full()) {
        const size_t new_capacity = m_Capacity + (m_Capacity + 1) / 2;
        T* new_buffer = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

        try {
            std::uninitialized_copy_n(m_Buffer, m_Size, new_buffer);
        } catch (...) {
            ::operator delete(new_buffer);
            throw;
        }

        new (new_buffer + m_Size) T(element);

        std::destroy_n(m_Buffer, m_Size);
        ::operator delete(m_Buffer);

        m_Buffer = new_buffer;
        m_Capacity = new_capacity;
        m_Size++;
        return;
    }

    new (m_Buffer + m_Size) T(element);
    ++m_Size;
}

template<typename T>
void Vector<T>::pop_back() {
    if (empty()) return;
    --m_Size;
    std::destroy_at(m_Buffer + m_Size);
}

template<typename T>
bool Vector<T>::empty() const {
    return m_Size == 0;
}

template<typename T>
bool Vector<T>::full() const {
    return m_Size == m_Capacity;
}

template<typename T>
size_t Vector<T>::size() const {
    return m_Size;
}

template<typename T>
size_t Vector<T>::capacity() const {
    return m_Capacity;
}

template<typename T>
void Vector<T>::reserve(const size_t n) {
    if (n <= capacity()) return;
    T* new_buffer = static_cast<T*>(::operator new(n * sizeof(T)));

    try {
        std::uninitialized_copy_n(m_Buffer, size(), new_buffer);
    } catch (...) {
        ::operator delete(new_buffer);
        throw;
    }

    std::destroy_n(m_Buffer, size());
    ::operator delete(m_Buffer);

    m_Buffer = new_buffer;
    m_Capacity = n;
}

template<typename T>
void Vector<T>::clear() {
    if (empty() or capacity() == 0) return;
    std::destroy_n(m_Buffer, size());
    m_Size = 0;
}

#endif