#ifndef BABEL_MUST_HAVE
#define BABEL_MUST_HAVE

#include <cmath>
#include <chrono>
#include <functional>
#include <fstream>
#include <filesystem>
#include <utility>
#include <stdexcept>
#include <variant>
#include "container/list.hpp"
#include "container/dynamic_array.hpp"
#include "concepts/concepts.hpp"
#include <cassert>
#include <queue>
#include <numeric>
#include <complex>
#include <numbers>
#include <list>
#include <random>
#include <thread>

#ifdef _WIN32
    #include <Windows.h>
#endif

namespace babel
{
    static constexpr const double VERSION = 1.13;
    static constexpr const bool COMPILER_IS_64B = sizeof(void*) == 8 ? true : false; //NOLINT
}

namespace _BABEL_PRIVATE_DO_NOT_USE //NOLINT
{


    class _PRIVATE_BABEL //NOLINT
    {
        static constexpr void babel_mult(uint64_t F[2][2], uint64_t M[2][2]) noexcept
        {
            uint64_t x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
            uint64_t y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
            uint64_t z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
            uint64_t w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
            F[0][0] = x;
            F[0][1] = y;
            F[1][0] = z;
            F[1][1] = w;
        }

    public:

        static constexpr void babel_pow(uint64_t F[2][2], unsigned n) noexcept
        {
            if ( n < 2 )
                return;
            babel_pow(F, n >> 1u);
            babel_mult(F, F);
            if ( n % 2 != 0 )
            {
                uint64_t x = F[0][0] + F[0][1];
                uint64_t z = F[1][0] + F[1][1];
                F[0][1] = F[0][0];
                F[0][0] = x;
                F[1][1] = F[1][0];
                F[1][0] = z;
            }
        }
    };
}
#endif