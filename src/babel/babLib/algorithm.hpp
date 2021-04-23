#ifndef BABEL_ALGO
#define BABEL_ALGO

#include "math.hpp"

namespace babel::ALGO{

    template< typename T >
    constexpr T string_to(const std::string &_string)
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
     *  @param  v Number can be positive or negative.
     * Must be arithmetic
     *  @return Return absolute value of number
     */
    template< typename T >
    requires ( !babel::CONCEPTS::IS_CONTAINER<T> )
    constexpr inline T abs(const T v)
    {
        return ( v >= 0 ) ? v : -v;
    }

    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
    requires(babel::CONCEPTS::IS_CONTAINER<T>)
    constexpr void abs(T &v)
    {
        std::for_each(std::begin(v), std::end(v), [](U &val) { val = std::abs(val); });
    }

    /**
   *  @brief  Count element in data struct
   *  @param  begin Iterator to begin
   *  @param  end Iterator to end
   *  @param  element Element we want to count
   *  @return Return number of element in data structure
   */
    template< typename Vec, typename Type = typename babel::CONCEPTS::type_in<Vec>::type >
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
*  @param  n Number
*  @return Return 1 if n is automorphic or 0 if not.
*/
    constexpr bool is_automorphic(int64_t n)
    {
        n = abs(n);
        uint16_t digits = 0;
        for ( int64_t cpy = n ; cpy > 1 ; ++digits )
            cpy /= 10;
        return ( static_cast<int64_t>(pow(n, 2)) % static_cast<int64_t>(pow(10, digits)) ) == n;
    }

    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
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
        return std::move(minimaxi);
    }


    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
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


    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
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

    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
    requires ( babel::CONCEPTS::IS_CONTAINER<T> && babel::CONCEPTS::IS_FLOATING_POINT<U> )
    constexpr void normalize(T &container) noexcept
    {
        auto mm = babel::ALGO::find_min_max(container);
        std::for_each(std::begin(container), std::end(container), [&mm](U &data) {
            data = babel::MATH::map(data, mm.first, mm.second, 0.0, 1.0);
        });
    }

    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr U sum(const T &container) noexcept
    {
        auto begin = std::begin(container);
        auto end = std::end(container);
        auto first = *begin;
        ++begin;
        return std::accumulate(begin, end, first);
    }

    template< typename T, typename U = typename babel::CONCEPTS::type_in<T>::type >
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

    template< typename Container, typename T = typename babel::CONCEPTS::type_in<Container>::type >
    requires ( babel::CONCEPTS::IS_FLOATING_POINT<T> && babel::CONCEPTS::IS_CONTAINER<Container> )
    std::vector<std::complex<T>> FFT(const Container &fn) noexcept
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
                auto t = std::polar(1.0, -2.0 * std::numbers::pi * k / N) * odd[k];
                fn[k] = even[k] + t;
                fn[k + N / 2] = even[k] - t;
            }
        };

        std::vector<std::complex<T>> res(std::begin(fn), std::end(fn));
        ditfft2(res);
        return res;
    }

    template< typename T >
    void swap(T &lhs, T &rhs) noexcept
    {
        T temp = std::move(lhs);
        lhs = std::move(rhs);
        rhs = std::move(temp);
    }

    template< typename T >
    requires ( std::is_signed_v<T> || std::is_unsigned_v<T> )
    constexpr auto signed_unsigned_conv(const T data) noexcept
    {
        return static_cast< typename babel::CONCEPTS::type_of_number<sizeof(data), !std::is_signed_v<T>>::type >(data);
    }

    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container drop(const Container &cont, const size_t n) noexcept
    {
        if ( n > cont.size() )
            return { };
        return {std::begin(cont) + n, std::end(cont)};
    }

    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container take(const Container &cont, const size_t n) noexcept
    {
        if ( n >= cont.size() )
            return cont;
        return {std::begin(cont), std::begin(cont) + n};
    }

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

    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container drop_last(const Container &cont, const size_t n) noexcept
    {
        if ( n > cont.size() )
            return { };
        return {std::begin(cont), std::end(cont) - n};
    }


    template< typename Container >
    requires babel::CONCEPTS::IS_CONTAINER<Container>
    [[nodiscard]] Container take_last(const Container &cont, const size_t n) noexcept
    {
        if ( n >= cont.size() )
            return cont;
        return {std::end(cont) - n, std::end(cont)};
    }

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

    template< typename Container, typename T = typename babel::CONCEPTS::type_in<Container>::type >
    requires babel::CONCEPTS::IS_LIKE_VECTOR<Container>
    [[nodiscard]] std::vector<std::pair<size_t, T>> enumerate(const Container &cont) noexcept
    {
        std::vector<std::pair<size_t, T>> res;
        for ( size_t i = 0 ; i < cont.size() ; ++i )
            res.emplace_back(i, cont[i]);
        return res;
    }

    template< typename Container, typename T = typename babel::CONCEPTS::type_in<Container>::type >
    requires babel::CONCEPTS::IS_LIKE_VECTOR<Container>
    [[nodiscard]] std::vector<std::pair<size_t, T>> run_length_encode(const Container &cont) noexcept
    {
        std::vector<std::pair<size_t, T>> res;
        if ( cont.size() == 1 )
            return {{1, cont[0]}};
        else if (cont.size() == 0)
            return {};
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

}


#endif