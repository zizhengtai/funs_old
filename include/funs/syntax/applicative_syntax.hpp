#ifndef FUNS_SYNTAX_APPLICATIVESYNTAX_HPP
#define FUNS_SYNTAX_APPLICATIVESYNTAX_HPP

#include <funs/applicative.hpp>
#include <funs/syntax/apply_syntax.hpp>

namespace funs {

template<template <typename...> class F, typename A, typename AF>
struct ApplicativeOps {
    const A value;

    ApplicativeOps(const A &a) : value(a)
    {
    }

    F<A> pure() const
    {
        return AF::pure(value);
    }
};

template<template <typename...> class F, typename A, typename AF = Applicative<F>>
ApplicativeOps<F, A, AF> withApplicative(const A &a)
{
    return ApplicativeOps<F, A, AF>(a);
}

}

#endif  // FUNS_SYNTAX_APPLICATIVESYNTAX_HPP
