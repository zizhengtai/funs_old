#ifndef FUNS_SYNTAX_MONADSYNTAX_HPP
#define FUNS_SYNTAX_MONADSYNTAX_HPP

#include <funs/monad.hpp>
#include <funs/syntax/apply_syntax.hpp>

namespace funs {

template<template <typename...> class F, typename A, typename MF>
struct MonadOps : public ApplyOps<F, A, MF> {
    using ApplyOps<F, A, MF>::ApplyOps;
    using ApplyOps<F, A, MF>::value;
    using ApplyOps<F, A, MF>::_map;
    using ApplyOps<F, A, MF>::_ap;

    template<typename Fn>
    MonadOps<F, typename MF::template ElemType<Ret<Fn, A>>, MF> flatMap(Fn f) const
    {
        return _flatMap(f);
    }

    template<typename Fn>
    MonadOps<F, Ret<Fn, A>, MF> map(Fn f) const
    {
        return _map(f);
    }

    template<typename Fn>
    MonadOps<F, Ret<Fn, A>, MF> ap(const F<Fn> &ff) const
    {
        return _ap(ff);
    }

protected:
    template<typename Fn>
    F<typename MF::template ElemType<Ret<Fn, A>>> _flatMap(Fn f) const
    {
        using B = typename MF::template ElemType<Ret<Fn, A>>;

        return MF::template flatMap<B>(value, f);
    }
};

template<template <typename...> class F, typename A, typename MF>
struct NestedMonadOps : public MonadOps<F, F<A>, MF> {
    using MonadOps<F, F<A>, MF>::MonadOps;
    using MonadOps<F, F<A>, MF>::value;
    using MonadOps<F, F<A>, MF>::_map;
    using MonadOps<F, F<A>, MF>::_ap;
    using MonadOps<F, F<A>, MF>::_flatMap;

    MonadOps<F, A, MF> flatten() const
    {
        return MF::flatten(value);
    }
};

template<template <typename...> class F, typename A, typename MF = Monad<F>>
MonadOps<F, A, MF> withM(const F<A> &fa)
{
    return MonadOps<F, A, MF>(fa);
}

template<template <typename...> class F, typename A, typename MF = Monad<F>>
NestedMonadOps<F, A, MF> withM(const F<F<A>> &ffa)
{
    return NestedMonadOps<F, A, MF>(ffa);
}

}

#endif  // FUNS_SYNTAX_MONADSYNTAX_HPP
