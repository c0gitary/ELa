#pragma once

#include <cmath>

namespace ela::op {
    template<class T>
    struct log {
        constexpr T operator()(const T&& right, const T&& left) {
            return static_cast<T>(std::log(left)/std::log(right));
        }
    };

    template<class T>
    struct pow {
        constexpr T operator()(const T&& right, const T&& left) {
            return static_cast<T>(std::pow<T, T>(right ,left));
        }
    };

    template<class T>
    struct round {
        constexpr int operator()(const T&& x) {
            return static_cast<int>(std::round(x));
        }
    };

}

