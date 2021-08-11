// Copyright [2021] <Wojtek>"
#ifndef BABLIB_VARIADIC_HPP_
#define BABLIB_VARIADIC_HPP_

#include <vector>
#include "concepts/concepts.hpp"

namespace babel::VARIADIC{
    template< typename Type, typename Container = std::vector<Type> >
    requires(babel::CONCEPTS::IS_NOT_ANY_VOID<Type>)
    class holder
    {
        Container m_hold;

        template< typename U = Type >
        requires(std::is_same_v<std::decay_t<U>, std::decay_t<Type>>)
        constexpr void _put(U &&_a1) noexcept
        {
            m_hold.emplace_back(std::forward<U>(_a1));
        }

        template< typename U = Type, typename ... Args >
        requires(std::is_same_v<std::decay_t<U>, std::decay_t<Type>>)
        constexpr void _put(U &&_a1, Args &&...args) noexcept
        {
            _put(std::forward<U>(_a1));
            _put(std::forward<Args>(args)...);
        }

    public:
        constexpr holder() = default;

        constexpr holder(const holder &other) noexcept
        {
            m_hold = other.m_hold;
        }


        constexpr holder(holder &&other) noexcept
        {
            m_hold = std::move(other.m_hold);
        }

        template< typename T = Type >
        requires ( !std::is_same_v<std::decay_t<T>, std::decay_t<holder>> )
        constexpr explicit holder(T &&arg) noexcept //NOLINT
        {
            _put(std::forward<T>(arg));
        }

        template< typename T = Type, typename ... Hold >
        requires ( !std::is_same_v<std::decay_t<T>, std::decay_t<holder>> )
        constexpr explicit holder(T &&arg, Hold &&... args) noexcept
        {
            _put(std::forward<T>(arg));
            _put(std::forward<Hold>(args)...);
        }

        constexpr holder &operator=(const holder &other) noexcept
        {
            m_hold = other.m_hold;
            return *this;
        }

        constexpr holder &operator=(holder &&other) noexcept
        {
            m_hold = std::move(other.m_hold);
            return *this;
        }

        constexpr Type &operator[](const size_t index)
        {
            return m_hold[index];
        }

        constexpr const Type &operator[](const size_t index) const
        {
            return m_hold[index];
        }

        constexpr auto operator->()
        {
            return &m_hold;
        }

        constexpr auto operator->() const
        {
            return &m_hold;
        }

        /**
         *  @brief  Return vector of storage parameter
         *  @return Return vector&
         */
        constexpr Container &get() noexcept
        {
            return m_hold;
        }

        /**
         *  @brief  Return vector of storage parameter
         *  @return Return const vector&
         */
        constexpr const Container &get() const noexcept
        {
            return m_hold;
        }
    };
}  // namespace babel::VARIADIC

#endif  // BABLIB_VARIADIC_HPP_
