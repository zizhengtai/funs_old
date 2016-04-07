#ifndef FUNS_CORE_HPP
#define FUNS_CORE_HPP

#include <type_traits>
#include <utility>

namespace funs {

template<typename Fn, typename... Args>
using Ret = typename std::result_of<Fn(Args...)>::type;

template<typename FA>
struct FType;

template<template <typename...> class F, typename... A>
struct FType<F<A...>> {
    template<typename... B>
    using type = F<B...>;
};

template<typename FA>
struct _ElemType;

template<template <typename...> class F, typename A, typename... B>
struct _ElemType<F<A, B...>> {
    using type = A;
};

template<typename FA>
using ElemType = typename _ElemType<FA>::type;

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

template<typename T>
constexpr auto identity(T &&x) noexcept -> decltype(std::forward<T>(x))
{
    return std::forward<T>(x);
}

template<template <typename...> class F>
struct Impl;

template<typename FA>
struct _ImplType;

template<template <typename...> class F, typename... A>
struct _ImplType<F<A...>> {
    using type = Impl<F>;
};

template<typename FA>
using ImplType = typename _ImplType<FA>::type;

}

#endif  // FUNS_CORE_HPP
