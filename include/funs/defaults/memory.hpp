#ifndef FUNS_DEFAULTS_MEMORY_HPP
#define FUNS_DEFAULTS_MEMORY_HPP

#include <memory>
#include <funs/core.hpp>

namespace funs {

template<>
struct DefaultImpl<std::shared_ptr> {
private:
    template<typename A>
    using F = std::shared_ptr<A>;

public:
    template<typename FA>
    using ElemType = typename FA::element_type;

    // Functor

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> map(const F<A> &fa, Fn f)
    {
        using B = Ret<Fn, A>;

        return fa == nullptr ? F<B>() : std::make_shared<B>(f(*fa));
    }

    // Apply

    template<typename A, typename Fn>
    static F<Ret<Fn, A>> ap(const F<A> &fa, const F<Fn> &ff)
    {
        using B = Ret<Fn, A>;

        return ff == nullptr ? F<B>() : map(fa, *ff);
    }

    // Applicative

    template<typename A>
    static F<A> pure(const A &a)
    {
        return std::make_shared<A>(a);
    }

    // Monad

    template<typename A, typename Fn>
    static F<ElemType<Ret<Fn, A>>> flatMap(const F<A> &fa, Fn f)
    {
        using B = ElemType<Ret<Fn, A>>;

        return fa == nullptr ? F<B>() : f(*fa);
    }
};

}

#endif  // FUNS_DEFAULTS_MEMORY_HPP
