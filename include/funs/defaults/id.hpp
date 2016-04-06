#ifndef FUNS_DEFAULTS_ID_HPP
#define FUNS_DEFAULTS_ID_HPP

#include <funs/core.hpp>

namespace funs {

template<>
struct DefaultImpl<Id> {
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

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        return ff.val(fa.val);
    }

    template<typename A>
    static F<A> pure(const A &a)
    {
        return a;
    }

    template<typename A, typename Fn>
    static F<ElemType<Ret<Fn, A>>> flatMap(const F<A> &fa, Fn f)
    {
        return f(fa.val);
    }
};

}

#endif  // FUNS_DEFAULTS_ID_HPP
