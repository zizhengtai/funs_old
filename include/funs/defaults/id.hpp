#ifndef FUNS_DEFAULTS_ID_HPP
#define FUNS_DEFAULTS_ID_HPP

#include <functional>
#include <funs/core.hpp>

namespace funs {

template<>
struct Impl<Id> {
private:
    template<typename A>
    using F = Id<A>;

public:
    struct Monad;
    using Functor     = Monad;
    using Apply       = Monad;
    using Applicative = Monad;

    struct Traverse;
    using Foldable = Traverse;

    struct Monad {
        template<typename A, typename Fn, typename B = Ret<Fn, A>>
        static F<B> map(const F<A> &fa, Fn f)
        {
            return f(fa.val);
        }

        template<typename A, typename Fn, typename B = Ret<Fn, A>>
        static F<B> ap(const F<A> &fa, const F<Fn> &ff)
        {
            return ff.val(fa.val);
        }

        template<typename A>
        static F<A> pure(const A &x)
        {
            return x;
        }

        template<typename A, typename Fn, typename B = typename HKT<Ret<Fn, A>>::Param>
        static F<B> flatMap(const F<A> &fa, Fn f)
        {
            return f(fa.val);
        }

        template<typename A>
        static F<A> flatten(const F<F<A>> &ffa)
        {
            return ffa.val;
        }
    };

    struct Traverse {
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

        template<typename A,
                 typename Fn,
                 typename IG = ImplType<Ret<Fn, A>>,
                 template <typename...> class G = HKT<Ret<Fn, A>>::template Cons,
                 typename B = typename HKT<Ret<Fn, A>>::Param>
        static G<F<B>> traverse(const F<A> &fa, Fn f)
        {
            return IG::Applicative::map(f(fa.val), Applicative::pure<B>);
        }

        template<typename A,
                 template <typename...> class G,
                 typename IG = Impl<G>>
        static G<F<A>> sequence(const F<G<A>> &fga)
        {
            const auto identity = [](const G<A> &ga) { return ga; };
            return traverse<A, decltype(identity), IG>(fga, identity);
        }
    };
};

}

#endif  // FUNS_DEFAULTS_ID_HPP
