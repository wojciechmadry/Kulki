// Copyright [2021] <Wojtek>"
#ifndef BABLIB_OPTIONAL_HPP_
#define BABLIB_OPTIONAL_HPP_

#include <variant>
#include "concepts/concepts.hpp"

namespace babel::OPT{
    template< typename T >
    requires ( babel::CONCEPTS::IS_NOT_SAME<T, void> &&
               babel::CONCEPTS::IS_DESTRUCTIBLE<T> &&
               babel::CONCEPTS::IS_NOT_SAME<T, std::monostate> )
    class optional
    {
        std::variant<T, std::monostate> m_storage;
    public:
        constexpr optional() noexcept: m_storage(std::monostate())
        { };


        template< typename U = T >
        requires ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<U, T> && babel::CONCEPTS::IS_NOT_SAME<U, optional> )
        constexpr optional(U &&value) noexcept : m_storage(std::forward<U>(value)) //NOLINT
        { }


        constexpr optional(const optional &other) noexcept: m_storage(other.m_storage)
        { }

        constexpr optional(optional &&other) noexcept: m_storage(std::move(other.m_storage))
        { }

        ~optional() noexcept
        { this->reset(); }


        /**
*  @brief  Check if class stored value
*  @return Return True if value is stored, false otherwise
*/
        [[nodiscard]]constexpr bool has_value() const noexcept
        {
            return std::holds_alternative<T>(m_storage);
        }

        constexpr optional &operator=(const optional &other) noexcept
        {
            m_storage = other.m_storage;
            return *this;
        }

        constexpr optional &operator=(optional &&other) noexcept
        {
            m_storage = std::move(other.m_storage);
            return *this;
        }


        template< typename U = T >
        requires ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<U, T> && babel::CONCEPTS::IS_NOT_SAME<U, optional> )
        constexpr optional &operator=(U &&value) noexcept
        {
            m_storage = std::forward<U>(value);
            return *this;
        }

        /**
*  @brief  Check if class stored value
*  @return Return True if value is stored, false otherwise
*/
        constexpr explicit operator bool() const noexcept
        {
            return std::holds_alternative<T>(m_storage);
        }

        /**
*  @brief  Clear stored element
*  @return No return
*/
        constexpr void reset() noexcept
        {
            m_storage = std::monostate();
        }

        constexpr void swap(optional &other) noexcept
        {
            std::swap(m_storage, other.m_storage);
        }

        template< typename ... Args >
        constexpr void emplace(Args &&... arg) noexcept
        {
            m_storage = T(std::forward<Args>(arg)...);
        }

        /**
*  @brief  If optional has stored data than return it in otherwise return OR
 *  @param  OR Value to return is there no stored value
*  @return Return stored data or OR
*/
        template< typename T2 = T >
        requires(babel::CONCEPTS::IS_SAME_CONVERTIBLE<T2, T>)
        constexpr T value_or(T2 &&OR) noexcept
        {
            if ( std::holds_alternative<T>(m_storage) )
                return std::get<T>(m_storage);
            return static_cast<T>(OR);
        }

        /**
*  @return Return value stored in optional
*/
        [[nodiscard]] constexpr T &value() noexcept
        {
            return std::get<T>(m_storage);
        }

        /**
*  @return Return const value stored in optional
*/
        [[nodiscard]] constexpr const T &value() const noexcept
        {
            return std::get<T>(m_storage);
        }

        [[nodiscard]] constexpr T *operator->() noexcept
        {
            return &std::get<T>(m_storage);
        }

        [[nodiscard]] constexpr const T *operator->() const noexcept
        {
            return &std::get<T>(m_storage);
        }

        [[nodiscard]] constexpr T &operator*() noexcept
        {
            return std::get<T>(m_storage);
        }

        [[nodiscard]] constexpr T &operator*() const noexcept
        {
            return std::get<T>(m_storage);
        }
    };
}  // namespace babel::OPT

#endif  // BABLIB_OPTIONAL_HPP_
