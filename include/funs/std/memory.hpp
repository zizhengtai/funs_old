#ifndef FUNS_STD_MEMORY_HPP
#define FUNS_STD_MEMORY_HPP

#include <memory>

#include <funs/monad.hpp>

namespace funs {

template<>
struct Functor<std::shared_ptr> {
    template<typename A>
    using F = std::shared_ptr<A>;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f)
    {
        using B = Ret<Fn, A>;

        return fa == nullptr ? F<B>() : std::make_shared<B>(f(*fa));
    }
};

template<>
struct Apply<std::shared_ptr> : public Functor<std::shared_ptr> {
    template<typename A>
    using F = std::shared_ptr<A>;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        using B = Ret<Fn, A>;

        return ff == nullptr ? F<B>() : map(fa, *ff);
    }
};

template<>
struct Applicative<std::shared_ptr> : public Apply<std::shared_ptr> {
    template<typename A>
    using F = std::shared_ptr<A>;

    template<typename A>
    static F<A> pure(const A &a)
    {
        return std::make_shared<A>(a);
    }
};

template<>
struct Monad<std::shared_ptr> : public Applicative<std::shared_ptr> {
    template<typename A>
    using F = std::shared_ptr<A>;

    template<typename FA>
    using ElemType = typename FA::element_type;

    template<typename A>
    static F<A> flatten(const F<F<A>> &ffa)
    {
        return ffa == nullptr ? F<A>() : *ffa;
    }

    template<typename B, typename A, typename Fn>
    static F<B> flatMap(const F<A> &fa, Fn f)
    {
        return flatten(map(fa, f));
    }
};

}

#endif  // FUNS_STD_MEMORY_HPP
