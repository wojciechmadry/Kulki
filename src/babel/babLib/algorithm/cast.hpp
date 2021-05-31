#ifndef babel_ALGO_CAST
#define babel_ALGO_CAST

#include "../must_have.hpp"

namespace babel::ALGO::CAST{

    /**
   *  @brief  Convert string to number (float, int, etc...)
    *  \EXAMPLE_1 string_to<float>("3.14") -> float(3.14)
   *  @param  _string Number in string
   *  @return Return string convert to number
   */
    template< typename T, typename U = std::decay_t<T>>
    constexpr inline U string_to(const std::string &_string)
    {
        if constexpr ( babel::CONCEPTS::IS_SAME<U, int> )
            return std::stoi(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<U, long> )
            return std::stol(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<U, long long> )
            return std::stoll(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<U, unsigned long long> )
            return std::stoull(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<U, unsigned long> )
            return std::stoul(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<U, float> )
            return std::stof(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<U, double> )
            return std::stod(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<U, long double> )
            return std::stold(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<U, unsigned int> )
            return static_cast<unsigned int>(std::stoul(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<U, char> )
            return static_cast<char>(std::stoi(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<U, unsigned char> )
            return static_cast<unsigned char>(std::stoul(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<U, short> )
            return static_cast<short>(std::stoi(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<U, unsigned short> )
            return static_cast<unsigned short>(std::stoul(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<U, bool> )
            return static_cast<bool>(std::stoul(_string));
        throw std::out_of_range("No visible conversion.");
    }

    /**
*  @brief  Convert signed/unsgined data to unsigned/signed.
*  \Example_1 int32_t a = -3, function return uint32_t(a)
*  \Example_2 unt32_t a = 35, function return int32_t(a)
*  @param  data Signed or Unsigned data to convert
*  @return Signed/Unsigned data
*/
    template< typename T >
    requires ( std::is_signed_v<T> || std::is_unsigned_v<T> )
    constexpr auto signed_unsigned_conv(const T data) noexcept
    {
        return static_cast< typename babel::CONCEPTS::type_of_number<static_cast<uint8_t>(sizeof(data)), !std::is_signed_v<T>>::type >(data);
    }


    /**
*  @brief  Convert from one type to another
*  \Example_1 T = std::string AND U is arithmetic -> std::to_string(data)
*  \Example_2 T is arithmetic AND U = std::string-> babel::ALGO::string_to<T>(data)
*  \Example_3 If T/U is base of U/T You can transform from one Base/Derived to Derived/Base. (using dynamic_cast<>)
     *  For example:
     *  Struct P {}, Struct Y : public P {}.
     *  Y y;
     *  P* = asType<P *>(y); OR P* = asType<P *>(&y);
     * auto& YRef = babel::ALGO::CAST::asType<Y&>(*pp);
*  \Example_4 Can convert std::list<T> to std::vector<U> T need to be convertible to U etc.
*  \Example_5 Can convert std::list<int/float...> to std::vector<std::string>
*  \Example_6 Can convert values with Convert Function -> Top priority!
     *  T = int*
     *  U = int
     *  Func = [] (int Value) -> int* {return new int Value;};
     *  asType<int*>(15, Func)
*  \Example_7 Can convert every single value in container
     *  U = std::vector<int> v1 = {1, 2}
     *  T = std::vector<std::string> v2 = {}
     *  Func = [] (int Value) -> std::string {return std::to_string(Value * 2);};
     *  asType<std::vector<std::string>>(v1, Func) -> v2 = {2, 4}
* \Example_8
     * U = std::string s1 = "test"
     * T = std::string s2 = ""
     * s2 = asType<std::string>(std::move(s1)) -> s1 = "" and s2 = "test"
 * \Example_9
     * U = std::vector<std::string> vs = {"t1", "t2"};
     * T = std::list<std::string> ls = {};
     * ls = asType<decltype(ls)>(std::move(vs));
     * vs == {"", ""} and ls == {"t1", "t2"};
*  \Example_LAST In other case return static_cast<T>(data)
*  @template  U Convert to T
*  @param  U (data) Convert from U data to T data
*  @return Converted type
*/
    template< typename T, typename ConvertFunction = void *, typename U, typename DECAY_T = typename std::decay_t<T>, typename DECAY_U = typename std::decay_t<U>>
    requires ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<DECAY_T, DECAY_U>
               || ( std::is_same_v<std::string, DECAY_T> && std::is_arithmetic_v<DECAY_U> )
               || ( std::is_same_v<std::string, DECAY_U> && std::is_arithmetic_v<DECAY_T> )
               || ( std::is_pointer_v<T> && ( std::is_base_of_v<std::remove_pointer_t<DECAY_T>, DECAY_U> ||
                                              std::is_base_of_v<std::remove_pointer_t<DECAY_T>, std::remove_pointer_t<DECAY_U> > ) )
               || ( std::is_pointer_v<T> && ( std::is_base_of_v<std::remove_pointer_t<DECAY_U>, DECAY_T> ||
                                              std::is_base_of_v<std::remove_pointer_t<DECAY_U>, std::remove_pointer_t<DECAY_T> > ) )
               || ( babel::CONCEPTS::IS_CONTAINER<DECAY_T> && babel::CONCEPTS::IS_CONTAINER<DECAY_U>
                    &&
                    babel::CONCEPTS::IS_SAME_CONVERTIBLE<babel::CONCEPTS::type_in<DECAY_T>, babel::CONCEPTS::type_in<DECAY_U>> )
               || ( babel::CONCEPTS::IS_CONTAINER<DECAY_T> && babel::CONCEPTS::IS_CONTAINER<DECAY_U>
                    && ( ( std::is_same_v<std::string, babel::CONCEPTS::type_in<DECAY_T>> &&
                           std::is_arithmetic_v<babel::CONCEPTS::type_in<DECAY_U>> ) ||
                         ( std::is_same_v<std::string, babel::CONCEPTS::type_in<DECAY_U>> &&
                           std::is_arithmetic_v<babel::CONCEPTS::type_in<DECAY_T>> ) ) )
               ||
               ( !std::is_same_v<ConvertFunction, void *> &&
                 babel::CONCEPTS::FUNCTION_RETURN<ConvertFunction, T, U> )
               || ( !std::is_same_v<ConvertFunction, void *> &&
                    babel::CONCEPTS::FUNCTION_RETURN<ConvertFunction, babel::CONCEPTS::type_in<DECAY_T>, babel::CONCEPTS::type_in<DECAY_U>> )
    )

    [[nodiscard]] constexpr inline T asType(U &&data, ConvertFunction Func = nullptr) noexcept
    {
        if constexpr ( !std::is_same_v<ConvertFunction, void *> )
        {
            if constexpr ( babel::CONCEPTS::FUNCTION_RETURN<ConvertFunction, T, U> )
                return Func(std::forward<U>(data));
            else
            {
                T ArrayLike;
                std::transform(std::begin(data), std::end(data), std::back_inserter(ArrayLike), Func);
                return ArrayLike;
            }
        } else if constexpr ( std::is_same_v<std::string, DECAY_T> && std::is_arithmetic_v<DECAY_U> )
            return std::to_string(data);
        else if constexpr ( std::is_arithmetic_v<DECAY_T> && std::is_same_v<std::string, DECAY_U> )
            return babel::ALGO::CAST::string_to<DECAY_T>(data);
        else if constexpr (
                ( std::is_pointer_v<T> && ( std::is_base_of_v<std::remove_pointer_t<DECAY_T>, DECAY_U> ||
                                            std::is_base_of_v<std::remove_pointer_t<DECAY_T>, std::remove_pointer_t<DECAY_U> > ) )
                || ( std::is_pointer_v<T> && ( std::is_base_of_v<std::remove_pointer_t<DECAY_U>, DECAY_T> ||
                                               std::is_base_of_v<std::remove_pointer_t<DECAY_U>, std::remove_pointer_t<DECAY_T> > ) ) )
        {
            if constexpr( std::is_pointer_v<DECAY_U> )
            {
                return dynamic_cast<T>(data);
            } else
            {
                return dynamic_cast<T>(&data);
            }
        } else if constexpr ( babel::CONCEPTS::IS_CONTAINER<DECAY_T> && babel::CONCEPTS::IS_CONTAINER<DECAY_U> )
        {
            if constexpr ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<babel::CONCEPTS::type_in<DECAY_T>, babel::CONCEPTS::type_in<DECAY_U>> )
            {
                if constexpr ( std::is_same_v<DECAY_T, DECAY_U> )
                {
                    return std::forward<U>(data);
                } else
                {
                    if constexpr ( std::is_lvalue_reference_v<U> )
                        return T {std::begin(data), std::end(data)};
                    else
                    {
                        T ArrayLike;
                        std::transform(std::begin(data), std::end(data),std::back_inserter(ArrayLike),
                                       []<typename LambdaType>(LambdaType& Element)
                                       {
                                           return std::move(Element);
                                       });
                        return ArrayLike;
                    }
                }
            } else if constexpr( ( std::is_same_v<std::string, babel::CONCEPTS::type_in<DECAY_U>> &&
                                   std::is_arithmetic_v<babel::CONCEPTS::type_in<DECAY_T>> )
                                 || ( std::is_same_v<std::string, babel::CONCEPTS::type_in<DECAY_T>> &&
                                      std::is_arithmetic_v<babel::CONCEPTS::type_in<DECAY_U>> ) )
            {
                T ArrayLike;
                std::transform(std::begin(data), std::end(data), std::back_inserter(ArrayLike),
                               []< typename LambdaType >(LambdaType &&Data) {
                                   return asType<std::decay_t<decltype(*std::begin(ArrayLike))>>(
                                           std::forward<LambdaType>(Data));
                               });
                return ArrayLike;
            }
        } else if constexpr ( std::is_same_v<DECAY_T, DECAY_U> )
        {
            return std::forward<U>(data);
        } else
        {
            return static_cast<T>(std::forward<U>(data));
        }

    }


    /**
    *  @brief  Swap values.
    *  \Example_1 a = 3, b = 7, swap(a, b) -> a = 7, b = 3
    *  @param  lhs Left object to swap
    *  @param  rhs Right object to swap
    *  @return No return
    */
    template< typename T >
    void swap(T &lhs, T &rhs) noexcept
    {
        T temp = std::move(lhs);
        lhs = std::move(rhs);
        rhs = std::move(temp);
    }


}

#endif
