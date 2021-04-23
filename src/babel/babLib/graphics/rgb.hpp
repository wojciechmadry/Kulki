#ifndef BABEL_GRAPHICS_RGB
#define BABEL_GRAPHICS_RGB

#include "../algorithm.hpp"

namespace babel::GRAPHICS{
    class rgb
    {
        using byte = uint8_t;
        std::array<byte, 3> _RGB; //NOLINT
    public:
        constexpr explicit rgb(const byte R = 0, const byte G = 0, const byte B = 0) noexcept: _RGB({R, G, B})
        { }

        constexpr rgb(const rgb &other) noexcept = default;

        [[nodiscard]]  constexpr std::array<byte, 3> &get_array() noexcept
        {
            return _RGB;
        }

        [[nodiscard]] constexpr const std::array<byte, 3> &get_array() const noexcept
        {
            return _RGB;
        }

        [[nodiscard]] constexpr byte &R() noexcept
        {
            return _RGB[0];
        }

        [[nodiscard]] constexpr byte &G() noexcept
        {
            return _RGB[1];
        }

        [[nodiscard]] constexpr byte &B() noexcept
        {
            return _RGB[2];
        }

        [[nodiscard]] constexpr byte R() const noexcept
        {
            return _RGB[0];
        }

        [[nodiscard]] constexpr byte G() const noexcept
        {
            return _RGB[1];
        }

        [[nodiscard]] constexpr byte B() const noexcept
        {
            return _RGB[2];
        }

        [[nodiscard]] constexpr byte &operator[](const byte index)
        {
            if ( index > 2 )
                throw std::out_of_range("Array out of range.");
            return _RGB[index];
        }

        [[nodiscard]] constexpr byte operator[](const byte index) const
        {
            if ( index > 2 )
                throw std::out_of_range("Array out of range.");
            return _RGB[index];
        }

        constexpr void set(const byte R, const byte G, const byte B) noexcept
        {
            _RGB[0] = R;
            _RGB[1] = G;
            _RGB[2] = B;
        }
    };

}

#endif