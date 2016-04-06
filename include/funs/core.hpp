#ifndef FUNS_CORE_HPP
#define FUNS_CORE_HPP

#include <type_traits>

namespace funs {

template<typename Fn, typename... Args>
using Ret = typename std::result_of<Fn(Args...)>::type;

template<typename T>
struct Id {
    const T value;

    using type = T;

    Id(const T &t) : value(t)
    {
    }

    operator T() const
    {
        return value;
    }
};

}

#endif  // FUNS_CORE_HPP
