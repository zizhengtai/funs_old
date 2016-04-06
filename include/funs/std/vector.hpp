#ifndef FUNS_STD_VECTOR_HPP
#define FUNS_STD_VECTOR_HPP

#include <vector>

#include <funs/monad.hpp>

namespace funs {

template<>
struct Functor<std::vector> {
    template<typename A>
    using F = std::vector<A>;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f)
    {
        using B = Ret<Fn, A>;

        F<B> fb;
        fb.reserve(fa.size());
        for (const auto &a: fa) {
            fb.emplace_back(f(a));
        }

        return fb;
    }
};

template<>
struct Apply<std::vector> : public Functor<std::vector> {
    template<typename A>
    using F = std::vector<A>;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        using B = Ret<Fn, A>;

        F<B> fb;
        fb.reserve(fa.size() * ff.size());
        for (const auto &f: ff) {
            for (const auto &a: fa) {
                fb.emplace_back(f(a));
            }
        }

        return fb;
    }
};

template<>
struct Applicative<std::vector> : public Apply<std::vector> {
    template<typename A>
    using F = std::vector<A>;

    template<typename A>
    static F<A> pure(const A &a)
    {
        return {a};
    }
};

template<>
struct Monad<std::vector> : public Applicative<std::vector> {
    template<typename A>
    using F = std::vector<A>;

    template<typename FA>
    using ElemType = typename FA::value_type;

    template<typename A>
    static F<A> flatten(const F<F<A>> &ffa)
    {
        F<A> result;
        for (const auto &fa: ffa) {
            for (const auto &a: fa) {
                result.emplace_back(a);
            }
        }

        return result;
    }

    template<typename B, typename A, typename Fn>
    static F<B> flatMap(const F<A> &fa, Fn f)
    {
        return flatten(map(fa, f));
    }
};

}

#endif  // FUNS_STD_VECTOR_HPP
