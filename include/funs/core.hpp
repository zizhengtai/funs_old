#ifndef FUNS_CORE_HPP
#define FUNS_CORE_HPP

#include <type_traits>

namespace funs {

template<typename Fn, typename... Args>
using Ret = typename std::result_of<Fn(Args...)>::type;

template<typename T>
struct Id {
    using type = T;

    const T val;

    // Copy constructors
    Id(const T &value) : val(value) {}
    Id(const Id<T> &that) : val(that.val) {}

    // Move constructors
    Id(T &&value) : val(std::move(value)) {}
    Id(Id<T> &&that) : val(std::move(that.val)) {}

    operator T() const
    {
        return val;
    }
};

template<typename T>
Id<T> makeId(const T &t)
{
    return t;
}

template<template <typename...> class F>
struct Impl;

}

#endif  // FUNS_CORE_HPP
