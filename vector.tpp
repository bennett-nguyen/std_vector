#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "vector.h"

// Member access
template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(const size_type count, const Allocator& alloc) : m_Alloc(alloc) {
    if (count == 0) return;

    T* new_buffer = m_Alloc.allocate(count);

    try {
        std::uninitialized_value_construct_n(new_buffer, count);
    } catch (...) {
        m_Alloc.deallocate(new_buffer, count);
        throw;
    }

    m_Buffer = new_buffer;
    m_Size = count;
    m_Capacity = count;
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Allocator &alloc) : m_Alloc(alloc) {}

template<typename T, typename Allocator>
Vector<T, Allocator>::~Vector() {
    std::destroy_n(m_Buffer, m_Size);
    m_Alloc.deallocate(m_Buffer, m_Capacity);
    m_Size = 0;
    m_Capacity = 0;
}

template<typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector &other) {
    if (&other == this) return;
    if (other.capacity() == 0) return;

    T* new_buffer = m_Alloc.allocate(other.m_Capacity);

    try {
        std::uninitialized_copy_n(other.m_Buffer, other.size(), m_Buffer);
    } catch (...) {
        m_Alloc.deallocate(new_buffer, other.m_Capacity);
        throw;
    }

    m_Buffer = new_buffer;
    m_Capacity = other.m_Capacity;
    m_Size = other.m_Size;
}

template<typename T, typename Allocator>
Vector<T, Allocator> &Vector<T, Allocator>::operator=(const Vector &other) {
    if (&other == this) return *this;
    if (other.empty()) {
        clear();
        return *this;
    }

    if (other.m_Capacity > m_Capacity) {
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

// Element access
template<typename T, typename Allocator>
T& Vector<T, Allocator>::operator[](const size_t pos) {
    return m_Buffer[pos];
}

template<typename T, typename Allocator>
const T& Vector<T, Allocator>::operator[](size_t pos) const {
    return m_Buffer[pos];
}

template<typename T, typename Allocator>
T& Vector<T, Allocator>::at(const size_t pos) {
    if (pos >= size()) throw std::out_of_range("position out of bound");
    return m_Buffer[pos];
}

template<typename T, typename Allocator>
const T& Vector<T, Allocator>::at(size_t pos) const {
    if (pos >= size()) throw std::out_of_range("position out of bound");
    return m_Buffer[pos];
}

template<typename T, typename Allocator>
T *Vector<T, Allocator>::data() noexcept {
    return m_Buffer;
}

template<typename T, typename Allocator>
const T *Vector<T, Allocator>::data() const noexcept {
    return m_Buffer;
}

// Capacity
template<typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const noexcept {
    return m_Size == 0;
}


template<typename T, typename Allocator>
size_t Vector<T, Allocator>::size() const noexcept {
    return m_Size;
}

template<typename T, typename Allocator>
size_t Vector<T, Allocator>::capacity() const noexcept {
    return m_Capacity;
}

// Modifiers
template<typename T, typename Allocator>
void Vector<T, Allocator>::clear() {
    if (empty() or capacity() == 0) return;
    std::destroy_n(m_Buffer, size());
    m_Size = 0;
}

template<typename T, typename Allocator>
void Vector<T, Allocator>::reserve(const size_t n) {
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

template<typename T, typename Allocator>
void Vector<T, Allocator>::push_back(const T& element) {
    if (m_Capacity == 0) {
        T* new_buffer = m_Alloc.allocate(1);
        new (new_buffer + m_Size) T(element);
        m_Buffer = new_buffer;
        m_Size = 1;
        m_Capacity = 1;
        return;
    }

    if (m_Size != m_Capacity) {
        new (m_Buffer + m_Size) T(element);
        ++m_Size;
        return;
    }

    const size_t new_capacity = m_Capacity + (m_Capacity + 1) / 2;
    T* new_buffer = m_Alloc.allocate(new_capacity);

    try {
        std::uninitialized_copy_n(m_Buffer, m_Size, new_buffer);
    } catch (...) {
        m_Alloc.deallocate(new_buffer, new_capacity);
        throw;
    }

    new (new_buffer + m_Size) T(element);

    std::destroy_n(m_Buffer, m_Size);
    m_Alloc.deallocate(m_Buffer, m_Size);

    m_Buffer = new_buffer;
    m_Capacity = new_capacity;
    m_Size++;
}

template<typename T, typename Allocator>
void Vector<T, Allocator>::pop_back() {
    if (empty()) return;
    --m_Size;
    std::destroy_at(m_Buffer + m_Size);
}

#endif