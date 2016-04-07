#ifndef FUNS_DEFAULTS_LIST_HPP
#define FUNS_DEFAULTS_LIST_HPP

#include <list>
#include <funs/core.hpp>

namespace funs {

template<>
struct Impl<std::list> {
private:
    template<typename A>
    using F = std::list<A>;

public:
    using Functor     = Impl<std::list>;
    using Apply       = Impl<std::list>;
    using Applicative = Impl<std::list>;
    using Monad       = Impl<std::list>;

    template<typename FA>
    using ElemType = typename FA::value_type;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f)
    {
        using B = Ret<Fn, A>;

        F<B> fb;
        for (const auto &a: fa) {
            fb.emplace_back(f(a));
        }

        return fb;
    }

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        using B = Ret<Fn, A>;

        F<B> fb;
        for (const auto &f: ff) {
            for (const auto &a: fa) {
                fb.emplace_back(f(a));
            }
        }

        return fb;
    }

    template<typename A>
    static F<A> pure(const A &x)
    {
        return {x};
    }

    template<typename A, typename Fn>
    static F<ElemType<Ret<Fn, A>>> flatMap(const F<A> &fa, Fn f)
    {
        using B = ElemType<Ret<Fn, A>>;

        F<B> fb;
        for (const auto &a: fa) {
            const auto fa2 = f(a);
            fb.insert(fb.end(), fa2.cbegin(), fa2.cend());
        }

        return fb;
    }
};

}

#endif  // FUNS_DEFAULTS_LIST_HPP
