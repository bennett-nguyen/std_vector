// An implementation of std::vector - a dynamic sequence container provided by the Standard Template Library (STL);
// C++ Version: Since C++11, until C++20.
// Referred from: https://en.cppreference.com/cpp/container/vector
// WARNING: This only works for default allocators!
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
#include <algorithm>
#include <iterator>

template<typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
    // Member types
    using value_type             = T;
    using allocator_type         = Allocator;
    using size_type              = std::size_t;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using iterator               = T*;
    using const_iterator         = const T*;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

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
    Vector& operator=(Vector&& other);
    Vector& operator=(std::initializer_list<value_type> ilist);

    // Element access
    reference       operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    reference       at(size_type pos);
    const_reference at(size_type pos) const;

    T* data();
    const T* data() const;

    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // Capacity
    bool empty() const noexcept;
    size_type max_size() const noexcept;
    size_type size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();

    // Modifiers
    void clear();
    void push_back(const T& element);
    void pop_back();

private:
    T* m_Buffer {};
    Allocator m_Alloc {};
    size_type m_Size {};
    size_type m_Capacity {};
};

#include "vector.tpp"

#endif