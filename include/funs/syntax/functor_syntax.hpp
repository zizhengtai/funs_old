#ifndef FUNS_SYNTAX_FUNCTORSYNTAX_HPP
#define FUNS_SYNTAX_FUNCTORSYNTAX_HPP

#include <funs/functor.hpp>

namespace funs {

template<template <typename...> class F, typename A, typename FF>
struct FunctorOps {
    const F<A> value;

    FunctorOps(const F<A> &fa) : value(fa)
    {
    }

    template<typename Fn>
    FunctorOps<F, Ret<Fn, A>, FF> map(Fn f) const
    {
        return _map(f);
    }

protected:
    template<typename Fn>
    F<Ret<Fn, A>> _map(Fn f) const
    {
        return FF::map(value, f);
    }
};

template<template <typename...> class F, typename A, typename FF = Functor<F>>
FunctorOps<F, A, FF> withFunctor(const F<A> &fa)
{
    return FunctorOps<F, A, FF>(fa);
}

}

#endif  // FUNS_SYNTAX_FUNCTORSYNTAX_HPP
