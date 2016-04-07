# Funs

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)
[![Join the chat at https://gitter.im/ZizhengTai/funs](https://badges.gitter.im/ZizhengTai/funs.svg)](https://gitter.im/ZizhengTai/funs)

Funs is a functional programming library for C++. It is currently only a proof of concept, but is under active development.

## Examples

```cpp
std::vector<int> v1{1, 2, 3};

auto v2 = on(v1)
    .map([](int x) { return x * x; })
    .flatMap([](int x) {
        auto s = std::to_string(x) + "!";
        return std::vector<std::string>{s, s};
    })
    .val();

// v2 == std::vector<std::string>{"1!", "1!", "4!", "4!", "9!", "9!"}
```

## Supported Concepts

* Functor
    * `map`
* Apply
    * `ap`
* Applicative
    * `pure`
* Monad
    * `flatMap`
    * `flatten`
* Foldable
    * `foldLeft`
    * `foldRight`
* Traverse
    * `traverse`

## Default Implementations

* `funs::Id`
* `std::list`
* `std::vector`
* `std::shared_ptr`

## Related Projects

Funs is inspired by [Cats](https://github.com/typelevel/cats).

## License

This project is licensed under the MIT license. See the [LICENSE](./LICENSE) file for details.
