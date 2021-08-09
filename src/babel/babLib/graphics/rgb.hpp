// Copyright [2021] <Wojtek>"
#ifndef BABLIB_GRAPHICS_RGB_HPP_
#define BABLIB_GRAPHICS_RGB_HPP_

#include "../algorithm/algorithm.hpp"

namespace babel::GRAPHICS{
    class rgb
    {
    public:
        using byte = uint8_t;
    private:
        std::array<byte, 3> m_RGB; //NOLINT
    public:
        constexpr explicit rgb(const byte R = 0, const byte G = 0, const byte B = 0) noexcept: m_RGB({R, G, B})
        { }

        constexpr rgb(const rgb &other) noexcept = default;

        [[nodiscard]]  constexpr std::array<byte, 3> &get_array() noexcept
        {
            return m_RGB;
        }

        [[nodiscard]] constexpr const std::array<byte, 3> &get_array() const noexcept
        {
            return m_RGB;
        }

        [[nodiscard]] constexpr byte &R() noexcept
        {
            return m_RGB[0];
        }

        [[nodiscard]] constexpr byte &G() noexcept
        {
            return m_RGB[1];
        }

        [[nodiscard]] constexpr byte &B() noexcept
        {
            return m_RGB[2];
        }

        [[nodiscard]] constexpr byte R() const noexcept
        {
            return m_RGB[0];
        }

        [[nodiscard]] constexpr byte G() const noexcept
        {
            return m_RGB[1];
        }

        [[nodiscard]] constexpr byte B() const noexcept
        {
            return m_RGB[2];
        }

        [[nodiscard]] constexpr byte &operator[](const byte index)
        {
            if ( index > 2 )
                throw std::out_of_range("Array out of range.");
            return m_RGB[index];
        }

        [[nodiscard]] constexpr byte operator[](const byte index) const
        {
            if ( index > 2 )
                throw std::out_of_range("Array out of range.");
            return m_RGB[index];
        }

        constexpr void set(const byte R, const byte G, const byte B) noexcept
        {
            m_RGB[0] = R;
            m_RGB[1] = G;
            m_RGB[2] = B;
        }
    };

}  // namespace babel::GRAPHICS

#endif  // BABLIB_GRAPHICS_RGB_HPP_
