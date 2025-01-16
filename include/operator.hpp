#pragma once

#include <stdexcept>

namespace ela::op {
    template<class Ty>
    struct add {
        constexpr Ty operator()(const Ty& left, const Ty& right) {
            return left + right;
        }
    };

    template<class Ty>
    struct sub {
        constexpr Ty operator()(const Ty& left, const Ty& right) {
            return left - right;
        }
    };

    template<class Ty>
    struct mul {
        constexpr Ty operator()(const Ty& left, const Ty& right) {
            return left * right;
        }
    };

    template<class Ty>
    struct div {
        constexpr Ty operator()(const Ty& left, const Ty& right) {
            if (right != 0)
                return left / right;
            throw std::invalid_argument("Div by zero");
        }
    };

    template<class Ty>
    struct mod {
        constexpr Ty operator()(const Ty& left, const Ty& right) {
            return left % right;
        }
    };

    template<class Ty>
    struct lst {
        constexpr Ty operator()(const Ty& left, const Ty& right) {
            return left < right;
        }
    };

    template<class Ty>
    struct rst {
        constexpr Ty operator()(const Ty& left, const Ty& right) {
            return left > right;
        }
    };

    template<class Ty>
    struct lse {
        constexpr bool operator()(const Ty& left, const Ty& right) {
            return left <= right;
        }
    };

    template<class Ty>
    struct rse {
        constexpr bool operator()(const Ty& left, const Ty& right) {
            return left >= right;
        }
    };

    template<class Ty>
    struct eqy {
        constexpr bool operator()(const Ty& left, const Ty& right) {
            return left == right;
        }
    };

    template<class Ty>
    struct nqy {
        constexpr bool operator()(const Ty& left, const Ty& right) {
            return left != right;
        }
    };

    template<class T, class Op>
    T apply_op(const T& a, const T& b, Op op) {
        return op(a, b);
    }

}

