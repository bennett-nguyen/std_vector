// An implementation of std::vector - a dynamic sequence container provided by the Standard Template Library (STL);
// C++ Version: Since C++11, until C++20.
// Referred from: https://en.cppreference.com/cpp/container/vector
//
// Copyright (C) 2026  Nguyen Vinh Phu
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <new>

template<typename T, typename Allocator = std::allocator<T>>
class Vector {
    T* m_Buffer {};
    Allocator m_Alloc {};
    size_t m_Size {};
    size_t m_Capacity {};
public:
    // Member types
    typedef T                  value_type;
    typedef Allocator          allocator_type;
    typedef std::size_t        size_type;
    typedef value_type&        reference;
    typedef const value_type&  const_reference;

    // Member functions
    Vector() noexcept(noexcept(Allocator())) : Vector(Allocator()) {};
    explicit Vector(const Allocator& alloc);
    explicit Vector(size_type count, const Allocator& alloc = Allocator());
    Vector(size_type count, const T& value, const Allocator& alloc = Allocator());
    Vector(const Vector& other);
    Vector(Vector&& other);
    Vector(const Vector& other, const Allocator& alloc);
    Vector(Vector&& other, const Allocator& alloc);
    Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator());

    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector& other);
    Vector& operator=(std::initializer_list<value_type> ilist);

    // Element access
    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;
    T& at(size_t pos);
    const T& at(size_t pos) const;
    T* data() noexcept;
    const T* data() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_t max_size() const noexcept;
    size_t size() const noexcept;
    size_t capacity() const noexcept;

    // Modifiers
    void clear();
    void reserve(size_t n);
    void push_back(const T& element);
    void pop_back();
};

#include "vector.tpp"

#endif