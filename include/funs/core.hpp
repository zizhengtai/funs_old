#ifndef FUNS_CORE_HPP
#define FUNS_CORE_HPP

#include <type_traits>
#include <utility>

namespace funs {

template<typename Fn, typename... Args>
using Ret = typename std::result_of<Fn(Args...)>::type;

template<typename T>
struct Id {
    using type = T;

    const T val;

    // Copy constructors
    Id(const T &x) : val(x) {}
    Id(const Id<T> &x) : val(x.val) {}

    // Move constructors
    Id(T &&x) : val(std::move(x)) {}
    Id(Id<T> &&x) : val(std::move(x.val)) {}

    operator T() const
    {
        return val;
    }
};

template<typename T>
Id<T> makeId(const T &x)
{
    return x;
}

template<typename T>
constexpr auto identity(T &&x) noexcept -> decltype(std::forward<T>(x))
{
    return std::forward<T>(x);
}

template<template <typename...> class F>
struct Impl;

}

#endif  // FUNS_CORE_HPP
