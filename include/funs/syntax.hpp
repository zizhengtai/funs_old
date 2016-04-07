#ifndef FUNS_SYNTAX_HPP
#define FUNS_SYNTAX_HPP

#include <funs/core.hpp>

namespace funs {

template<typename FA, typename I,
         template <typename...> class F = HKT<FA>::template Cons,
         typename A = typename HKT<FA>::Param>
struct FunsOps {
private:
    FA _val;

public:
    FunsOps<FA, I, F, A>(FA &&fa) : _val(std::forward<FA>(fa)) {}

    FA val()
    {
        return std::forward<FA>(_val);
    }

    // Functor

    template<typename Fn, typename B = Ret<Fn, A>>
    FunsOps<F<B>, I> map(Fn f) const
    {
        return I::Functor::template map<A, Fn, B>(_val, f);
    }

    // Apply

    template<typename Fn, typename B = Ret<Fn, A>>
    FunsOps<F<B>, I> ap(const F<Fn> &ff) const
    {
        return I::Apply::template ap<A, Fn, B>(_val, ff);
    }

    // Monad

    template<typename Fn, typename B = typename HKT<Ret<Fn, A>>::Param>
    FunsOps<F<B>, I> flatMap(Fn f) const
    {
        return I::Monad::template flatMap<A, Fn, B>(_val, f);
    }

    // Foldable
    
    template<typename B, typename Fn>
    B foldLeft(const B &z, Fn op) const
    {
        return I::Foldable::template foldLeft<A, B, Fn>(_val, z, op);
    }

    template<typename B, typename Fn>
    B foldRight(const B &z, Fn op) const
    {
        return I::Foldable::template foldRight<A, B, Fn>(_val, z, op);
    }

    // Traverse
    template<typename Fn,
             typename IG = ImplType<Ret<Fn, A>>,
             template <typename...> class G = HKT<Ret<Fn, A>>::template Cons,
             typename B = typename HKT<Ret<Fn, A>>::Param>
    FunsOps<G<F<B>>, I> traverse(Fn f) const
    {
        return I::Traverse::template traverse<A, Fn, IG, G, B>(_val, f);
    }
};

template<typename FA>
FunsOps<FA, ImplType<FA>> on(FA &&fa)
{
    return FunsOps<FA, ImplType<FA>>(std::forward<FA>(fa));
}

}

#endif  // FUNS_SYNTAX_HPP
