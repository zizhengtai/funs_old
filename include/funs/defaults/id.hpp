#ifndef FUNS_DEFAULTS_ID_HPP
#define FUNS_DEFAULTS_ID_HPP

#include <functional>
#include <funs/core.hpp>

namespace funs {

template<typename A>
struct FType<Id<A>> {
    template<typename B>
    using type = Id<B>;
};

template<typename A>
struct ElemType<Id<A>> {
    using type = A;
};

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

        template<typename A, typename Fn, typename B = typename ElemType<Ret<Fn, A>>::type>
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
                 typename IG = typename ImplType<Ret<Fn, A>>::type,
                 template <typename...> class G = FType<Ret<Fn, A>>::template type,
                 typename B = typename ElemType<Ret<Fn, A>>::type>
        static G<F<B>> traverse(const F<A> &fa, Fn f)
        {
            return IG::Applicative::map(f(fa.val), Applicative::pure<B>);
        }
    };
};

}

#endif  // FUNS_DEFAULTS_ID_HPP
