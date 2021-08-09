// Copyright [2021] <Wojtek>"
#ifndef BABLIB_WRAPER_HPP_
#define BABLIB_WRAPER_HPP_

#include <utility>
#include "concepts/concepts.hpp"

namespace babel::WRAPER{
    template< typename T >
    class wrap
    {
        T m_data;
    public:
        constexpr wrap() = default;

        constexpr ~wrap() = default;

        constexpr explicit wrap(T &&data) noexcept: m_data(std::move(data))
        { }

        constexpr explicit wrap(const T &data) noexcept: m_data(data)
        { }


        constexpr wrap(const wrap &other) noexcept: m_data(other.m_data)
        { }

        constexpr wrap(wrap &&other) noexcept: m_data(std::move(other.m_data))
        { }

        /**
*  @brief  Emplace data in wraper with T(args...)
 *  \Example_1 T = std::pair<int, int> -> emplace(std::make_pair<int, int>(20, 12)) -> m_data = std::pair<int, int>(std::make_pair<int, int>(20, 12))
*  @param  Arguments to constructor T
*  @return Return m_data& in wraper
*/
        template< typename ... Args >
        constexpr T &emplace(Args &&... args) noexcept
        {
            m_data = T(std::forward<Args>(args)...);
            return m_data;
        }

        /**
*  @brief Get m_data stored in wraper
*  @return Return m_data& in wraper
*/
        [[nodiscard]] constexpr T &get() noexcept
        {
            return m_data;
        }


        /**
*  @brief Get  const m_data stored in wraper
*  @return Return const m_data& in wraper
*/
        [[nodiscard]] constexpr const T &get() const noexcept
        {
            return m_data;
        }

        /**
*  @brief Get m_data stored in wraper
*  @return Return m_data& in wraper
*/
        [[nodiscard]] constexpr T &operator*() noexcept
        {
            return m_data;
        }

        /**
*  @brief Get  const m_data stored in wraper
*  @return Return const m_data& in wraper
*/
        [[nodiscard]] constexpr const T &operator*() const noexcept
        {
            return m_data;
        }

        /**
*  @brief Get  pointer to  m_data stored in wraper
*  @return Return T* m_data in wraper
*/
        [[nodiscard]] constexpr T *Pointer() noexcept
        {
            return &m_data;
        }

        /**
*  @brief Get  const pointer to  m_data stored in wraper
*  @return Return const T* m_data in wraper
*/
        [[nodiscard]] constexpr const T *Pointer() const noexcept
        {
            return &m_data;
        }


        /**
*  @brief Get m_data stored in wraper
*  @return Return m_data& in wraper
*/
        constexpr auto operator->() noexcept
        {
            return &m_data;
        }

        /**
*  @brief Get  const m_data stored in wraper
*  @return Return const m_data& in wraper
*/
        constexpr auto operator->() const noexcept
        {
            return &m_data;
        }


        /**
*  @brief If type T has member Size return m_data.size()
         *  \Example_1 T = std::vector<int> = {0, 1 , 3} , size() -> 3
*  @return Return size of m_data
*/
        template< typename U = T >
        requires ( babel::CONCEPTS::IS_SAME<U, T> && babel::CONCEPTS::MEMBER::HAS_SIZE<U> )
        [[nodiscard]] constexpr size_t size() const
        {
            if constexpr ( babel::CONCEPTS::IS_NOT_POINTER<U> )
                return m_data.size();
            else
                return m_data->size();
        }

        constexpr wrap<T> &operator=(const wrap<T> &other) noexcept
        {
            m_data = other.m_data;
            return *this;
        }

        constexpr wrap<T> &operator=(wrap<T> &&other) noexcept
        {
            m_data = std::move(other.m_data);
            return *this;
        }

        template< typename U = T >
        requires ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<U, T> && babel::CONCEPTS::IS_NOT_SAME<U, wrap<T>> )
        constexpr wrap<T> &operator=(U &&data) noexcept
        {
            m_data = std::forward<U>(data);
            return *this;
        }
    };
}  // namespace babel::WRAPER
#endif  // BABLIB_WRAPER_HPP_
