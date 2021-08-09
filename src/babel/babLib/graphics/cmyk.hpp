// Copyright [2021] <Wojtek>"
#ifndef BABLIB_GRAPHICS_CMYK_HPP_
#define BABLIB_GRAPHICS_CMYK_HPP_

#include "../algorithm/algorithm.hpp"

namespace babel::GRAPHICS{
    //------------------CMYK---------------
    class cmyk
    {
    public:
        using byte = uint8_t;
    private:
        std::array<byte, 4> m_CMYK; //NOLINT

        [[nodiscard]] static constexpr byte _max(const byte Value) noexcept
        {
            return Value > 100 ? static_cast<byte>(100) : Value;
        }

        constexpr void _check_and_fix() noexcept
        {
            m_CMYK[0] = _max(m_CMYK[0]);
            m_CMYK[1] = _max(m_CMYK[1]);
            m_CMYK[2] = _max(m_CMYK[2]);
            m_CMYK[3] = _max(m_CMYK[3]);
        }

        constexpr void _set(const byte C, const byte M, const byte Y, const byte K) noexcept
        {
            m_CMYK[0] = _max(C);
            m_CMYK[1] = _max(M);
            m_CMYK[2] = _max(Y);
            m_CMYK[3] = _max(K);
        }

        constexpr void _set_at(const byte index, const byte Value) noexcept
        {
            m_CMYK[index] = _max(Value);
        }

    public:
        constexpr explicit cmyk(const byte C = 0, const byte M = 0, const byte Y = 0, //NOLINT
                                const byte K = 0) noexcept //NOLINT
        {
            _set(C, M, Y, K);
        }

        constexpr cmyk(const cmyk &other) noexcept = default;


        [[nodiscard]] constexpr const std::array<byte, 4> &get_array() const noexcept
        {
            return m_CMYK;
        }

        [[nodiscard]] constexpr byte C() const noexcept
        {
            return m_CMYK[0];
        }

        [[nodiscard]] constexpr byte M() const noexcept
        {
            return m_CMYK[1];
        }

        [[nodiscard]] constexpr byte Y() const noexcept
        {
            return m_CMYK[2];
        }

        [[nodiscard]] constexpr byte K() const noexcept
        {
            return m_CMYK[3];
        }


        [[nodiscard]] constexpr byte operator[](const byte index) const
        {
            if ( index > 3 )
                throw std::out_of_range("Array out of range.");
            return m_CMYK[index];
        }

        constexpr void set(const byte C, const byte M, const byte Y, const byte K) noexcept
        {
            _set(C, M, Y, K);
        }

        constexpr void set_C(const byte C) noexcept
        {
            _set_at(0, C);
        }

        constexpr void set_M(const byte M) noexcept
        {
            _set_at(1, M);
        }


        constexpr void set_Y(const byte Y) noexcept
        {
            _set_at(2, Y);
        }

        constexpr void set_K(const byte K) noexcept
        {
            _set_at(3, K);
        }
    };


}  // namespace babel::GRAPHICS

#endif  // BABLIB_GRAPHICS_CMYK_HPP_
