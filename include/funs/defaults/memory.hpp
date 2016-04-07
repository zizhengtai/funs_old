#ifndef FUNS_DEFAULTS_MEMORY_HPP
#define FUNS_DEFAULTS_MEMORY_HPP

#include <memory>
#include <funs/core.hpp>

namespace funs {

template<>
struct Impl<std::shared_ptr> {
private:
    template<typename A>
    using F = std::shared_ptr<A>;

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
            return fa == nullptr ? F<B>() : std::make_shared<B>(f(*fa));
        }

        template<typename A, typename Fn, typename B = Ret<Fn, A>>
        static F<B> ap(const F<A> &fa, const F<Fn> &ff)
        {
            return ff == nullptr ? F<B>() : map(fa, *ff);
        }

        template<typename A>
        static F<A> pure(const A &x)
        {
            return std::make_shared<A>(x);
        }

        template<typename A, typename Fn, typename B = typename HKT<Ret<Fn, A>>::A>
        static F<B> flatMap(const F<A> &fa, Fn f)
        {
            return fa == nullptr ? F<B>() : f(*fa);
        }

        template<typename A>
        static F<A> flatten(const F<F<A>> &ffa)
        {
            return ffa == nullptr ? F<A>() : *ffa;
        }
    };

    struct Traverse {
        template<typename A, typename B, typename Fn>
        static B foldLeft(const F<A> &fa, const B &z, Fn op)
        {
            return fa == nullptr ? z : op(z, *fa);
        }

        template<typename A, typename B, typename Fn>
        static B foldRight(const F<A> &fa, const B &z, Fn op)
        {
            return fa == nullptr ? z : op(*fa, z);
        }

        template<typename A,
                 typename Fn,
                 typename IG = ImplType<Ret<Fn, A>>,
                 template <typename...> class G = HKT<Ret<Fn, A>>::template F,
                 typename B = typename HKT<Ret<Fn, A>>::A>
        static G<F<B>> traverse(const F<A> &fa, Fn f)
        {
            if (fa == nullptr) {
                return IG::Applicative::pure(F<B>());
            } else {
                return IG::Applicative::map(f(*fa), Applicative::pure<B>);
            }
        }
    };
};

}

#endif  // FUNS_DEFAULTS_MEMORY_HPP
