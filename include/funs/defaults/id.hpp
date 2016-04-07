#ifndef FUNS_DEFAULTS_ID_HPP
#define FUNS_DEFAULTS_ID_HPP

#include <funs/core.hpp>

namespace funs {

template<>
struct Impl<Id> {
private:
    template<typename A>
    using F = Id<A>;

public:
    using Functor     = Impl<Id>;
    using Apply       = Impl<Id>;
    using Applicative = Impl<Id>;
    using Monad       = Impl<Id>;

    template<typename FA>
    using ElemType = typename FA::type;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f)
    {
        return f(fa.val);
    }

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        return ff.val(fa.val);
    }

    template<typename A>
    static F<A> pure(const A &x)
    {
        return x;
    }

    template<typename A, typename Fn>
    static F<ElemType<Ret<Fn, A>>> flatMap(const F<A> &fa, Fn f)
    {
        return f(fa.val);
    }
};

}

#endif  // FUNS_DEFAULTS_ID_HPP
