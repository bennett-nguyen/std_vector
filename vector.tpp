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
    if (this == &other) return *this;
    if (other.m_Capacity > m_Capacity) {
        Vector temp(other);
        std::swap(m_Buffer, temp.m_Buffer);
        std::swap(m_Capacity, temp.m_Capacity);
        std::swap(m_Size, temp.m_Size);
        return *this;
    }

    std::destroy_n(m_Buffer, m_Size);

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
T *Vector<T, Allocator>::data() {
    return m_Buffer;
}

template<typename T, typename Allocator>
const T *Vector<T, Allocator>::data() const {
    return m_Buffer;
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::reference Vector<T, Allocator>::front() {
    return *begin();
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::front() const {
    return *begin();
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::reference Vector<T, Allocator>::back() {
    return *std::prev(end());
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference Vector<T, Allocator>::back() const {
    return *std::prev(end());
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::begin() noexcept {
    return m_Buffer;
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::begin() const noexcept {
    return m_Buffer;
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cbegin() const noexcept {
    return m_Buffer;
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end() noexcept {
    return begin() + m_Size;
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::end() const noexcept {
    return begin() + m_Size;
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator Vector<T, Allocator>::cend() const noexcept {
    return begin() + m_Size;
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rbegin() noexcept {
    return std::make_reverse_iterator(end());
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rbegin() const noexcept {
    return std::make_reverse_iterator(end());
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crbegin() const noexcept {
    return std::make_reverse_iterator(end());
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator Vector<T, Allocator>::rend() noexcept {
    return std::make_reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::rend() const noexcept {
    return std::make_reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator Vector<T, Allocator>::crend() const noexcept {
    return std::make_reverse_iterator(begin());
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
void Vector<T, Allocator>::reserve(const size_t new_cap) {
    if (new_cap <= capacity()) return;
    // if (new_cap > max_size()) throw std::length_error("reservation exceeded maximum size");
    T* new_buffer = m_Alloc.allocate(new_cap);

    try {
        std::uninitialized_copy_n(m_Buffer, size(), new_buffer);
    } catch (...) {
        m_Alloc.deallocate(new_buffer, new_cap);
        throw;
    }

    std::destroy_n(m_Buffer, size());
    m_Alloc.deallocate(new_buffer, m_Capacity);

    m_Buffer = new_buffer;
    m_Capacity = new_cap;
}

template<typename T, typename Allocator>
size_t Vector<T, Allocator>::capacity() const noexcept {
    return m_Capacity;
}

template<typename T, typename Allocator>
void Vector<T, Allocator>::shrink_to_fit() {
    Vector temp(*this);
    std::swap(m_Buffer, temp.m_Buffer);
    std::swap(m_Size, temp.m_Size);
    std::swap(m_Capacity, temp.m_Capacity);
}

// Modifiers
template<typename T, typename Allocator>
void Vector<T, Allocator>::clear() {
    std::destroy_n(m_Buffer, m_Size);
    m_Size = 0;
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
    // if empty() is true then the behavior is undefined
    // but let's just say for the sake of god popping back an empty vector does nothing
    if (empty()) return;
    --m_Size;
    std::destroy_at(m_Buffer + m_Size);
}

#endif