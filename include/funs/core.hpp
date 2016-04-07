#ifndef FUNS_CORE_HPP
#define FUNS_CORE_HPP

#include <type_traits>
#include <utility>

namespace funs {

// Default implementation for F
template<template <typename...> class F>
struct Impl;
 
namespace detail {

template<typename>
struct _HKT;

template<template <typename...> class F, typename A, typename... Args>
struct _HKT<F<A, Args...>> {
    template<typename... B>
    using Cons = F<B...>;

    using Param = A;
};

template<typename>
struct _ImplType;

template<template <typename...> class F, typename A, typename... Args>
struct _ImplType<F<A, Args...>> {
    using type = Impl<F>;
};

}

// Return type of Fn(Args...)
template<typename Fn, typename... Args>
using Ret = typename std::result_of<Fn(Args...)>::type;

// Trait for higher-kinded types
template<typename FA>
using HKT = detail::_HKT<typename std::decay<FA>::type>;

// Returns Impl<F> given F<A>
template<typename FA>
using ImplType = typename detail::_ImplType<typename std::decay<FA>::type>::type;

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

    template<typename Fn>
    void foreach(Fn f) const
    {
        f(val);
    }
};

template<typename T>
Id<T> makeId(const T &x)
{
    return x;
}

}

#endif  // FUNS_CORE_HPP
