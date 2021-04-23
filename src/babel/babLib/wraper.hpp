#ifndef BABEL_WRAPER
#define BABEL_WRAPER

#include "must_have.hpp"

namespace babel::WRAPER{
    template< typename T >
    class wrap
    {
        T _data;
    public:
        constexpr wrap() noexcept: _data()
        { }

        template< typename U = T >
        requires ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<U, T> && babel::CONCEPTS::IS_NOT_SAME<U, wrap<T>> )
        constexpr wrap(U &&data) noexcept: _data(std::forward<U>(data)) //NOLINT
        { }

        constexpr wrap(const wrap &other) noexcept: _data(other._data)
        { }

        constexpr wrap(wrap &&other) noexcept: _data(std::move(other._data))
        { }

        template< typename ... Args >
        constexpr T &emplace(Args &&... args) noexcept
        {
            _data = T(std::forward<Args>(args)...);
            return _data;
        }

        [[nodiscard]] constexpr T &get() noexcept
        {
            return _data;
        }

        [[nodiscard]] constexpr const T &get() const noexcept
        {
            return _data;
        }

        [[nodiscard]] constexpr T &operator*() noexcept
        {
            return _data;
        }

        [[nodiscard]] constexpr const T &operator*() const noexcept
        {
            return _data;
        }

        [[nodiscard]] constexpr T *Pointer() noexcept
        {
            return &_data;
        }

        [[nodiscard]] constexpr const T *Pointer() const noexcept
        {
            return &_data;
        }

        constexpr auto operator->() noexcept
        {
            return &_data;
        }

        constexpr auto operator->() const noexcept
        {
            return &_data;
        }

        template< typename U = T >
        requires ( babel::CONCEPTS::IS_SAME<U, T> && babel::CONCEPTS::MEMBER::HAS_SIZE<U> )
        [[nodiscard]] constexpr size_t size() const
        {
            if constexpr ( babel::CONCEPTS::IS_NOT_POINTER<U> )
                return _data.size();
            else
                return _data->size();
        }

        constexpr wrap<T> &operator=(const wrap<T> &other) noexcept
        {
            _data = other._data;
            return *this;
        }

        constexpr wrap<T> &operator=(wrap<T> &&other) noexcept
        {
            _data = std::move(other._data);
            return *this;
        }

        template< typename U = T >
        requires ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<U, T> && babel::CONCEPTS::IS_NOT_SAME<U, wrap<T>> )
        constexpr wrap<T> &operator=(U &&data) noexcept
        {
            _data = std::forward<U>(data);
            return *this;
        }

    };
}
#endif