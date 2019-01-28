//
// Created by damm1t on 1/28/19.
//

#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <iostream>
#include <type_traits>
#include <string>
#include <cassert>

template<class T>
class optional {
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data;
    bool contains = false;

public:
    optional() = default;

    optional(T const &val) {
        contains = true;
        new(reinterpret_cast<T *>(&data)) T(val);
    }

    optional(optional const &other) {
        if (other.contains)
            new(reinterpret_cast<T *>(&data)) T(*other);
        contains = other.contains;
    }

    optional &operator=(optional const &other) {
        optional tmp(other);
        swap(tmp);
        return *this;
    }

    ~optional() {
        clear();
    }

    explicit operator bool() const {
        return contains;
    }

    void clear() {
        if (contains) {
            contains = false;
            reinterpret_cast<T *>(&data)->~T();
        }
    }

    void swap(optional &other) {
        if (contains && other.contains) {
            std::swap(contains, other.contains);
            std::swap(*reinterpret_cast<T *>(&data), *reinterpret_cast<T *>(&other.data));
        } else if (contains) {
            new(reinterpret_cast<T *>(&other.data)) T(**this);
            this->clear();
            other.contains = true;
        } else if (other.contains) {
            new(reinterpret_cast<T *>(&data)) T(*other);
            other.clear();
            contains = true;
        }
    }


    T &operator*() {
        assert(contains);
        return *reinterpret_cast<T *>(&data);
    }

    T const &operator*() const {
        assert(contains);
        return *reinterpret_cast<T const *>(&data);
    }

    T *operator->() {
        assert(contains);
        return (reinterpret_cast<T *>(&data));
    }

    T const *operator->() const {
        assert(contains);
        return (reinterpret_cast<T const *>(&data));
    }
};

template<typename T>
void swap(optional<T> &a, optional<T> &b) {
    a.swap(b);
}

#endif //OPTIONAL_H
