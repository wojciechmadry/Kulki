//
// Created by Wojtek on 19.11.2020.
//

#ifndef KULKI_RANDOM_GENERATOR_HPP
#define KULKI_RANDOM_GENERATOR_HPP

#include "../babel/babel.hpp"
#include <random>
#include <cmath>
#include <algorithm>

class random_generator
{
#if !defined(__32BITVERSION__)
    static std::random_device rd;
#endif
    static std::mt19937 gen;

public:

    random_generator() = default;

    ~random_generator() = default;

    template< typename Vec >
    requires babel::CONCEPTS::IS_CONTAINER<Vec>
    static void random_shuffle(Vec &to_shuffle) noexcept
    {
        std::shuffle(to_shuffle.begin(), to_shuffle.end(), gen);
    }

    [[nodiscard]] static bool generate() noexcept
    {
        return std::uniform_int_distribution<uint8_t>(0, 1)(gen);
    }

    template< typename T = int >
    requires ( std::is_integral_v<T> && !std::is_same_v<std::decay_t<T>, bool> )
    [[nodiscard]] static T generate(const T min, const T max) noexcept
    {
        return std::uniform_int_distribution<T>(min, max)(gen);
    }

    template< typename T = float, uint8_t after_coma = 2 >
    requires(std::is_floating_point_v<T>)
    [[nodiscard]] static T generate(const T min, const T max) noexcept
    {
        return std::uniform_real_distribution<T>(min, max)(gen);
    }
};

// idk why std::random_device doesn't
// work on clang 11.0 32bit.
#if !defined(__32BITVERSION__)
std::random_device random_generator::rd; //NOLINT
std::mt19937  random_generator::gen(random_generator::rd()); //NOLINT
#else
std::mt19937  random_generator::gen(std::chrono::system_clock::now().time_since_epoch().count()); //NOLINT
#endif
#endif //KULKI_RANDOM_GENERATOR_HPP
