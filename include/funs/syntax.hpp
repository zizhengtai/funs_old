#ifndef FUNS_SYNTAX_HPP
#define FUNS_SYNTAX_HPP

#include <funs/core.hpp>

namespace funs {

template<template <typename...> class F, typename A, typename I>
struct FunsOps {
private:
    F<A> _val;

public:
    FunsOps<F, A>(const F<A> &fa) : _val(fa) {}
    FunsOps<F, A>(F<A> &&fa) : _val(std::move(fa)) {}

    F<A> val()
    {
        return std::move(_val);
    }

    // Functor

    template<typename Fn>
    FunsOps<F, Ret<Fn, A>, I> map(Fn f) const
    {
        return I::Functor::map(_val, f);
    }

    // Apply

    template<typename Fn>
    FunsOps<F, Ret<Fn, A>, I> ap(const F<Fn> &ff) const
    {
        return I::Apply::ap(_val, ff);
    }

    // Monad

    template<typename Fn>
    FunsOps<F, typename I::template ElemType<Ret<Fn, A>>, I> flatMap(Fn f) const
    {
        return I::Monad::flatMap(_val, f);
    }

    // Foldable
    
    template<typename B, typename Fn>
    B foldLeft(const B &z, Fn op) const
    {
        return I::Foldable::foldLeft(_val, z, op);
    }

    template<typename B, typename Fn>
    B foldRight(const B &z, Fn op) const
    {
        return I::Foldable::foldRight(_val, z, op);
    }
};

template<typename FF, template <typename...> class F, typename A>
FunsOps<F, A, FF> on(const F<A> &fa)
{
    return FunsOps<F, A, FF>(fa);
}

template<template <typename...> class F, typename A>
FunsOps<F, A, Impl<F>> on(const F<A> &fa)
{
    return FunsOps<F, A, Impl<F>>(fa);
}

}

#endif  // FUNS_SYNTAX_HPP
