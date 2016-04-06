#ifndef FUNS_APPLICATIVE_HPP
#define FUNS_APPLICATIVE_HPP

#include <funs/apply.hpp>

namespace funs {

template<template <typename...> class F>
struct Applicative : public Apply<F> {
    template<typename A>
    static F<A> pure(const A &a);
};

}

#endif  // FUNS_APPLICATIVE_HPP
