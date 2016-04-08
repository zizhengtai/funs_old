#ifndef FUNS_DEFAULTS_VECTOR_HPP
#define FUNS_DEFAULTS_VECTOR_HPP

#include <iostream>
#include <vector>
#include <funs/core.hpp>

namespace funs {

template<>
struct Impl<std::vector> {
private:
    template<typename A>
    using F = std::vector<A>;

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
            F<B> fb;
            fb.reserve(fa.size());
            for (const auto &a: fa) {
                fb.emplace_back(f(a));
            }
            return fb;
        }

        template<typename A, typename Fn, typename B = Ret<Fn, A>>
        static F<B> ap(const F<A> &fa, const F<Fn> &ff)
        {
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

        template<typename A, typename Fn, typename B = typename HKT<Ret<Fn, A>>::Param>
        static F<B> flatMap(const F<A> &fa, Fn f)
        {
            F<B> fb;
            for (const auto &a: fa) {
                const auto fb2 = f(a);
                fb.insert(fb.end(), fb2.cbegin(), fb2.cend());
            }
            return fb;
        }

        template<typename A, typename B, typename Fn, typename C = Ret<Fn, A, B>>
        static F<C> map2(const F<A> &fa, const F<B> &fb, Fn f)
        {
            return flatMap(fa, [&fb, &f](const A &a) {
                return map(fb, [&a, &f](const B &b) {
                    return f(a, b);
                });
            });
        }
    };

    struct Traverse {
        template<typename Iter, typename B, typename Fn>
        static B foldLeft(Iter first, Iter last, const B &z, Fn op)
        {
            if (first == last) {
                return z;
            }
            return foldLeft(first + 1, last, op(z, *first), op);
        }

        template<typename A, typename B, typename Fn>
        static B foldLeft(const F<A> &fa, const B &z, Fn op)
        {
            return foldLeft(fa.cbegin(), fa.cend(), z, op);
        }

        template<typename RIter, typename B, typename Fn>
        static B foldRight(RIter first, RIter last, const B &z, Fn op)
        {
            if (first == last) {
                return z;
            }
            return foldRight(first + 1, last, op(*first, z), op);
        }

        template<typename A, typename B, typename Fn>
        static B foldRight(const F<A> &fa, const B &z, Fn op)
        {
            return foldRight(fa.rbegin(), fa.rend(), z, op);
        }

        template<typename A,
                 typename Fn,
                 typename IG = ImplType<Ret<Fn, A>>,
                 template <typename...> class G = HKT<Ret<Fn, A>>::template Cons,
                 typename B = typename HKT<Ret<Fn, A>>::Param>
        static G<F<B>> traverse(const F<A> &fa, Fn f)
        {
            return foldLeft(fa, IG::Applicative::pure(F<B>()), [&f](const G<F<B>> &buf, const A &a) {
                return IG::Apply::map2(buf, f(a), [](const F<B> &fb, const B &b) {
                    F<B> fb2 = fb;
                    fb2.emplace_back(b);
                    return fb2;
                });
            });
        }
    };
};

}

#endif  // FUNS_DEFAULTS_VECTOR_HPP
