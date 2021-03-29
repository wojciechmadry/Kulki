#ifndef BABEL_VARIADIC
#define BABEL_VARIADIC

#include "must_have.hpp"

namespace babel::VARIADIC {
    template<typename Type>
    requires(babel::CONCEPTS::IS_NOT_ANY_VOID<Type>)
    class holder
    {
        CONTAINER::dynamic_array<Type> _hold;

        template<typename U = Type>
        constexpr void _put(U &&_a1) noexcept
        {
            _hold.push_back(std::forward<U>(_a1));
        }

        template<typename U = Type, typename ... Args>
        constexpr void _put(U &&_a1, Args &&...args) noexcept
        {
            _put(std::forward<U>(_a1));
            _put(std::forward<Args>(args)...);
        }
        template<typename U>
        using decay = typename std::decay_t<U>;
    public:
        constexpr holder() = default;

        template<typename ... Hold>
        constexpr explicit holder(Hold &&... args) noexcept
        {
            _put(std::forward<Hold>(args)...);
        }


        constexpr holder(const holder &other) noexcept
        {
            _hold = other._hold;
        }

        constexpr holder(holder &&other) noexcept
        {
            _hold = std::move(other._hold);
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
        constexpr CONTAINER::dynamic_array<Type> &get() noexcept
        {
            return _hold;
        }

        /**
         *  @brief  Return vector of storage parameter
         *  @return Return const vector&
         */
        constexpr const CONTAINER::dynamic_array<Type> &get() const noexcept
        {
            return _hold;
        }
    };
}

#endif