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
    template<typename FA>
    using ElemType = typename FA::type;

    struct Monad;
    using Functor     = Monad;
    using Apply       = Monad;
    using Applicative = Monad;

    struct Monad {
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

    struct Foldable {
        template<typename A, typename B, typename Fn>
        static B foldLeft(const F<A> &fa, const B &z, Fn op)
        {
            return op(z, fa.val);
        }

        template<typename A, typename B, typename Fn>
        static B foldRight(const F<A> &fa, const B &z, Fn op)
        {
            return op(fa.val, z);
        }
    };
};

}

#endif  // FUNS_DEFAULTS_ID_HPP
