#ifndef BABEL_ALGO_VECTOR
#define BABEL_ALGO_VECTOR

#include "../must_have.hpp"

namespace babel::ALGO::VECTOR{
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
        std::for_each(std::begin(Container), std::end(Container),
                      [&counter, &element](const auto &Data) mutable {
                          counter += (Data == element );
                      });
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
        size_t counter = 0;
        std::for_each(std::begin(Container), std::end(Container),
                      [&counter, prediction](const auto &Data) mutable {
                          if ( prediction(Data) )
                              ++counter;
                      });
        return counter;
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
        std::pair<U, U> minimaxi = {*begin, *begin};
        ++begin;
        std::for_each(begin, std::end(container), [&minimaxi](const U &Data) mutable {
            if ( Data > minimaxi.second )
                minimaxi.second = Data;
            else if ( Data < minimaxi.first )
                minimaxi.first = Data;
        });
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
        std::pair<U *, U *> minimaxi = {&( *begin ), &( *begin )};
        ++begin;
        std::for_each(begin, std::end(container), [&minimaxi](const U &Data) mutable {
            if ( Data > *minimaxi.second )
                minimaxi.second = &Data;
            else if ( Data < *minimaxi.first )
                minimaxi.first = &Data;
        });

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
        U Mean = std::accumulate(std::begin(container), std::end(container), 0);
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
        auto mm = babel::ALGO::VECTOR::find_min_max(container);
        std::for_each(std::begin(container), std::end(container), [&mm](U &data) {
            data = babel::ALGO::MATH::map<U>(data, mm.first, mm.second, 0.0, 1.0);
        });
    }

    /**
*  @brief  Sum all element in data structure (accumulate wraper)
     *  \Example_1 {3,4,2} -> 9
     *  \Example_2 {-2, 5, 5} -> 8
*  @param  container Data structure of elements.
*  @return Return sum of elements
*/
    template< typename T, typename U =babel::CONCEPTS::type_in<T> >
    requires babel::CONCEPTS::IS_CONTAINER<T>
    constexpr U sum(const T &container) noexcept
    {
        return std::accumulate(std::begin(container), std::end(container), 0);
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
        U diff = babel::ALGO::MATH::abs(_mean - *begin);
        ++begin;
        std::for_each(begin, end, [&closest, &diff, &_mean](const U &Data) {
            U temp = babel::ALGO::MATH::abs(_mean - Data);
            if ( temp < diff )
            {
                diff = temp;
                closest = Data;
            }
        });
        return closest;
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
    [[nodiscard]] Container drop(const Container &cont, const int64_t n) noexcept
    {
        if ( n > static_cast<int64_t>(cont.size()) || n <= 0 )
            return { };
        return {std::begin(cont) + static_cast<babel::CONCEPTS::IteratorAddType>(n), std::end(cont)};
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
    [[nodiscard]] Container take(const Container &cont, const uint64_t n) noexcept
    {
        if ( n >= cont.size() )
            return cont;
        return {std::begin(cont), std::begin(cont) + static_cast<babel::CONCEPTS::IteratorAddType>(n)};
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
        size_t index = 0;
        Container res(static_cast<size_t>(std::ceil(static_cast<double>(cont.size()) / static_cast<double>(n))));
        std::for_each(std::begin(res), std::end(res), [&cont, &index, n](auto &Value) mutable {
            Value = cont[index];
            index += n;
        });
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
        Container res;
        auto back_inserter = std::back_inserter(res);
        auto _get = [](const auto &data) { return data; };
        std::transform(std::begin(cont), std::begin(cont) + static_cast<babel::CONCEPTS::IteratorAddType>(index), back_inserter, _get);
        std::transform(std::begin(cont) + static_cast<babel::CONCEPTS::IteratorAddType>(index) + 1, std::end(cont), back_inserter, _get);
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
    [[nodiscard]] Container drop_last(const Container &cont, const uint64_t n) noexcept
    {
        if ( n > cont.size() )
            return { };
        return {std::begin(cont), std::end(cont) - static_cast<babel::CONCEPTS::IteratorAddType>(n)};
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
        return {std::end(cont) - static_cast<babel::CONCEPTS::IteratorAddType>(n), std::end(cont)};

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
        auto begin = std::begin(cont);
        std::for_each(std::begin(res), std::end(res), [&begin, &cont](auto &Data) {
            Data = *begin;
            ++begin;
            if ( begin == std::end(cont) )
                begin = std::begin(cont);
        });
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
        Container res;
        auto back_inserter = std::back_inserter(res);
        std::for_each(std::begin(cont), std::end(cont),
                      [&back_inserter, n](const auto &Data) mutable {
                          std::fill_n(back_inserter, n, Data);
                      });
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
        std::size_t index {0};
        std::vector<std::pair<std::size_t, T>> res;
        auto back_inserter = std::back_inserter(res);
        std::transform(std::begin(cont), std::end(cont), back_inserter,
                       [&index](const T &Data) mutable -> std::pair<std::size_t, T> {
                           return {index++, Data};
                       });
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
        if ( cont.size() == 0 )
            return { };
        auto begin = std::begin(cont);
        size_t counter = 1;
        std::for_each(std::begin(cont) + 1, std::end(cont),
                      [&begin, &counter, &res](const auto &Data) mutable {
                          if ( Data == *begin )
                              ++counter;
                          else
                          {
                              res.emplace_back(counter, *begin);
                              counter = 1;
                          }
                          ++begin;
                      });
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
    [[deprecated("Use ITERATOR::range instead.")]] [[nodiscard]] std::vector<int64_t> range(int64_t start, int64_t end, int64_t step = 1) noexcept
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
    [[deprecated("Use ITERATOR::range instead.")]][[nodiscard]] std::vector<int64_t> range(int64_t end) noexcept
    {
        int64_t start = 0;
        int64_t step = 1;
        if ( start > end )
            step = -1;
        if ( start == end )
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

}
#endif