#ifndef FUNS_SYNTAX_HPP
#define FUNS_SYNTAX_HPP

#include <funs/core.hpp>

namespace funs {

template<template <typename...> class F, typename A, typename I>
struct FunsOps {
private:
    F<A> _val;

public:
    FunsOps<F, A, I>(const F<A> &fa) : _val(fa) {}
    FunsOps<F, A, I>(F<A> &&fa) : _val(std::move(fa)) {}

    F<A> val()
    {
        return std::move(_val);
    }

    // Functor

    template<typename Fn, typename B = Ret<Fn, A>>
    FunsOps<F, B, I> map(Fn f) const
    {
        return I::Functor::template map<A, Fn, B>(_val, f);
    }

    // Apply

    template<typename Fn, typename B = Ret<Fn, A>>
    FunsOps<F, B, I> ap(const F<Fn> &ff) const
    {
        return I::Apply::template ap<A, Fn, B>(_val, ff);
    }

    // Monad

    template<typename Fn, typename B = typename ElemType<Ret<Fn, A>>::type>
    FunsOps<F, B, I> flatMap(Fn f) const
    {
        return I::Monad::template flatMap<A, Fn, B>(_val, f);
    }

    // Foldable
    
    template<typename B, typename Fn>
    B foldLeft(const B &z, Fn op) const
    {
        return I::Foldable::template foldLeft<A, B, Fn>(_val, z, op);
    }

    template<typename B, typename Fn>
    B foldRight(const B &z, Fn op) const
    {
        return I::Foldable::template foldRight<A, B, Fn>(_val, z, op);
    }

    // Traverse
    template<typename Fn,
             typename IG = typename ImplType<Ret<Fn, A>>::type,
             template <typename...> class G = FType<Ret<Fn, A>>::template type,
             typename B = typename ElemType<Ret<Fn, A>>::type>
    FunsOps<G, F<B>, I> traverse(Fn f) const
    {
        return I::Traverse::template traverse<A, Fn, IG, G, B>(_val, f);
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
