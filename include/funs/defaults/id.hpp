#ifndef FUNS_DEFAULTS_ID_HPP
#define FUNS_DEFAULTS_ID_HPP

#include <funs/core.hpp>

namespace funs {

template<>
struct Functor<Id> {
private:
    template<typename A>
    using F = Id<A>;

public:
    template<typename FA>
    using ElemType = typename FA::type;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f)
    {
        return f(fa.val);
    }
};

template<>
struct Apply<Id> : Functor<Id> {
private:
    template<typename A>
    using F = Id<A>;

public:
    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        return ff.val(fa.val);
    }
};

template<>
struct Applicative<Id> : Apply<Id> {
private:
    template<typename A>
    using F = Id<A>;

public:
    template<typename A>
    static F<A> pure(const A &x)
    {
        return x;
    }
};

template<>
struct Monad<Id> : Applicative<Id> {
private:
    template<typename A>
    using F = Id<A>;

public:
    using Applicative<Id>::ElemType;

    template<typename A, typename Fn>
    static F<ElemType<Ret<Fn, A>>> flatMap(const F<A> &fa, Fn f)
    {
        return f(fa.val);
    }
};

template<>
struct Impl<Id> : Monad<Id> {
};

}

#endif  // FUNS_DEFAULTS_ID_HPP
