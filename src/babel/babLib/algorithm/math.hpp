#ifndef babel_ALGO_MATH
#define babel_ALGO_MATH

#include "../variadic.hpp"

namespace babel::ALGO::MATH{
    namespace DERIVATIVE{
        namespace FIRST{
            /**
*  @brief  Calculate first derivative by definition
*  @param func The function from which we calculate the derivative
              *  @param h Small value h -> 0
*  @return Returns a function that takes one parameter of x, that evaluates to the derivative of.
*/
            template< typename Function, typename TYPE = double >
            [[nodiscard]] auto by_definiton(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto { return ( func(x + h) - func(x) ) / h; };
            }

            /**
*  @brief  Calculate first derivative in three point
*  @param func The function from which we calculate the derivative
  *  @param h Small value h -> 0
*  @return Returns a function that takes one parameter of x, that evaluates to the derivative of.
*/
            template< typename Function, typename TYPE = double >
            [[nodiscard]] auto three_point(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto { return ( func(x + h) - func(x - h) ) / ( 2.0 * h ); };
            }

            /**
*  @brief  Calculate first derivative in five point
*  @param func The function from which we calculate the derivative
*  @param h Small value h -> 0
*  @return Returns a function that takes one parameter of x, that evaluates to the derivative of.
*/
            template< typename Function, typename TYPE = double >
            [[nodiscard]] auto five_point(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( -func(x + 2.0 * h) + 8 * func(x + h) - 8.0 * func(x - h) + func(x - 2.0 * h) ) /
                           ( 12.0 * h );
                };
            }

            /**
*  @brief  Calculate first forward derivative
*  @param func The function from which we calculate the derivative
*  @param h Small value h -> 0
*  @return Returns a function that takes one parameter of x, that evaluates to the derivative of.
*/
            template< typename Function, typename TYPE = double >
            [[nodiscard]] auto forward(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( -3.0 * func(x) + 4.0 * func(x + h) - func(x + 2.0 * h) ) / ( 2.0 * h );
                };
            }

            /**
*  @brief  Calculate first central derivative
*  @param func The function from which we calculate the derivative
*  @param h Small value h -> 0
*  @return Returns a function that takes one parameter of x, that evaluates to the derivative of.
*/
            template< typename Function, typename TYPE = double >
            [[nodiscard]] auto central(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto { return ( func(x + h) - func(x - h) ) / ( 2.0 * h ); };
            }

            /**
*  @brief  Calculate first backward derivative
*  @param func The function from which we calculate the derivative
*  @param h Small value h -> 0
*  @return Returns a function that takes one parameter of x, that evaluates to the derivative of.
*/
            template< typename Function, typename TYPE = double >
            [[nodiscard]] auto backward(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( func(x - 2.0 * h) - 4.0 * func(x - h) + 3.0 * func(x) ) / ( 2.0 * h );
                };
            }
        }
        namespace SECOND{
            /**
*  @brief  Calculate second derivative in three point
*  @param func The function from which we calculate the second derivative
*  @param h Small value h -> 0
*  @return Returns a function that takes one parameter of x, that evaluates to the second derivative of.
*/
            template< typename Function, typename TYPE = double >
            [[nodiscard]] auto three_point(const Function func, const double h = 0.00001) noexcept
            {
                return [func, h](const TYPE x) -> auto {
                    return ( func(x + h) - 2.0 * func(x) + func(x - h) ) / ( std::pow(h, 2.0) );
                };
            }

            /**
*  @brief  Calculate second derivative in five point
*  @param func The function from which we calculate the second derivative
*  @param h Small value h -> 0
*  @return Returns a function that takes one parameter of x, that evaluates to the second derivative of.
*/
            template< typename Function, typename TYPE = double >
            [[nodiscard]] auto five_point(const Function func, const double h = 0.00001) noexcept
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
     *  \EXAMPLE_1 abs(-4) -> 4
     *  \EXAMPLE_2 abs(4) -> 4
     *  @param  v Number can be positive or negative.
     *  @return Return absolute value of number
     */
    template< typename T >
    requires ( !babel::CONCEPTS::IS_CONTAINER<T> )
    [[nodiscard]] constexpr inline T abs(const T v)
    {
        return ( v >= 0 ) ? v : -v;
    }


    /**
 *  @brief  Convert negative number to positive in data structure.
  *  \EXAMPLE_1  {3, 1, -4, 2, -1} -> {3, 1, 4, 2 , 1}
 *  @param  v Vector of numbers.
 *  @return no return
 */
    template< typename T, typename U = babel::CONCEPTS::type_in<T> >
    requires(babel::CONCEPTS::IS_CONTAINER<T>)
    constexpr void abs(T &v)
    {
        std::for_each(std::begin(v), std::end(v), [](U &val) { val = babel::ALGO::MATH::abs(val); });
    }


    /**
    *  @brief  Compare two number
     *  \Example_1 max(-3, 5) -> 5
     *  \Example_2 max(7, 20) -> 20
    *  @param  value1 First number
    *  @param  value2 Second number
    *  @return Return greater number
    */
    template< typename T, typename T2 >
    requires ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<T, T2> && !babel::CONCEPTS::IS_CONTAINER<T> &&
               !babel::CONCEPTS::IS_CONTAINER<T2> )
    [[nodiscard]] constexpr inline auto max(const T value1, const T2 value2) noexcept
    {
        return value1 > value2 ? value1 : value2;
    }

    /**
*  @brief  Compare more than two number (its the worst method)
     *  \Example_1 max(-3, 5,12 ,5 , 3) -> 12
     *  \Example_2 max(7, 20,4, 8) -> 20
*  @param  value1 First number
*  @param  value2 Second number
*  @param  arg    all other number
*  @return Return the largest number
*/
    template< typename T, typename ... Args >
    requires ( !babel::CONCEPTS::IS_CONTAINER<T> )
    [[nodiscard]] constexpr T max(T value1, T value2, Args... arg) noexcept
    {
        if ( value1 < value2 )
            value1 = value2;
        babel::VARIADIC::holder<T> _hold(arg...);
        const auto &vec = _hold.get();
        std::for_each(vec.begin(), vec.end(),
                      [&value1](const T &Data) mutable {
                          if ( Data > value1 )
                              value1 = Data;
                      }
        );
        return value1;
    }

    /**
    *  @brief  Compare two number
     *  \Example_1 min(-3, 5) -> -3
     *  \Example_2 min(7, 20) -> 8
    *  @param  value1 First number
    *  @param  value2 Second number
    *  @return Return lowest number
    */
    template< typename T, typename T2 >
    requires babel::CONCEPTS::IS_SAME_CONVERTIBLE<T, T2>
    [[nodiscard]] constexpr inline auto min(const T value1, const T2 value2) noexcept
    {
        return value1 < value2 ? value1 : value2;
    }

    /**
*  @brief  Compare more than two number (its the worst method)
      *  \Example_1 min(-3, 5,12 ,5 , 3) -> -3
     *  \Example_2 min(7, 20,4, 8) -> 4
*  @param  value1 First number
*  @param  value2 Second number
*  @param  arg    all other number
*  @return Return the lowest number
*/
    template< typename T, typename ... Args >
    [[nodiscard]] constexpr T min(T value1, T value2, Args... arg) noexcept
    {
        if ( value1 > value2 )
            value1 = value2;
        babel::VARIADIC::holder<T> _hold(arg...);
        const auto &vec = _hold.get();
        std::for_each(vec.begin(), vec.end(),
                      [&value1](const T &Data) mutable {
                          if ( Data < value1 )
                              value1 = Data;
                      }
        );
        return value1;
    }

    /**
    *  @brief  Compare few number
     *  \Example_1 max({-3, 5,12 ,5 , 3}) -> 12
     *  \Example_2 max({7, 20,4, 8}) -> 20
    *  @param   Container  of numbers
    *  @return Return the largest number
    */
    template< typename T, typename U =babel::CONCEPTS::type_in<T>>
    requires babel::CONCEPTS::IS_CONTAINER<T>
    [[nodiscard]] constexpr U max(const T &Container) noexcept
    {
        if ( Container.size() == 0 )
            return { };
        U MAX = std::numeric_limits<U>::min();
        std::for_each(std::begin(Container), std::end(Container),
                      [&MAX](const U &Data) mutable {
                          if ( Data > MAX )
                              MAX = Data;
                      });
        return MAX;
    }

    /**
   *  @brief  Compare few number
     *  \Example_1 min({-3, 5,12 ,5 , 3}) -> -3
     *  \Example_2 min({7, 20,4, 8}) -> 4
   *  @param   Container of numbers
   *  @return Return the smallest number
   */
    template< typename T, typename U = babel::CONCEPTS::type_in<T> >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    [[nodiscard]] constexpr U min(const T &Container) noexcept
    {
        if ( Container.size() == 0 )
            return { };
        U MIN = std::numeric_limits<U>::max();
        std::for_each(std::begin(Container), std::end(Container),
                      [&MIN](const U &Data) mutable {
                          if ( Data < MIN )
                              MIN = Data;
                      });
        return MIN;
    }

    /**
   *  @brief  Check if number is negative
     *  \Example_1 is_neg(5) -> false
     *  \Example_2 is_neg(-5) -> true
   *  @param   val A number
   *  @return If val is negative return 1 otherwise return 0
   */
    template< typename T >
    [[nodiscard]] constexpr inline bool is_neg(const T val) noexcept
    {
        return val < 0 ? 1 : 0;
    }

    /**
*  @brief  Return factorial of n calculate in compiler time
     *  \Example_1 n = 3, return : 1 * 2 * 3
     *  \Example_2 n = 4, return : 1 * 2 * 3 * 4
    *  @return Factorial N
    */
    template< uint64_t N >
    [[nodiscard]] consteval uint64_t factorial() noexcept
    {
        uint64_t res = 1;
        for ( size_t i = 2 ; i <= N ; ++i )
            res *= i;
        return res;
    }

    /**
*  @brief  Return factorial of n
     *  \Example_1 n = 3, return : 1 * 2 * 3
     *  \Example_2 n = 4, return : 1 * 2 * 3 * 4
*  @param   n Factorial of n
*  @return Factorial N
*/

    [[nodiscard]] constexpr uint64_t factorial(uint64_t N) noexcept
    {
        uint64_t res = 1;
        while ( N > 1 )
        {
            res *= N;
            --N;
        }

        return res;
    }

    /**
*  @brief  Calculate binomial coefficient
     *  n >= k >= 0
*  @return Binomial coefficient
*/
    [[nodiscard]] constexpr double binomial_coefficient(const uint64_t N, const uint64_t K)
    {
        if ( K > N )
            throw std::out_of_range("K > N.");
        return static_cast<double>(factorial(N)) / static_cast<double>(factorial(K) * factorial(N - K));
    }

    /**
*  @brief  Calculate binomial coefficient in compiler time
 *  n >= k >= 0
*  @return Binomial coefficient
*/
    template< uint64_t N, uint64_t K >
    [[nodiscard]] consteval double binomial_coefficient() noexcept
    {
        if ( K > N )
            throw std::out_of_range("K > N.");
        return static_cast<double>(factorial<N>()) / static_cast<double>(factorial<K>() * factorial<N - K>());
    }

    /**
   *  @param   n Fibonacci number
   *  @return Fibonacci N
   */
    [[nodiscard]] constexpr uint64_t fib(unsigned n) noexcept
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
    [[nodiscard]] inline constexpr Type delta(const Type a, const Type b, const Type c) noexcept
    {
        return ( b * b ) - ( a * static_cast<Type>(4) ) * c;
    }

    /**
   *  @return a * a 
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type square_area(const Type a) noexcept
    {
        return a * a;
    }

    /**
   *  @return 4 * a
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type square_circumference(const Type a) noexcept
    {
        return a * 4;
    }

    /**
   *  @return a * a * a 
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type cube_volume(const Type a) noexcept
    {
        return a * a * a;
    }

    /**
   *  @return a * b
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type rectangle_area(const Type a, const Type b) noexcept
    {
        return a * b;
    }

    /**
   *  @return a * 2 + b * 2
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type rectangle_circumference(const Type a, const Type b) noexcept
    {
        return a * 2 + b * 2;
    }

    /**
   *  @return a * b * c
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type cuboid_volume(const Type a, const Type b, const Type c) noexcept
    {
        return a * b * c;
    }

    /**
   *  @return PI * r * r
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type circle_area(const Type r) noexcept
    {
        return static_cast<Type>(CONSTANT::PI<Type> * r * r);
    }

    /**
   *  @return 2 * PI * r
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type circle_circumference(const Type r) noexcept
    {
        return static_cast<Type>(CONSTANT::PI<Type> * ( r * 2 ));
    }

    /**
   *  @return 4/3 * PI * R^3
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type sphere_volume(const Type R) noexcept
    {
        return static_cast<Type>(CONSTANT::PI<Type> * ( 4.0 / 3.0 ) * R * R * R);
    }

    /**
   *  @return circle_area(r) * H
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type cylinder_volume(const Type r, const Type H) noexcept
    {
        return static_cast<Type>(circle_area<Type>(r) * H);
    }

    /**
   *  @return cylinder_volume(r, h) * 1/3
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type cone_volume(const Type r, const Type h) noexcept
    {
        return static_cast<Type>(cylinder_volume<Type>(r, h) * ( 1.0 / 3.0 ));
    }

    /**
   *  @brief Convert kW to HP
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type kW_to_HP(const Type kW) noexcept
    {
        return static_cast<Type>(1.341022 * kW);
    }

    /**
   *  @brief Convert HP to kw
   */
    template< typename Type >
    [[nodiscard]] inline constexpr Type HP_to_kW(const Type HP) noexcept
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
    [[nodiscard]] inline constexpr Type
    map(const Type value, const Type fromLow, const Type fromHigh, const Type toLow, const Type toHigh)
    {
        return ( ( ( value - fromLow ) * ( toHigh - toLow ) ) / ( fromHigh - fromLow ) ) + toLow;
    }

    /**
*  @brief  Decompose the number into prime factors
 *  \Example_1 (42) -> 2, 3, 7
 *  \Example_2 (116) -> 2, 2, 29
*  @param  number to decompose
*  @return Return vector of prime number
*/
    template< typename T >
    requires ( std::is_integral_v<T> && !std::is_signed_v<T> )
    [[nodiscard]] std::vector<T> prime_factors(T number) noexcept
    {
        if ( number <= 2 )
            return {number};
        std::vector<T> _res;
        for ( T i = 2 ; i <= number ; ++i )
            while ( number % i == 0 )
            {
                _res.emplace_back(i);
                number /= i;
            }
        return _res;
    }

    /**
*  @brief  Greatest common divisor
*  \Example_1 (36, 6) -> 6
*  \Example_2 (420, 56) -> 28
*  @param  x Number 1
*  @param  y Number 2
*  @return Greatest common divisor
*/
    template< typename T >
    requires std::is_integral_v<T>
    [[nodiscard]] constexpr T gcd(T x, T y) noexcept
    {
        while ( x % y != 0 )
        {
            T temp = x;
            x = y;
            y = temp % y;
        }
        return y;
    }

    /**
*  @brief  Least common multiple
*  \Example_1 (36, 6) -> 36
*  \Example_2 (420, 56) -> 840
*  @param  x Number 1
*  @param  y Number 2
*  @return Least common multiple
*/
    template< typename T >
    requires std::is_integral_v<T>
    [[nodiscard]] constexpr inline T lcm(T x, T y) noexcept
    {
        return ( x * y ) / gcd(x, y);
    }

    /**
*  @brief  Calculate zeros position of the function (can be 0, 1 or 2 zeros) ax^2 + bx + c
*  \Example_1 (3, 5, -4) -> {0.590667, -2.25733}
*  \Example_2 (-4, 3, 2) -> {-0.425391, 1.17539}
*  @param  a, b, c function coefficients
*  @return zeros position of the function
*/
    template< typename T >
    requires std::is_floating_point_v<T>
    [[nodiscard]] std::vector<T> find_x(const T a, const T b, const T c) noexcept
    {
        std::vector<T> zeros;
        auto _delta = delta(a, b, c);
        if ( _delta > 0 )
        {
            auto sq_delta = std::sqrt(_delta);
            auto two_a = 2.0 * a;
            zeros.emplace_back(( sq_delta - b ) / two_a);
            zeros.emplace_back(( -sq_delta - b ) / two_a);
        } else if ( _delta == 0 )
            zeros.emplace_back(( -b ) / ( 2.0 * a ));
        return zeros;
    }

    /**
*  @brief  Calculate distance between two points in OX
*  \Example_1 (-3, 2) -> 5
*  \Example_2 (2, -3) -> 5
*  \Example_3 (12, 18) -> 6
*  @param  x1,x2 point in OX
*  @return Distance between to points
*/
    template< typename T >
    requires std::is_floating_point_v<T>
    [[nodiscard]] constexpr inline T distance(const T x1, const T x2) noexcept
    {
        return babel::ALGO::MATH::abs(x1 - x2);
    }

    /**
*  @brief  Calculate distance between two points in Cartesian matrix
*  \Example_1 (-3, 2, 4, 7) -> 8.60233
*  \Example_2 (2, -3, 7, 4) -> 8.60233
*  \Example_3 (12, 18, 5, 5) -> 14.7648
*  @param  Ax,Ay first point in matrix
*  @param  Bx,By second point in matrix
*  @return Distance between two points
*/
    template< typename T >
    requires std::is_floating_point_v<T>
    [[nodiscard]] constexpr inline T distance(const T Ax, const T Ay, const T Bx, const T By) noexcept
    {
        return std::sqrt(std::pow(Bx - Ax, 2.0) + std::pow(By - Ay, 2.0));
    }

    /**
*  @brief  Check if number is automorphic
     *  \EXAMPLE_1 (25)^2 == 625 -> true
     *  \EXAMPLE_2 (76)^2 == 5776 -> true
*  @param  n Number
*  @return Return 1 if n is automorphic or 0 if not.
*/
    [[nodiscard]] constexpr bool is_automorphic(int64_t n) noexcept
    {
        n = babel::ALGO::MATH::abs(n);
        uint16_t digits = 0;
        for ( int64_t cpy = n ; cpy > 1 ; ++digits )
            cpy /= 10;
        return ( static_cast<int64_t>(pow(static_cast<double>(n), 2.0)) % static_cast<int64_t>(pow(10, digits)) ) == n;
    }


    /**
*  @brief  Calculate FFT from probes.
*  @param  container Data structure of elements.
*  @return Return FFT
*/
    template< typename Container, typename T = babel::CONCEPTS::type_in<Container> >
    requires ( babel::CONCEPTS::IS_FLOATING_POINT<T> && babel::CONCEPTS::IS_CONTAINER<Container> )
    [[nodiscard]] std::vector<std::complex<T>> FFT(const Container &probes) noexcept
    {
        std::function<void(std::vector<std::complex<T>> &)> ditfft2;
        ditfft2 = [&ditfft2](std::vector<std::complex<T>> &fn) -> void {
            const size_t N = fn.size();
            if ( N < 2 ) return;
            std::vector<std::complex<T>> even;
            std::vector<std::complex<T>> odd;
            for ( size_t i = 0 ; i < N ; ++i )
                if ( i % 2 == 0 )
                    even.emplace_back(fn[i]);
                else
                    odd.emplace_back(fn[i]);
            ditfft2(even);
            ditfft2(odd);
            for ( size_t k = 0 ; k < N / 2 ; ++k )
            {
                auto t = std::polar(1.0, -2.0 * std::numbers::pi * static_cast<double>(k) / static_cast<double>(N)) *
                         odd[k];
                fn[k] = even[k] + t;
                fn[k + N / 2] = even[k] - t;
            }
        };

        std::vector<std::complex<T>> res(std::begin(probes), std::end(probes));
        ditfft2(res);
        return res;
    }

}


#endif