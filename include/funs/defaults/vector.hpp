#ifndef FUNS_DEFAULTS_VECTOR_HPP
#define FUNS_DEFAULTS_VECTOR_HPP

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

    struct Monad {
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

        template<typename A>
        static F<A> pure(const A &x)
        {
            return {x};
        }

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

    struct Foldable {
        template<typename Iter, typename B, typename Fn>
        static B foldLeft(Iter first, Iter last, const B &z, Fn op)
        {
            B b = z;
            while (first != last) {
                b = op(b, *first);
                ++first;
            }
            return b;
        }

        template<typename A, typename B, typename Fn>
        static B foldLeft(const F<A> &fa, const B &z, Fn op)
        {
            return foldLeft(fa.cbegin(), fa.cend(), z, op);
        }

        template<typename RIter, typename B, typename Fn>
        static B foldRight(RIter first, RIter last, const B &z, Fn op)
        {
            B b = z;
            while (first != last) {
                b = op(*first, b);
                ++first;
            }
            return b;
        }

        template<typename A, typename B, typename Fn>
        static B foldRight(const F<A> &fa, const B &z, Fn op)
        {
            return foldRight(fa.rbegin(), fa.rend(), z, op);
        }
    };
};

}

#endif  // FUNS_DEFAULTS_VECTOR_HPP
