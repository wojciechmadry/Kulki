#ifndef babel_MATH
#define babel_MATH

#include "variadic.hpp"

namespace babel::MATH {
    namespace CONSTANT {

        /**
        *  @brief PI value convert to Type
        */
        template<typename Type>
        constexpr Type PI = static_cast<Type>(3.141592653589793238462643383279502884197169399375105);

        /**
        *  @brief E value convert to Type
        */
        template<typename Type>
        constexpr Type E = static_cast<Type>(2.71828182845904523536028747135266249775724709369995);

        /**
         *  @brief Square root of two convert to Type
         */
        template<typename Type>
        constexpr Type sqrt_2 = static_cast<Type>(1.41421356237309504880168872420969807856967187537694);

        /**
         *  @brief Square root of three convert to Type
         */
        template<typename Type>
        constexpr Type sqrt_3 = static_cast<Type>(1.73205080756887729352744634150587236694280525381038);

        /**
         *  @brief Planck constant convert to Type
         */
        template<typename Type>
        constexpr Type PLANCK = static_cast<Type>(6.62607004e-34);

        /**
         *  @brief Golden ratio convert to Type
         */
        template<typename Type>
        constexpr Type golden_ratio = static_cast<Type>(1.61803398874989484820);

    }

    /**
    *  @brief  Convert negative number to positive.
    *  @param  v Number can be positive or negative.
    * Must be arithmetic
    *  @return Return absolute value of number
    */
    template<typename T>
    requires babel::CONCEPTS::IS_SIGNED<T>
    constexpr inline T abs(const T v)
    {
        return (v >= 0) ? v : -v;
    }


    /**
    *  @brief  Compare two number
    *  @param  value1 First number
    *  @param  value2 Second number
    *  @return Return greater number
    */
    template<typename T, typename T2>
    requires babel::CONCEPTS::IS_SAME_CONVERTIBLE<T, T2>
    constexpr inline auto max(T value1, T2 value2)
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
    template<typename T, typename ... Args>
    constexpr T max(T value1, T value2, Args... arg)
    {
        if (value1 < value2)
            value1 = value2;
        babel::VARIADIC::holder<T> _hold(arg...);
        const auto &vec = _hold.get();
        for (size_t i = 0; i < vec.size(); ++i)
        {
            if (vec[i] > value1)
                value1 = vec[i];
        }
        return value1;
    }

    /**
    *  @brief  Compare two number
    *  @param  value1 First number
    *  @param  value2 Second number
    *  @return Return lowest number
    */
    template<typename T, typename T2>
    requires babel::CONCEPTS::IS_SAME_CONVERTIBLE<T, T2>
    constexpr inline auto min(T value1, T2 value2)
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
    template<typename T, typename ... Args>
    constexpr T min(T value1, T value2, Args... arg)
    {
        if (value1 > value2)
            value1 = value2;
        babel::VARIADIC::holder<T> _hold(arg...);
        for (size_t i = 0; i < _hold.get().size(); ++i)
        {
            if (_hold.get()[i] < value1)
                value1 = _hold.get()[i];
        }
        return value1;
    }

    /**
    *  @brief  Compare few number
    *  @param   init_list Initializer list of numbers
    *  @return Return the largest number
    */
    template<typename T>
    constexpr T max(const std::initializer_list<T> &init_list)
    {
        auto _it = init_list.begin();
        T MAX = *_it++;
        for (; _it != init_list.end(); ++_it)
            MAX = max(MAX, *_it);
        return MAX;
    }

    /**
   *  @brief  Compare few number
   *  @param   init_list Initializer list of numbers
   *  @return Return the smallest number
   */
    template<typename T>
    constexpr T min(const std::initializer_list<T> &init_list)
    {
        auto _it = init_list.begin();
        T MIN = *_it++;
        for (; _it != init_list.end(); ++_it)
            MIN = min(MIN, *_it);
        return MIN;

    }

    /**
   *  @brief  Check if number is negative
   *  @param   val A number
   *  @return If val is negative return 1 otherwise return 0
   */
    template<typename T>
    requires babel::CONCEPTS::IS_SIGNED<T>
    constexpr inline bool is_neg(T val)
    {
        return val < 0 ? 1 : 0;
    }

        /**
    *  @brief  Check if number is negative
    *  @param   val A number
    *  @return If val is negative return 1 otherwise return 0
    */
    template<typename T>
    requires babel::CONCEPTS::IS_UNSIGNED<T>
    constexpr inline bool is_neg(T val)
    {
        return false;
    }

    /**
    *  @brief  ex.: n = 3, return : 1 * 2 * 3
    *  @param   n Factorial of n
    *  @return Factorial N
    */
    template<size_t N>
    constexpr uint64_t factorial()
    {
        uint64_t res = 1;
        for(size_t i = 2 ; i <= N ; ++i)
            res *= i;
        return res;
    }

    /**
*  @brief  ex.: n = 3, return : 1 * 2 * 3
*  @param   n Factorial of n
*  @return Factorial N
*/

    constexpr uint64_t factorial(size_t N)
    {
        uint64_t res = 1;
        while(N > 1)
        {
            res *= N;
            N -= 1;
        }

        return res;
    }

    /**
   *  @param   n Fibonacci number
   *  @return Fibonacci N
   */
    constexpr uint64_t fib(unsigned n)
    {
        uint64_t F[2][2] = {{1, 1},
                            {1, 0}};
        if (n == 0)
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
    template<typename Type>
    inline constexpr Type delta(const Type a, const Type b, const Type c)
    {
        return (b * b) - (a * 4) * c;
    }

    /**
   *  @return a * a 
   */
    template<typename Type>
    inline constexpr Type square_area(Type a)
    {
        return a * a;
    }

    /**
   *  @return 4 * a
   */
    template<typename Type>
    inline constexpr Type square_circumference(Type a)
    {
        return a * 4;
    }

    /**
   *  @return a * a * a 
   */
    template<typename Type>
    inline constexpr Type cube_volume(Type a)
    {
        return a * a * a;
    }

    /**
   *  @return a * b
   */
    template<typename Type>
    inline constexpr Type rectangle_area(Type a, Type b)
    {
        return a * b;
    }

    /**
   *  @return a * 2 + b * 2
   */
    template<typename Type>
    inline constexpr Type rectangle_circumference(Type a, Type b)
    {
        return (a * 2) + (b * 2);
    }

    /**
   *  @return a * b * c
   */
    template<typename Type>
    inline constexpr Type cuboid_volume(Type a, Type b, Type c)
    {
        return a * b * c;
    }

    /**
   *  @return PI * r * r
   */
    template<typename Type>
    inline constexpr Type circle_area(Type r)
    {
        return static_cast<Type>(CONSTANT::PI<long double> * r * r);
    }

    /**
   *  @return 2 * PI * r
   */
    template<typename Type>
    inline constexpr Type circle_circumference(Type r)
    {
        return static_cast<Type>(CONSTANT::PI<long double> * (r * 2));
    }

    /**
   *  @return 4/3 * PI * R^3
   */
    template<typename Type>
    inline constexpr Type sphere_volume(Type R)
    {
        return static_cast<Type>(CONSTANT::PI<long double> * (4.0 / 3.0) * R * R * R);
    }

    /**
   *  @return circle_area(r) * H
   */
    template<typename Type>
    inline constexpr Type cylinder_volume(Type r, Type H)
    {
        return static_cast<Type>(circle_area<long double>(r) * H);
    }

    /**
   *  @return cylinder_volume(r, h) * 1/3
   */
    template<typename Type>
    inline constexpr Type cone_volume(Type r, Type h)
    {
        return static_cast<Type>(cylinder_volume<long double>(r, h) * (1.0 / 3.0));
    }

    /**
   *  @brief Convert kW to HP
   */
    template<typename Type>
    inline constexpr Type kW_to_HP(Type kW)
    {
        return static_cast<Type>(1.341022 * kW);
    }

    /**
   *  @brief Convert HP to kw
   */
    template<typename Type>
    inline constexpr Type HP_to_kW(Type HP)
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
    template<typename Type = double>
    requires babel::CONCEPTS::IS_FLOATING_POINT<Type>
    inline constexpr Type map(Type value, Type fromLow, Type fromHigh, Type toLow, Type toHigh)
    {
        return (((value - fromLow) * (toHigh - toLow)) / (fromHigh - fromLow)) + toLow;
    }
}


#endif