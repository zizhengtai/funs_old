#ifndef FUNS_DEFAULTS_MEMORY_HPP
#define FUNS_DEFAULTS_MEMORY_HPP

#include <memory>
#include <funs/core.hpp>

namespace funs {

template<>
struct Functor<std::shared_ptr> {
private:
    template<typename A>
    using F = std::shared_ptr<A>;

public:
    template<typename FA>
    using ElemType = typename FA::element_type;

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f)
    {
        using B = Ret<Fn, A>;

        return fa == nullptr ? F<B>() : std::make_shared<B>(f(*fa));
    }
};

template<>
struct Apply<std::shared_ptr> : Functor<std::shared_ptr> {
private:
    template<typename A>
    using F = std::shared_ptr<A>;

public:
    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        using B = Ret<Fn, A>;

        return ff == nullptr ? F<B>() : map(fa, *ff);
    }
};

template<>
struct Applicative<std::shared_ptr> : Apply<std::shared_ptr> {
private:
    template<typename A>
    using F = std::shared_ptr<A>;

public:
    template<typename A>
    static F<A> pure(const A &a)
    {
        return std::make_shared<A>(a);
    }
};

template<>
struct Monad<std::shared_ptr> : Applicative<std::shared_ptr> {
private:
    template<typename A>
    using F = std::shared_ptr<A>;

public:
    template<typename A, typename Fn>
    static F<ElemType<Ret<Fn, A>>> flatMap(const F<A> &fa, Fn f)
    {
        using B = ElemType<Ret<Fn, A>>;

        return fa == nullptr ? F<B>() : f(*fa);
    }
};

template<>
struct Impl<std::shared_ptr> : Monad<std::shared_ptr> {
};

}

#endif  // FUNS_DEFAULTS_MEMORY_HPP
