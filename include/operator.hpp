#pragma once

#include <random>
#include <cmath>

namespace ela::op {
    template<class T>
    struct log {
        constexpr T operator()(const T right, const T left) {
            return static_cast<T>(std::log(left)/std::log(right));
        }
    };

    template<class T>
    struct pow {
        constexpr T operator()(const T right, const T left) {
            return static_cast<T>(std::pow<T, T>(right ,left));
        }
    };

    template<class T>
    struct rand {
        T operator()(const T low, const T high) {
            static std::random_device __rd;
            static std::mt19937 __genRandomNumber(__rd());
            if constexpr (std::is_integral_v<T>){
                std::uniform_int_distribution<T> __dist(low, high);
                return __dist(__genRandomNumber);
            } 
            else if constexpr (std::is_floating_point_v<T>){
                std::uniform_real_distribution<T> __dist(low, high);
                return __dist(__genRandomNumber);
            }
            return 0;
        }
    };


    template<class T>
    struct factorial {
        constexpr int operator()(const T x) {
            return (x <= 1) ? 1 : x * (*this)(x - 1);        
        }
    };
    
    template<class T>
    struct sqrt {
        constexpr T operator()(const T x) {
            return static_cast<T>(std::sqrt(x));
        }
    };

    template<class T>
    struct abs {
        constexpr T operator()(const T x) {
            return static_cast<T>(std::abs(x));
        }
    };

    template<class T>
    struct exp {
        constexpr T operator()(const T x) {
            return static_cast<T>(std::exp(x));
        }
    };

    // template<class T>
    // struct dec_to_bin {
    //     std::string opearator()
    // }

}

