#ifndef BABEL_VARIADIC
#define BABEL_VARIADIC

#include "must_have.hpp"

namespace babel::VARIADIC{
    template< typename Type >
    requires(babel::CONCEPTS::IS_NOT_ANY_VOID<Type>)
    class holder
    {
        std::vector<Type> _hold;

        template< typename U = Type >
        requires (std::is_same_v<std::decay_t<U>, std::decay_t<Type>>)
        constexpr void _put(U &&_a1) noexcept
        {
            _hold.push_back(std::forward<U>(_a1));
        }

        template< typename U = Type, typename ... Args >
        requires (std::is_same_v<std::decay_t<U>, std::decay_t<Type>>)
        constexpr void _put(U &&_a1, Args &&...args) noexcept
        {
            _put(std::forward<U>(_a1));
            _put(std::forward<Args>(args)...);
        }

    public:
        constexpr holder() = default;


        constexpr holder(const holder &other) noexcept
        {
            _hold = other._hold;
        }


        constexpr holder(holder &&other) noexcept
        {
            _hold = std::move(other._hold);
        }

        template< typename T = Type>
        requires(!std::is_same_v<std::decay_t<T>, std::decay_t<holder>>)
        constexpr explicit holder(T&& arg) noexcept //NOLINT
        {
            _put(std::forward<T>(arg));
        }

        template< typename T = Type, typename ... Hold>
        requires(!std::is_same_v<std::decay_t<T>, std::decay_t<holder>>)
        constexpr explicit holder(T&& arg, Hold &&... args) noexcept
        {
            _put(std::forward<T>(arg));
            _put(std::forward<Hold>(args)...);
        }




        constexpr holder &operator=(const holder &other) noexcept
        {
            _hold = other._hold;
            return *this;
        }

        constexpr holder &operator=(holder &&other) noexcept
        {
            _hold = std::move(other._hold);
            return *this;
        }

        constexpr Type &operator[](const size_t index)
        {
            return _hold[index];
        }

        constexpr const Type &operator[](const size_t index) const
        {
            return _hold[index];
        }

        constexpr auto operator->()
        {
            return &_hold;
        }

        constexpr auto operator->() const
        {
            return &_hold;
        }

        /**
         *  @brief  Return vector of storage parameter
         *  @return Return vector&
         */
        constexpr std::vector<Type> &get() noexcept
        {
            return _hold;
        }

        /**
         *  @brief  Return vector of storage parameter
         *  @return Return const vector&
         */
        constexpr const std::vector<Type> &get() const noexcept
        {
            return _hold;
        }
    };
}

#endif