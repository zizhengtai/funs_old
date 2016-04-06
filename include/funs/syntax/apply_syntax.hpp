#ifndef FUNS_SYNTAX_APPLYSYNTAX_HPP
#define FUNS_SYNTAX_APPLYSYNTAX_HPP

#include <funs/apply.hpp>
#include <funs/syntax/functor_syntax.hpp>

namespace funs {

template<template <typename...> class F, typename A, typename AF>
struct ApplyOps : public FunctorOps<F, A, AF> {
    using FunctorOps<F, A, AF>::FunctorOps;
    using FunctorOps<F, A, AF>::value;
    using FunctorOps<F, A, AF>::_map;

    template<typename Fn>
    ApplyOps<F, Ret<Fn, A>, AF> ap(const F<Fn> &ff) const
    {
        return _ap(ff);
    }

    template<typename Fn>
    ApplyOps<F, Ret<Fn, A>, AF> map(Fn f) const
    {
        return _map(f);
    }

protected:
    template<typename Fn>
    F<Ret<Fn, A>> _ap(const F<Fn> &ff) const
    {
        return AF::ap(value, ff);
    }
};

template<template <typename...> class F, typename A, typename AF = Apply<F>>
ApplyOps<F, A, AF> withApply(const F<A> &fa)
{
    return ApplyOps<F, A, AF>(fa);
}

}

#endif  // FUNS_SYNTAX_APPLYSYNTAX_HPP
