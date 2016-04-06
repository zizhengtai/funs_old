#ifndef FUNS_DEFAULTS_LIST_HPP
#define FUNS_DEFAULTS_LIST_HPP

#include <list>
#include <funs/core.hpp>

namespace funs {

template<>
struct Functor<std::list> {
private:
    template<typename A>
    using F = std::list<A>;

public:
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
};

template<>
struct Apply<std::list> : Functor<std::list> {
private:
    template<typename A>
    using F = std::list<A>;

public:
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
};

template<>
struct Applicative<std::list> : Apply<std::list> {
private:
    template<typename A>
    using F = std::list<A>;

public:
    template<typename A>
    static F<A> pure(const A &a)
    {
        return {a};
    }
};

template<>
struct Monad<std::list> : Applicative<std::list> {
private:
    template<typename A>
    using F = std::list<A>;

public:
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

template<>
struct Impl<std::list> : Monad<std::list> {
};

}

#endif  // FUNS_DEFAULTS_LIST_HPP
