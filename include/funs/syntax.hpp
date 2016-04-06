#ifndef FUNS_SYNTAX_HPP
#define FUNS_SYNTAX_HPP

#include <funs/core.hpp>

namespace funs {

template<template <typename...> class F, typename A, typename Impl>
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
    FunsOps<F, Ret<Fn, A>, Impl> map(Fn f) const
    {
        return Impl::map(_val, f);
    }

    // Apply

    template<typename Fn>
    FunsOps<F, Ret<Fn, A>, Impl> ap(const F<Fn> &ff) const
    {
        return Impl::ap(_val, ff);
    }

    // Monad

    template<typename Fn>
    FunsOps<F, typename Impl::template ElemType<Ret<Fn, A>>, Impl> flatMap(Fn f) const
    {
        return Impl::flatMap(_val, f);
    }
};

template<typename FF, template <typename...> class F, typename A>
FunsOps<F, A, FF> on(const F<A> &fa)
{
    return FunsOps<F, A, FF>(fa);
}

template<template <typename...> class F, typename A>
FunsOps<F, A, DefaultImpl<F>> on(const F<A> &fa)
{
    return FunsOps<F, A, DefaultImpl<F>>(fa);
}

}

#endif  // FUNS_SYNTAX_HPP
