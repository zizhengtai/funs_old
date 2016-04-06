#ifndef FUNS_FUNCTOR_HPP
#define FUNS_FUNCTOR_HPP

#include <funs/core.hpp>

namespace funs {

template<template <typename...> class F>
struct Functor {
    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f);
};

}

#endif  // FUNS_FUNCTOR_HPP
