#ifndef FUNS_MONAD_HPP
#define FUNS_MONAD_HPP

#include <funs/applicative.hpp>

namespace funs {

template<template <typename...> class F>
struct Monad : public Applicative<F> {
    template<typename FA>
    using ElemType = std::nullptr_t;

    template<typename A>
    static F<A> flatten(const F<F<A>> &ffa);

    template<typename B, typename A, typename Fn>
    static F<B> flatMap(const F<A> &fa, Fn f);
};

}

#endif  // FUNS_MONAD_HPP
