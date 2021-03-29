#ifndef BABEL_TIME
#define BABEL_TIME

#include "must_have.hpp"

namespace babel::TIME {

    class timer
    {
    public:
        timer() noexcept
        {
            start();
        }

        void start() noexcept
        {
            time = std::chrono::high_resolution_clock::now();
        }

        [[nodiscard]]long double get_time() const noexcept
        {
            return std::chrono::duration<long double>(std::chrono::high_resolution_clock::now() - (time)).count();
        }

        [[nodiscard]]long long get_time_ns() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - (time)).count();
        }

        [[nodiscard]]long long get_time_mili() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - (time)).count();
        }

        [[nodiscard]]long long get_time_micro() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - (time)).count();
        }

    private:
        std::chrono::high_resolution_clock::time_point time;
    };


    template<typename Func, typename ... args>
    long double measure_time(const size_t times, Func f, args && ...  arg)
    {
        timer T;
        for (size_t i = 0; i < times; ++i)
            f(std::forward<args>(arg)...);
        return T.get_time();
    }

}

#endif