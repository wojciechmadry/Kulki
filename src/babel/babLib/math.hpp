#ifndef babel_MATH
#define babel_MATH

#include "variadic.hpp"

namespace babel::MATH{
    namespace DERIVATIVE{
        namespace FIRST{

            template< typename Function, typename TYPE = double >
            auto by_definiton(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto { return ( func(x + h) - func(x) ) / h; };
            }

            template< typename Function, typename TYPE = double >
            auto three_point(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto { return ( func(x + h) - func(x - h) ) / ( 2.0 * h ); };
            }

            template< typename Function, typename TYPE = double >
            auto five_point(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( -func(x + 2.0 * h) + 8 * func(x + h) - 8.0 * func(x - h) + func(x - 2.0 * h) ) /
                           ( 12.0 * h );
                };
            }

            template< typename Function, typename TYPE = double >
            auto forward(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( -3.0 * func(x) + 4.0 * func(x + h) - func(x + 2.0 * h) ) / ( 2.0 * h );
                };
            }

            template< typename Function, typename TYPE = double >
            auto central(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto { return ( func(x + h) - func(x - h) ) / ( 2.0 * h ); };
            }

            template< typename Function, typename TYPE = double >
            auto backward(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( func(x - 2.0 * h) - 4.0 * func(x - h) + 3.0 * func(x) ) / ( 2.0 * h );
                };
            }
        }
        namespace SECOND{
            template< typename Function, typename TYPE = double >
            auto three_point(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( func(x + h) - 2.0 * func(x) + func(x - h) ) / ( std::pow(h, 2.0) );
                };
            }

            template< typename Function, typename TYPE = double >
            auto five_point(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( -func(x + 2.0 * h) + 16.0 * func(x + h) - 30.0 * func(x) + 16.0 * func(x - h) -
                             func(x - 2.0 * h) ) / ( 12.0 * std::pow(h, 2.0) );
                };
            }
        }
    }

    namespace CONSTANT{

        /**
        *  @brief PI value convert to Type
        */
        template< typename Type >
        constexpr Type PI = static_cast<Type>(3.141592653589793238462643383279502884197169399375105);

        /**
        *  @brief E value convert to Type
        */
        template< typename Type >
        constexpr Type E = static_cast<Type>(2.71828182845904523536028747135266249775724709369995);

        /**
         *  @brief Square root of two convert to Type
         */
        template< typename Type >
        constexpr Type sqrt_2 = static_cast<Type>(1.41421356237309504880168872420969807856967187537694);

        /**
         *  @brief Square root of three convert to Type
         */
        template< typename Type >
        constexpr Type sqrt_3 = static_cast<Type>(1.73205080756887729352744634150587236694280525381038);

        /**
         *  @brief Planck constant convert to Type
         */
        template< typename Type >
        constexpr Type PLANCK = static_cast<Type>(6.62607004e-34);

        /**
         *  @brief Golden ratio convert to Type
         */
        template< typename Type >
        constexpr Type golden_ratio = static_cast<Type>(1.61803398874989484820);

    }

    /**
    *  @brief  Convert negative number to positive.
    *  @param  v Number can be positive or negative.
    * Must be arithmetic
    *  @return Return absolute value of number
    */
    template< typename T >
    requires babel::CONCEPTS::IS_SIGNED<T>
    constexpr inline T abs(const T v) noexcept
    {
        return ( v >= 0 ) ? v : -v;
    }


    /**
    *  @brief  Compare two number
    *  @param  value1 First number
    *  @param  value2 Second number
    *  @return Return greater number
    */
    template< typename T, typename T2 >
    requires ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<T, T2> && !babel::CONCEPTS::IS_CONTAINER<T> &&
               !babel::CONCEPTS::IS_CONTAINER<T2> )
    constexpr inline auto max(const T value1, const T2 value2) noexcept
    {
        return value1 > value2 ? value1 : value2;
    }

    /**
*  @brief  Compare more than two number (its the worst method)
*  @param  value1 First number
*  @param  value2 Second number
*  @param  arg    all other number
*  @return Return the largest number
*/
    template< typename T, typename ... Args >
    requires ( !babel::CONCEPTS::IS_CONTAINER<T> )
    constexpr T max(T value1, T value2, Args... arg) noexcept
    {
        if ( value1 < value2 )
            value1 = value2;
        babel::VARIADIC::holder<T> _hold(arg...);
        const auto &vec = _hold.get();
        auto begin = std::begin(vec);
        auto end = std::end(vec);
        for ( ; begin != end ; ++begin )
            if ( *begin > value1 )
                value1 = *begin;
        return value1;
    }

    /**
    *  @brief  Compare two number
    *  @param  value1 First number
    *  @param  value2 Second number
    *  @return Return lowest number
    */
    template< typename T, typename T2 >
    requires babel::CONCEPTS::IS_SAME_CONVERTIBLE<T, T2>
    constexpr inline auto min(const T value1, const T2 value2) noexcept
    {
        return value1 < value2 ? value1 : value2;
    }

    /**
*  @brief  Compare more than two number (its the worst method)
*  @param  value1 First number
*  @param  value2 Second number
*  @param  arg    all other number
*  @return Return the lowest number
*/
    template< typename T, typename ... Args >
    constexpr T min(T value1, T value2, Args... arg) noexcept
    {
        if ( value1 > value2 )
            value1 = value2;
        babel::VARIADIC::holder<T> _hold(arg...);
        const auto &vec = _hold.get();
        auto begin = std::begin(vec);
        auto end = std::end(vec);
        for ( ; begin != end ; ++begin )
            if ( *begin < value1 )
                value1 = *begin;
        return value1;
    }

    /**
    *  @brief  Compare few number
    *  @param   init_list Initializer list of numbers
    *  @return Return the largest number
    */
    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr U max(const T &Container) noexcept
    {
        if ( Container.size() == 0 )
            return { };

        auto _it = std::begin(Container);
        auto end = std::end(Container);
        U MAX = *_it;
        ++_it;
        for ( ; _it != end ; ++_it )
            MAX = max(MAX, *_it);
        return MAX;
    }

    /**
   *  @brief  Compare few number
   *  @param   init_list Initializer list of numbers
   *  @return Return the smallest number
   */
    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr U min(const T &Container) noexcept
    {
        if ( Container.size() == 0 )
            return { };
        auto _it = std::begin(Container);
        auto end = std::end(Container);
        U MIN = *_it;
        ++_it;
        for ( ; _it != end ; ++_it )
            MIN = min(MIN, *_it);
        return MIN;

    }

    /**
   *  @brief  Check if number is negative
   *  @param   val A number
   *  @return If val is negative return 1 otherwise return 0
   */
    template< typename T >
    constexpr inline bool is_neg(const T val) noexcept
    {
        return val < 0 ? 1 : 0;
    }

    /**
    *  @brief  ex.: n = 3, return : 1 * 2 * 3
    *  @param   n Factorial of n
    *  @return Factorial N
    */
    template< uint64_t N >
    consteval uint64_t factorial() noexcept
    {
        uint64_t res = 1;
        for ( size_t i = 2 ; i <= N ; ++i )
            res *= i;
        return res;
    }

    /**
*  @brief  ex.: n = 3, return : 1 * 2 * 3
*  @param   n Factorial of n
*  @return Factorial N
*/

    constexpr uint64_t factorial(size_t N) noexcept
    {
        uint64_t res = 1;
        while ( N > 1 )
        {
            res *= N;
            --N;
        }

        return res;
    }

    constexpr double binomial_coefficient(const uint64_t N, const uint64_t K)
    {
        if ( K > N )
            throw std::out_of_range("K > N.");
        return static_cast<double>(factorial(N)) / static_cast<double>(factorial(K) * factorial(N - K));
    }

    template< uint64_t N, uint64_t K >
    consteval double binomial_coefficient() noexcept
    {
        if ( K > N )
            throw std::out_of_range("K > N.");
        return static_cast<double>(factorial<N>()) / static_cast<double>(factorial<K>() * factorial<N - K>());
    }

    /**
   *  @param   n Fibonacci number
   *  @return Fibonacci N
   */
    constexpr uint64_t fib(unsigned n) noexcept
    {
        uint64_t F[2][2] = {{1, 1},
                            {1, 0}};
        if ( n == 0 )
            return 0;
        _BABEL_PRIVATE_DO_NOT_USE::_PRIVATE_BABEL::babel_pow(F, n - 1);
        return F[0][0];
    }

    /**
   *  @brief  Return delta of : ax^2 + bx + c = 0
   *  @param   a Param ax^2
   *  @param   b Param bx
   *  @param   c param c
   *  @return b^2 - 4 * a * c
   */
    template< typename Type >
    inline constexpr Type delta(const Type a, const Type b, const Type c) noexcept
    {
        return ( b * b ) - ( a * 4 ) * c;
    }

    /**
   *  @return a * a 
   */
    template< typename Type >
    inline constexpr Type square_area(const Type a) noexcept
    {
        return a * a;
    }

    /**
   *  @return 4 * a
   */
    template< typename Type >
    inline constexpr Type square_circumference(const Type a) noexcept
    {
        return a * 4;
    }

    /**
   *  @return a * a * a 
   */
    template< typename Type >
    inline constexpr Type cube_volume(const Type a) noexcept
    {
        return a * a * a;
    }

    /**
   *  @return a * b
   */
    template< typename Type >
    inline constexpr Type rectangle_area(const Type a, const Type b) noexcept
    {
        return a * b;
    }

    /**
   *  @return a * 2 + b * 2
   */
    template< typename Type >
    inline constexpr Type rectangle_circumference(const Type a, const Type b) noexcept
    {
        return a * 2 + b * 2;
    }

    /**
   *  @return a * b * c
   */
    template< typename Type >
    inline constexpr Type cuboid_volume(const Type a, const Type b, const Type c) noexcept
    {
        return a * b * c;
    }

    /**
   *  @return PI * r * r
   */
    template< typename Type >
    inline constexpr Type circle_area(const Type r) noexcept
    {
        return static_cast<Type>(CONSTANT::PI<long double> * r * r);
    }

    /**
   *  @return 2 * PI * r
   */
    template< typename Type >
    inline constexpr Type circle_circumference(const Type r) noexcept
    {
        return static_cast<Type>(CONSTANT::PI<long double> * ( r * 2 ));
    }

    /**
   *  @return 4/3 * PI * R^3
   */
    template< typename Type >
    inline constexpr Type sphere_volume(const Type R) noexcept
    {
        return static_cast<Type>(CONSTANT::PI<long double> * ( 4.0 / 3.0 ) * R * R * R);
    }

    /**
   *  @return circle_area(r) * H
   */
    template< typename Type >
    inline constexpr Type cylinder_volume(const Type r, const Type H) noexcept
    {
        return static_cast<Type>(circle_area<long double>(r) * H);
    }

    /**
   *  @return cylinder_volume(r, h) * 1/3
   */
    template< typename Type >
    inline constexpr Type cone_volume(const Type r, const Type h) noexcept
    {
        return static_cast<Type>(cylinder_volume<long double>(r, h) * ( 1.0 / 3.0 ));
    }

    /**
   *  @brief Convert kW to HP
   */
    template< typename Type >
    inline constexpr Type kW_to_HP(const Type kW) noexcept
    {
        return static_cast<Type>(1.341022 * kW);
    }

    /**
   *  @brief Convert HP to kw
   */
    template< typename Type >
    inline constexpr Type HP_to_kW(const Type HP) noexcept
    {
        return static_cast<Type>(0.745699872 * HP);
    }

    /**
     *  @brief  Scale number ex.: (1,0,10,0,100) = 10
     *  @param   value Number to scale
     *  @param fromLow Minimum value old scale
     *  @param fromHigh Maximum value old scale
     *  @param toLow Minimum value new scale
     *  @param toLow Minimum value new scale
     *  @return Scaled number
     */
    template< typename Type = double >
    requires babel::CONCEPTS::IS_FLOATING_POINT<Type>
    inline constexpr Type
    map(const Type value, const Type fromLow, const Type fromHigh, const Type toLow, const Type toHigh)
    {
        return ( ( ( value - fromLow ) * ( toHigh - toLow ) ) / ( fromHigh - fromLow ) ) + toLow;
    }

    template<typename T>
    requires std::is_integral_v<T>
    std::vector<T> prime_factors(T number) noexcept
    {
        if (number <= 2)
            return {number};
        std::vector<T> _res;
        for(size_t i = 2; i <= number ; ++i)
            while(number%i == 0)
            {
                _res.emplace_back(i);
                number /= i;
            }
        return _res;
    }

    template<typename T>
    requires std::is_integral_v<T>
    constexpr T nwd(T x, T y) noexcept
    {
        while (x%y !=0)
        {
            T temp = x;
            x = y;
            y = temp%y;
        }
        return y;
    }

    template<typename T>
    requires std::is_integral_v<T>
    constexpr inline T nww(T x, T y) noexcept
    {
        return (x*y) / nwd(x, y);
    }

    template<typename T>
    requires std::is_floating_point_v<T>
    std::vector<T> find_x(const T a, const T b, const T c) noexcept
    {
        std::vector<T> zeros;
        auto _delta = delta(a, b, c);
        if (_delta > 0)
        {
            auto sq_delta = std::sqrt(_delta);
            auto two_a = 2.0 * a;
            zeros.emplace_back(( sq_delta - b) / two_a);
            zeros.emplace_back(( -sq_delta - b) / two_a);
        }
        else if (_delta == 0)
            zeros.emplace_back((-b)/(2.0 * a));
        return zeros;
    }

    template<typename T>
    requires std::is_floating_point_v<T>
    constexpr inline T distance(const T Ax, const T Ay) noexcept
    {
        return babel::MATH::abs(Ax - Ay);
    }

    template<typename T>
    requires std::is_floating_point_v<T>
    constexpr inline T distance(const T Ax, const T Ay, const T Bx , const T By) noexcept
    {
        return std::sqrt(std::pow(Bx- Ax, 2.0) + std::pow(By - Ay, 2.0));
    }

}


#endif