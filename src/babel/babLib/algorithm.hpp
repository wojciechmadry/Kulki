#ifndef BABEL_ALGO
#define BABEL_ALGO

#include "math.hpp"

namespace babel::ALGO{

    /**
 *  @brief  Convert string to number (float, int, etc...)
     *  \EXAMPLE_1 string_to<float>("3.14") -> float(3.14)
 *  @param  _string Number in string
 *  @return Return string convert to number
 */
    template< typename T >
    constexpr inline T string_to(const std::string &_string)
    {
        if constexpr ( babel::CONCEPTS::IS_SAME<T, int> )
            return std::stoi(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<T, long> )
            return std::stol(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<T, long long> )
            return std::stoll(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<T, unsigned long long> )
            return std::stoull(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<T, unsigned long> )
            return std::stoul(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<T, float> )
            return std::stof(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<T, double> )
            return std::stod(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<T, long double> )
            return std::stold(_string);
        if constexpr ( babel::CONCEPTS::IS_SAME<T, unsigned int> )
            return static_cast<unsigned int>(std::stoul(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<T, char> )
            return static_cast<char>(std::stoi(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<T, unsigned char> )
            return static_cast<unsigned char>(std::stoul(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<T, short> )
            return static_cast<short>(std::stoi(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<T, unsigned short> )
            return static_cast<unsigned short>(std::stoul(_string));
        if constexpr ( babel::CONCEPTS::IS_SAME<T, bool> )
            return static_cast<bool>(std::stoul(_string));
        throw std::out_of_range("No visible conversion.");
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
    constexpr inline T abs(const T v)
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
        std::for_each(std::begin(v), std::end(v), [](U &val) { val = babel::ALGO::abs(val); });
    }

    /**
   *  @brief  Count element in data struct
     *  \EXAMPLE_1 {3, 1, 2, 1, 1} with element 1 -> 3, with element 2 -> 1
   *  @param  begin Iterator to begin
   *  @param  end Iterator to end
   *  @param  element Element we want to count
   *  @return Return number of element in data structure
   */
    template< typename Vec, typename Type = babel::CONCEPTS::type_in<Vec> >
    requires babel::CONCEPTS::IS_CONTAINER<Vec>
    constexpr size_t count(const Vec &Container, const Type &element)
    {
        size_t counter = 0;
        auto begin = std::begin(Container);
        auto end = std::end(Container);
        for ( ; begin != end ; ++begin )
            counter += ( *begin == element );
        return counter;
    }

    /**
   *  @brief  Count prediction element in data struct
     *  \EXAMPLE_1 {3,4,2,7,8,12,3} with prediction x > 5 -> 3
   *  @param  begin Iterator to begin
   *  @param  end Iterator to end
   *  @param  pr Is function that return 1 if element count or 0 in otherwise
   *  @return Return number of element in data structure
   */
    template< typename Vec, typename Pr >
    requires babel::CONCEPTS::IS_CONTAINER<Vec>
    constexpr size_t count_if(const Vec &Container, Pr prediction)
    {
        auto begin = std::begin(Container);
        auto end = std::end(Container);
        size_t counter = 0;
        for ( ; begin != end ; ++begin )
            if ( prediction(*begin) )
                ++counter;
        return counter;
    }

    /**
*  @brief  Check if number is automorphic
     *  \EXAMPLE_1 (25)^2 == 625 -> true
     *  \EXAMPLE_2 (76)^2 == 5776 -> true
*  @param  n Number
*  @return Return 1 if n is automorphic or 0 if not.
*/
    constexpr bool is_automorphic(int64_t n) noexcept
    {
        n = abs(n);
        uint16_t digits = 0;
        for ( int64_t cpy = n ; cpy > 1 ; ++digits )
            cpy /= 10;
        return ( static_cast<int64_t>(pow(static_cast<double>(n), 2.0)) % static_cast<int64_t>(pow(10, digits)) ) == n;
    }

    /**
 *  @brief  Find minimum and maximum value in data structure.
     *  \EXAMPLE_1 {3,1,-5,2,4,5} -> {-5, 5};
 *  @param  container Data structure of elements.
 *  @return Return pair MIN and MAX values in the data structure
 */
    template< typename T, typename U = babel::CONCEPTS::type_in<T> >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr std::pair<U, U> find_min_max(const T &container) noexcept
    {
        if ( container.size() == 0 )
            return { };
        auto begin = std::begin(container);
        auto end = std::end(container);
        std::pair<U, U> minimaxi = {*begin, *begin};
        ++begin;
        for ( ; begin != end ; ++begin )
            if ( *begin > minimaxi.second )
                minimaxi.second = *begin;
            else if ( *begin < minimaxi.first )
                minimaxi.first = *begin;
        return minimaxi;
    }

    /**
   *  @brief  Find minimum and maximum value in data structure.
   *  @param  container Data structure of elements.
   *  @return Return pointers pair MIN and MAX values in the data structure
   */
    template< typename T, typename U = babel::CONCEPTS::type_in<T> >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr std::pair<U *, U *> find_min_max_ptr(T &container) noexcept
    {
        if ( container.size() == 0 )
            return {nullptr, nullptr};
        auto begin = std::begin(container);
        auto end = std::end(container);
        std::pair<U *, U *> minimaxi = {&( *begin ), &( *begin )};
        ++begin;
        for ( ; begin != end ; ++begin )
            if ( *begin > *minimaxi.second )
                minimaxi.second = &( *begin );
            else if ( *begin < *minimaxi.first )
                minimaxi.first = &( *begin );
        return std::move(minimaxi);
    }


    /**
*  @brief  Calculate mean in data structure
     *  \EXAMPLE_1 {3,4,2} -> (3+4+2)/3 = 3
*  @param  container Data structure of elements.
*  @return Return mean value
*/
    template< typename T, typename U = babel::CONCEPTS::type_in<T> >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr U mean(const T &container) noexcept
    {
        if ( container.size() == 0 )
            return { };
        auto begin = std::begin(container);
        auto end = std::end(container);
        U Mean = *begin;
        ++begin;
        for ( ; begin != end ; ++begin )
            Mean += *begin;
        return Mean / static_cast<U>(container.size());
    }

    /**
*  @brief  Normalize data structure to 0 - 1
     *\Example_1 {0,3,12,5,-5,8,3} -> {0.294118, 0.470588, 1, 0.588235, 0, 0.764706, 0.470588}
*  @param  container Data structure to normalize
*  @return No return
*/

    template< typename T, typename U = babel::CONCEPTS::type_in<T> >
    requires ( babel::CONCEPTS::IS_CONTAINER<T> && babel::CONCEPTS::IS_FLOATING_POINT<U> )
    constexpr void normalize(T &container) noexcept
    {
        auto mm = babel::ALGO::find_min_max(container);
        std::for_each(std::begin(container), std::end(container), [&mm](U &data) {
            data = babel::MATH::map<U>(data, mm.first, mm.second, 0.0, 1.0);
        });
    }

    /**
*  @brief  Sum all element in data structure
     *  \Example_1 {3,4,2} -> 9
     *  \Example_2 {-2, 5, 5} -> 8
*  @param  container Data structure of elements.
*  @return Return sum of elements
*/
    template< typename T, typename U =babel::CONCEPTS::type_in<T> >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr U sum(const T &container) noexcept
    {
        auto begin = std::begin(container);
        auto end = std::end(container);
        auto first = *begin;
        ++begin;
        return std::accumulate(begin, end, first);
    }

    /**
*  @brief  Find the closest element to the mean value.
     *  \Example_1 {0.0, 1.0, 2.0, 3.0}, mean = 6/4 = 1.5, function return 2.0
     *  \Example_2 {1.0, 5.0, 9.0}, mean = 15/3 = 5, function return 5.0
*  @param  container Data structure of elements.
*  @return Return closest element to the mean value
*/
    template< typename T, typename U = babel::CONCEPTS::type_in<T> >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr U closest_to_mean(const T &container)
    {
        if ( container.size() == 0 )
            return { };
        auto _mean = mean(container);
        auto begin = std::begin(container);
        auto end = std::end(container);
        U closest = *begin;
        U diff = babel::MATH::abs(_mean - *begin);
        ++begin;
        for ( ; begin != end ; ++begin )
        {
            U temp = babel::MATH::abs(_mean - *begin);
            if ( temp < diff )
            {
                diff = temp;
                closest = *begin;
            }
        }
        return closest;
    }

    /**
*  @brief  Calculate FFT from probes.
*  @param  container Data structure of elements.
*  @return Return FFT
*/
    template< typename Container, typename T = babel::CONCEPTS::type_in<Container> >
    requires ( babel::CONCEPTS::IS_FLOATING_POINT<T> && babel::CONCEPTS::IS_CONTAINER<Container> )
    std::vector<std::complex<T>> FFT(const Container &probes) noexcept
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
*  @brief  Drop n's first element from container
*  \Example_1 cont = {4,7,8}, n = 2 -> { 8}
*  \Example_2 cont = {4,7,8}, n = 1 -> {7, 8}
*  \Example_3 cont = {4,7,8}, n = 3 -> { }
*  @param  cont Data structure
*  @param  n Delete n's first element from cont
*  @return Return copy of container without first n elements
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container drop(const Container &cont, const size_t n) noexcept
    {
        if ( n > cont.size() )
            return { };
        return {std::begin(cont) + static_cast<int64_t>(n), std::end(cont)};
    }

    /**
*  @brief  Take n's first element from container
*  \Example_1 cont = {4,7,8}, n = 2 -> {4, 7}
*  \Example_2 cont = {4,7,8}, n = 1 -> {7}
*  \Example_3 cont = {4,7,8}, n = 5 -> {4, 7, 8}
*  @param  cont Data structure
*  @param  n Take n's first element from cont
*  @return Return n first elements
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container take(const Container &cont, const size_t n) noexcept
    {
        if ( n >= cont.size() )
            return cont;
        return {std::begin(cont), std::begin(cont) + static_cast<int64_t>(n)};
    }

    /**
*  @brief  Repeat container n's times
*  \Example_1 cont = {4,7,8}, n = 2 -> {4,7,8, 4,7,8}
*  \Example_2 cont = {4,7,8}, n = 1 -> {4,7,8}
*  \Example_3 cont = {4,7,8}, n = 3 -> {4,7,8, 4,7,8 }
*  \Example_4 cont = {4,7,8}, n = 0 -> {4,7,8}
*  @param  cont Data structure
*  @param  n repeat
*  @return Return container repeated n times
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_LIKE_VECTOR<Container>
    [[nodiscard]] Container repeat(const Container &cont, const size_t n) noexcept
    {
        if ( n <= 1 )
            return cont;

        Container RET(n * cont.size());

        auto rbegin = std::begin(RET);
        auto cbegin = std::begin(cont);

        auto rend = std::end(RET);
        auto cend = std::end(cont);

        while ( rbegin != rend )
        {
            *rbegin = *cbegin;
            ++rbegin;
            ++cbegin;
            if ( cbegin == cend )
                cbegin = std::begin(cont);
        }

        return RET;
    }

    /**
*  @brief  Return container with n stride
*  \Example_1 cont = {0,1,2,3,4}, n = 0 -> {0,1,2,3,4}
*  \Example_2 cont = {0,1,2,3,4}, n = 1 -> {0,1,2,3,4}
*  \Example_3 cont = {0,1,2,3,4}, n = 2 -> {0, 2, 4 }
*  \Example_4 cont = {0,1,2,3,4}, n = 3 -> {0, 3}
*  @param  cont Data structure
*  @param  n Step
*  @return Return container with step = n
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_LIKE_VECTOR<Container>
    [[nodiscard]] Container stride(const Container &cont, const size_t n) noexcept
    {
        if ( n <= 1 )
            return cont;
        size_t k = 0;
        size_t index = 0;
        Container res(static_cast<size_t>(std::ceil(static_cast<double>(cont.size()) / static_cast<double>(n))));
        while ( k < res.size() )
        {
            res[k] = cont[index];
            ++k;
            index += n;
        }
        return res;
    }

    /**
*  @brief  Drop n'th index from data structure
*  \Example_1 cont = {0,1,2,3,4}, n = 0 -> {1,2,3,4}
*  \Example_2 cont = {0,1,2,3,4}, n = 1 -> {0,2,3,4}
*  \Example_3 cont = {0,1,2,3,4}, n = 2 -> {1,2,4}
*  \Example_4 cont = {0,1,2,3,4}, n = 3 -> {1,2,3}
*  @param  cont Data structure
*  @param  index Index of element what need to be drop
*  @return Return container with dropped element on index
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_LIKE_VECTOR<Container>
    [[nodiscard]] Container drop_idx(const Container &cont, const size_t index) noexcept
    {
        if ( cont.empty() || index >= cont.size() )
            return cont;
        Container res(cont.size() - 1);
        for ( size_t i = 0 ; i < index ; ++i )
            res[i] = cont[i];
        for ( size_t i = index + 1 ; i < cont.size() ; ++i )
            res[i - 1] = cont[i];
        return res;
    }

    /**
*  @brief  Drop n's last element from container
* \Example_1 cont = {4,7,8}, n = 1 -> {4, 7}
*  \Example_2 cont = {4,7,8}, n = 2 -> {4}
*  \Example_3 cont = {4,7,8}, n = 3 -> { }
*  @param  cont Data structure
*  @param  n Delete n's last element from cont
*  @return Return copy of container without last n elements
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container drop_last(const Container &cont, const size_t n) noexcept
    {
        if ( n > cont.size() )
            return { };
        return {std::begin(cont), std::end(cont) - static_cast<int64_t>(n)};
    }


    /**
*  @brief  Take n's last element from container
*  \Example_1 cont = {4,7,8}, n = 1 -> {8}
*  \Example_2 cont = {4,7,8}, n = 2 -> {7, 8}
*  \Example_3 cont = {4,7,8}, n = 5 -> {4, 7, 8}
*  @param  cont Data structure
*  @param  n Take n's last element from cont
*  @return Return n last elements
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container take_last(const Container &cont, const size_t n) noexcept
    {
        if ( n >= cont.size() )
            return cont;
        return {std::end(cont) - static_cast<int64_t>(n), std::end(cont)};
    }

    /**
*  @brief  Take n last element from container periodically
*  \Example_1 cont = {0,1,2,3,4}, n = 5 -> {0,1,2,3,4}
*  \Example_2 cont = {0,1,2,3,4}, n = 6 -> {0,1,2,3,4,0}
*  \Example_3 cont = {0,1,2,3,4}, n = 7 -> {0,1,2,3,4,0,1}
*  @param  cont Data structure
*  @param  n Take n's cyclic element from cont
*  @return Return n cyclic element
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container take_cyclic(const Container &cont, const size_t n) noexcept
    {
        if ( n == cont.size() || cont.size() == 0 )
            return cont;
        Container res(n);
        auto N = cont.size();
        for ( size_t i = 0 ; i < res.size() ; ++i )
            res[i] = cont[i % N];
        return res;
    }

    /**
*  @brief  Replicate every element of container n times
*  \Example_1 cont = {0,1,2,3,4}, n = 1 -> {0,1,2,3,4}
*  \Example_2 cont = {0,1,2,3,4}, n = 2 -> {0, 0,1, 1,2, 2,3, 3,4, 4}
*  \Example_3 cont = {0,1,2,3,4}, n = 3 -> {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4}
*  @param  cont Data structure
*  @param  n Every element replicate n times
*  @return Return container with replicated elements
*/
    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container replicate_elems(const Container &cont, const size_t n) noexcept
    {
        if ( n == 0 )
            return { };
        else if ( n == 1 )
            return cont;

        Container res(n * cont.size());
        auto N = cont.size();
        size_t index = 0;
        for ( size_t i = 0 ; i < N ; ++i )
            for ( size_t j = 0 ; j < n ; ++j, ++index )
            {
                res[index] = cont[i];
            }
        return res;
    }

    /**
*  @brief  Enumerate every elements in container
*  \Example_1 cont = {0,1,2,3,4} -> {(0, 0),(1, 1),(2, 2),(3, 3),(4, 4)}
*  \Example_2 cont = {15, 6} -> {(0, 15), (1, 6)}
*  @param  cont Data structure
*  @return Return container of pair where first is enumerate from(0 to n-1) and second is element from cont
*/
    template< typename Container, typename T = babel::CONCEPTS::type_in<Container> >
    requires babel::CONCEPTS::IS_LIKE_VECTOR<Container>
    [[nodiscard]] std::vector<std::pair<size_t, T>> enumerate(const Container &cont) noexcept
    {
        std::vector<std::pair<size_t, T>> res;
        for ( size_t i = 0 ; i < cont.size() ; ++i )
            res.emplace_back(i, cont[i]);
        return res;
    }

    /**
*  @brief  Count repeated element in a row
*  \Example_1 cont = {0,0,0,1,2,1} -> {(3, 0),(1, 1),(1, 2),(1, 1)}
*  \Example_2 cont = {0,0,2,2,0,0,2,2} -> {(2, 0), (2, 2), (2, 0), (2, 2)}
*  @param  cont Data structure
*  @return Return container of pairs with counted element
*/
    template< typename Container, typename T = babel::CONCEPTS::type_in<Container> >
    requires babel::CONCEPTS::IS_LIKE_VECTOR<Container>
    [[nodiscard]] std::vector<std::pair<size_t, T>> run_length_encode(const Container &cont) noexcept
    {
        std::vector<std::pair<size_t, T>> res;
        if ( cont.size() == 1 )
            return {{1, cont[0]}};
        else if ( cont.size() == 0 )
            return { };
        size_t counter = 1;
        for ( size_t i = 1 ; i < cont.size() ; ++i )
            if ( cont[i] == cont[i - 1ull] )
                ++counter;
            else
            {
                res.emplace_back(counter, cont[i - 1ull]);
                counter = 1;
            }
        res.emplace_back(counter, cont[cont.size() - 1ull]);
        return res;
    }

    /**
*  @brief  Generate vector from start to end with step
*  \Example_1 range(0, 5, 2) -> {0, 2, 4}
*  \Example_2 range(0, 5, 1) -> {0, 1, 2, 3, 4}
*  \Example_3 range(0, -5, -2) -> {0, -2, -4}
*  \Example_4 range(0, -3, 1) -> {0, -1, -2}
*  \Example_5 range(5, 15, 0) -> {5}
*  \Example_6 start > end AND step > 0 OR start < end AND step < 0  -> {}
*  @param  start Where start
*  @param  end Where end
*  @param  step What step
*  @return Return vector
*/
    [[nodiscard]] std::vector<int64_t> range(int64_t start, int64_t end, int64_t step = 1) noexcept
    {
        if ( start > end && step == 1 )
            step = -1;
        if ( start == end || step == 0 )
            return {start};
        if ( ( start > end && step > 0 ) || ( start < end && step < 0 ) )
            return { };
        std::vector<int64_t> _res;
        if ( start < end )
            for ( ; start < end ; start += step )
            {
                _res.emplace_back(start);
            }
        else
            for ( ; start > end ; start += step )
            {
                _res.emplace_back(start);
            }
        return _res;

    }

    /**
*  @brief  Generate vector from 0 to end
*  \Example_1 range(3) -> {0, 1, 2}
*  \Example_2 range(-3) -> {0, -1, -2}
*  @param  end Where end
*  @return Return vector
*/
    [[nodiscard]] std::vector<int64_t> range(int64_t end) noexcept
    {
        return range(0, end);
    }

    /**
*  @brief  Generate vector of 0
*  \Example_1 zeros(2, 1) ->  {{0}, {0}}
*  \Example_2 zeros(1, 2) -> {{0, 0}}
*  @param  rows how many rows
*  @param  cols how many cols
*  @return Return 2D vector filled with 0
*/
    [[nodiscard]] std::vector<std::vector<int64_t>> zeros(const size_t rows, const size_t columns) noexcept
    {
        return std::vector<std::vector<int64_t>>(rows, std::vector<int64_t>(columns, 0));
    }

    /**
*  @brief  Generate vector of 0
*  \Example_1 zeros(2) ->  {0, 0}
*  \Example_2 zeros(3) -> {0, 0, 0}
*  @param  columns how many cols
*  @return Return 1D vector filled with 0
*/
    [[nodiscard]] std::vector<int64_t> zeros(const size_t columns) noexcept
    {
        return std::vector<int64_t>(columns, 0);
    }

    /**
*  @brief  Generate vector of 1
*  \Example_1 ones(2, 1) ->  {{1}, {1}}
*  \Example_2 ones(1, 2) -> {{1, 1}}
*  @param  rows how many rows
*  @param  cols how many cols
*  @return Return 2D vector filled with 1
*/
    [[nodiscard]] std::vector<std::vector<int64_t>> ones(const size_t rows, const size_t columns) noexcept
    {
        return std::vector<std::vector<int64_t>>(rows, std::vector<int64_t>(columns, 1));
    }

    /**
*  @brief  Generate vector of 1
*  \Example_1 zeros(2) ->  {1, 1}
*  \Example_2 zeros(3) -> {1, 1, 1}
*  @param  columns how many cols
*  @return Return 1D vector filled with 1
*/
    [[nodiscard]] std::vector<int64_t> ones(const size_t columns) noexcept
    {
        return std::vector<int64_t>(columns, 1);
    }

    /**
*  @brief  Convert from one type to another
*  \Example_1 T = std::string AND U is arithmetic -> std::to_string(data)
*  \Example_2 T is arithmetic AND U = std::string-> babel::ALGO::string_to<T>(data)
*  \Example_3 If T/U is base of U/T and T must be pointer !!! You can transform from one Base/Derived to Derived/Base. (using dynamic_cast<>)
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
               ( !std::is_same_v<ConvertFunction, void *> && babel::CONCEPTS::FUNCTION_RETURN<ConvertFunction, T, U> )
               || ( !std::is_same_v<ConvertFunction, void *> &&
                    babel::CONCEPTS::FUNCTION_RETURN<ConvertFunction, babel::CONCEPTS::type_in<DECAY_T>, babel::CONCEPTS::type_in<DECAY_U>> )
    )

    [[nodiscard]] constexpr inline DECAY_T asType(U &&data, ConvertFunction Func = nullptr) noexcept
    {
        if constexpr ( !std::is_same_v<ConvertFunction, void *> )
        {
            if constexpr ( babel::CONCEPTS::FUNCTION_RETURN<ConvertFunction, T, U> )
                return Func(std::forward<U>(data));
            else
            {
                T ArrayLike(data.size());
                if ( ArrayLike.size() == data.size() )
                {
                    auto begin = std::begin(ArrayLike);
                    auto ConvBegin = std::begin(data);
                    auto end = std::end(ArrayLike);
                    for ( ; begin != end ; ++begin, ++ConvBegin )
                    {
                        *begin = Func(*ConvBegin);
                    }
                }
                return ArrayLike;
            }
        } else if constexpr ( std::is_same_v<std::string, DECAY_T> && std::is_arithmetic_v<DECAY_U> )
            return std::to_string(data);
        else if constexpr ( std::is_arithmetic_v<DECAY_T> && std::is_same_v<std::string, DECAY_U> )
            return babel::ALGO::string_to<DECAY_T>(data);
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
                    return T {std::begin(data), std::end(data)};
                }
            } else if constexpr( ( std::is_same_v<std::string, babel::CONCEPTS::type_in<DECAY_U>> &&
                                   std::is_arithmetic_v<babel::CONCEPTS::type_in<DECAY_T>> )
                                 || ( std::is_same_v<std::string, babel::CONCEPTS::type_in<DECAY_T>> &&
                                      std::is_arithmetic_v<babel::CONCEPTS::type_in<DECAY_U>> ) )
            {
                T ArrayLike(data.size());
                if ( ArrayLike.size() == data.size() )
                {
                    auto begin = std::begin(ArrayLike);
                    auto ConvBegin = std::begin(data);
                    auto end = std::end(ArrayLike);
                    for ( ; begin != end ; ++begin, ++ConvBegin )
                    {
                        *begin = asType<decltype(*begin)>(*ConvBegin);
                    }
                }
                return ArrayLike;
            }
        } else if constexpr ( std::is_same_v<DECAY_T, DECAY_U> )
        {
            return std::forward<U>(data);
        } else
        {
            return static_cast<T>(data);
        }

    }


}


#endif
