#ifndef BABEL_TIME
#define BABEL_TIME

#include "must_have.hpp"

namespace babel::TIME{

    class timer
    {
    public:
        timer() noexcept
        {
            start();
        }

        /**
*  @brief  Start counting time.
*  @return No return
*/
        void start() noexcept
        {
            time = std::chrono::high_resolution_clock::now();
        }

        /**
*  @return Get time in seconds
*/
        [[nodiscard]]long double get_time() const noexcept
        {
            return std::chrono::duration<long double>(std::chrono::high_resolution_clock::now() - ( time )).count();
        }


        /**
*  @return Get time in nanoseconds
*/
        [[nodiscard]]long long get_time_ns() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now() - ( time )).count();
        }

        /**
*  @return Get time in milliseconds
*/
        [[nodiscard]]long long get_time_mili() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::high_resolution_clock::now() - ( time )).count();
        }

        /**
*  @return Get time in microseconds
*/
        [[nodiscard]]long long get_time_micro() const noexcept
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - ( time )).count();
        }

    private:
        std::chrono::high_resolution_clock::time_point time;
    };


    /**
*  @brief  Call function N times and measure time.
*  @param  times How many times you want call function
*  @param  f Function to call
*  @param  arg argument to function, f(arg...)
*  @return Return measured time in seconds
*/
    template< typename Func, typename ... args >
    long double measure_time(const size_t times, Func f, args &&...  arg)
    {
        timer T;
        for ( size_t i = 0 ; i < times ; ++i )
            f(std::forward<args>(arg)...);
        return T.get_time();
    }

    namespace CONVERT{
        namespace NS{
            constexpr double to_micro(const uint64_t nano) noexcept
            {
                return static_cast<double>(nano) / 1000.0;
            }

            constexpr double to_mili(const uint64_t nano) noexcept
            {
                return static_cast<double>(nano) / 1e+6;
            }

            constexpr double to_sec(const uint64_t nano) noexcept
            {
                return static_cast<double>(nano) / 1e+9;
            }

            constexpr double to_min(const uint64_t nano) noexcept
            {
                return static_cast<double>(nano) / 6e+10;
            }

            constexpr double to_hour(const uint64_t nano) noexcept
            {
                return static_cast<double>(nano) / 3.6e+12;
            }
        }
        namespace MICRO{
            constexpr uint64_t to_ns(const double micro) noexcept
            {
                return static_cast<uint64_t>(micro * 1000.0);
            }

            constexpr double to_mili(const double micro) noexcept
            {
                return micro / 1000.0;
            }

            constexpr double to_sec(const double micro) noexcept
            {
                return micro / 1e+6;
            }

            constexpr double to_min(const double micro) noexcept
            {
                return micro / 6e+7;
            }

            constexpr double to_hour(const double micro) noexcept
            {
                return micro / 3.6e+9;
            }

            constexpr double to_day(const double micro) noexcept
            {
                return micro / 8.64e+10;
            }
        }
        namespace MILI{
            constexpr uint64_t to_nano(const double mili) noexcept
            {
                return static_cast<uint64_t>(mili * 1e+6);
            }

            constexpr double to_micro(const double mili) noexcept
            {
                return mili * 1000.0;
            }

            constexpr double to_sec(const double mili) noexcept
            {
                return mili / 1000.0;
            }

            constexpr double to_min(const double mili) noexcept
            {
                return mili / 60000.0;
            }

            constexpr double to_hour(const double mili) noexcept
            {
                return mili / 3.6e+6;
            }

            constexpr double to_day(const double mili) noexcept
            {
                return mili / 8.64e+7;
            }

            constexpr double to_month(const double mili) noexcept
            {
                return mili / 2.628e+9;
            }
        }
        namespace SECOND{
            constexpr uint64_t to_ns(const double sec) noexcept
            {
                return static_cast<uint64_t>(sec * 1e+9);
            }

            constexpr double to_micro(const double sec) noexcept
            {
                return sec * 1e+6;
            }

            constexpr double to_mili(const double sec) noexcept
            {
                return sec * 1000.0;
            }

            constexpr double to_min(const double sec) noexcept
            {
                return sec / 60.0;
            }

            constexpr double to_hour(const double sec) noexcept
            {
                return sec / 3600.0;
            }

            constexpr double to_day(const double sec) noexcept
            {
                return sec / 86400.0;
            }

            constexpr double to_month(const double sec) noexcept
            {
                return sec / 2.628e+6;
            }

            constexpr double to_year(const double sec) noexcept
            {
                return sec / 3.154e+7;
            }
        }
        namespace MIN{
            constexpr uint64_t to_ns(const double min) noexcept
            {
                return static_cast<uint64_t>(min * 6e+10);
            }

            constexpr double to_micro(const double min) noexcept
            {
                return min * 6e+7;
            }

            constexpr double to_mili(const double min) noexcept
            {
                return min * 60000.0;
            }

            constexpr double to_sec(const double min) noexcept
            {
                return min * 60.0;
            }

            constexpr double to_hour(const double min) noexcept
            {
                return min / 60.0;
            }

            constexpr double to_day(const double min) noexcept
            {
                return min / 1440.0;
            }

            constexpr double to_month(const double min) noexcept
            {
                return min / 43800.0;
            }

            constexpr double to_year(const double min) noexcept
            {
                return min / 525600.0;
            }

        }
        namespace HOUR{
            constexpr uint64_t to_ns(const double hour) noexcept
            {
                return static_cast<uint64_t>(hour * 3.6e+12);
            }

            constexpr double to_micro(const double hour) noexcept
            {
                return hour * 3.6e+9;
            }

            constexpr double to_mili(const double hour) noexcept
            {
                return hour * 3.6e+6;
            }

            constexpr double to_sec(const double hour) noexcept
            {
                return hour * 3600.0;
            }

            constexpr double to_min(const double hour) noexcept
            {
                return hour * 60.0;
            }

            constexpr double to_day(const double hour) noexcept
            {
                return hour / 24.0;
            }

            constexpr double to_month(const double hour) noexcept
            {
                return hour / 730.0;
            }

            constexpr double to_year(const double hour) noexcept
            {
                return hour / 8760.0;
            }

            constexpr double to_decade(const double hour) noexcept
            {
                return hour / 87600.0;
            }

            constexpr double to_century(const double hour) noexcept
            {
                return hour / 876000.0;
            }
        }
        namespace DAY{
            constexpr double to_sec(const double day) noexcept
            {
                return day * 86400.0;
            }

            constexpr double to_min(const double day) noexcept
            {
                return day * 1440.0;
            }

            constexpr double to_hour(const double day) noexcept
            {
                return day * 24.0;
            }

            constexpr double to_week(const double day) noexcept
            {
                return day / 7.0;
            }

            constexpr double to_month(const double day) noexcept
            {
                return day / 30.417;
            }

            constexpr double to_year(const double day) noexcept
            {
                return day / 365.0;
            }

            constexpr double to_decade(const double day) noexcept
            {
                return day / 3650.0;
            }

            constexpr double to_century(const double day) noexcept
            {
                return day / 36500.0;
            }


        }
    }
}

#endif