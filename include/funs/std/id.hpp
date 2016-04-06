#ifndef FUNS_STD_ID_HPP
#define FUNS_STD_ID_HPP

#include <funs/monad.hpp>

namespace funs {

template<>
struct Functor<Id> {
    template<typename A>
    using F = Id<A>;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f)
    {
        return f(fa);
    }
};

template<>
struct Apply<Id> : public Functor<Id> {
    template<typename A>
    using F = Id<A>;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        return ff.value(fa.value);
    }
};

template<>
struct Applicative<Id> : public Apply<Id> {
    template<typename A>
    using F = Id<A>;

    template<typename A>
    static F<A> pure(const A &a)
    {
        return a;
    }
};

template<>
struct Monad<Id> : public Applicative<Id> {
    template<typename A>
    using F = Id<A>;

    template<typename FA>
    using ElemType = typename FA::type;

    template<typename A>
    static F<A> flatten(const F<F<A>> &ffa)
    {
        return ffa.value;
    }

    template<typename B, typename A, typename Fn>
    static F<B> flatMap(const F<A> &fa, Fn f)
    {
        return flatten(map(fa, f));
    }
};

}

#endif  // FUNS_STD_ID_HPP
