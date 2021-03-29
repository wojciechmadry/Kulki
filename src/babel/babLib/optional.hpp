#ifndef babel_OPT
#define babel_OPT

#include "must_have.hpp"

namespace babel::OPT {
    template<typename T>
    requires (babel::CONCEPTS::IS_NOT_SAME<T, void> &&
            babel::CONCEPTS::IS_DESTRUCTIBLE<T> &&
            babel::CONCEPTS::IS_NOT_SAME<T, std::monostate>)
    class optional
    {
        std::variant<T, std::monostate> _storage;
    public:
        constexpr optional() noexcept: _storage(std::monostate())
        {};


        template<typename U = T>
        requires (babel::CONCEPTS::IS_SAME_CONVERTIBLE<U, T> && babel::CONCEPTS::IS_NOT_SAME<U, optional>)
        constexpr explicit optional(U &&value) noexcept : _storage(std::forward<U>(value)) //NOLINT
        {}


        constexpr optional(const optional &other) noexcept: _storage(other._storage)
        {}

        constexpr optional(optional &&other) noexcept: _storage(std::move(other._storage))
        {}

        ~optional() noexcept
        { this->reset(); }

        [[nodiscard]]constexpr bool has_value() const noexcept
        {
            return std::holds_alternative<T>(_storage);
        }

        constexpr optional &operator=(const optional &other) noexcept
        {
            _storage = other._storage;
            return *this;
        }

        constexpr optional &operator=(optional &&other) noexcept
        {
            _storage = std::move(other._storage);
            return *this;
        }


        template<typename U = T>
        requires (babel::CONCEPTS::IS_SAME_CONVERTIBLE<U, T> && babel::CONCEPTS::IS_NOT_SAME<U, optional>)
        constexpr optional &operator=(U &&value)
        {
            _storage = std::forward<U>(value);
            return *this;
        }

        constexpr explicit operator bool() const
        {
            return std::holds_alternative<T>(_storage);
        }

        constexpr void reset() noexcept
        {
            _storage = std::monostate();
        }

        constexpr void swap(optional &other) noexcept
        {
            auto temporary = std::move(other._storage);
            other._storage = std::move(_storage);
            _storage = std::move(temporary);
        }

        template<typename ... Args>
        constexpr void emplace(Args &&... arg)
        {
            _storage = T(std::forward<Args>(arg)...);
        }

        template<typename T2 = T>
        requires(babel::CONCEPTS::IS_SAME_CONVERTIBLE<T2, T>)
        constexpr T value_or(T2 &&OR)
        {
            if (std::holds_alternative<T>(_storage))
                return std::get<T>(_storage);
            return static_cast<T>(OR);
        }

        constexpr T &value()
        {
            return std::get<T>(_storage);
        }

        constexpr const T &value() const
        {
            return std::get<T>(_storage);
        }

        constexpr T *operator->()
        {
            return &std::get<T>(_storage);
        }

        constexpr const T *operator->() const
        {
            return &std::get<T>(_storage);
        }

        constexpr T &operator*()
        {
            return std::get<T>(_storage);
        }

        constexpr T &operator*() const
        {
            return std::get<T>(_storage);
        }
    };
}

#endif