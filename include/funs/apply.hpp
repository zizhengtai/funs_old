#ifndef FUNS_APPLY_HPP
#define FUNS_APPLY_HPP

#include <funs/functor.hpp>

namespace funs {

template<template <typename...> class F>
struct Apply : public Functor<F> {
    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff);
};

}

#endif  // FUNS_APPLY_HPP
