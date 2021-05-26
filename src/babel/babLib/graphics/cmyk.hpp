#ifndef BABEL_GRAPHICS_CMYK
#define BABEL_GRAPHICS_CMYK

#include "../algorithm/algorithm.hpp"

namespace babel::GRAPHICS{



    //------------------CMYK---------------
    class cmyk
    {
        using byte = uint8_t;
        std::array<byte, 4> _CMYK; //NOLINT

        [[nodiscard]] static constexpr byte _max(const byte Value) noexcept
        {
            return Value > 100 ? 100 : Value;
        }

        constexpr void _check_and_fix() noexcept
        {
            _CMYK[0] = _max(_CMYK[0]);
            _CMYK[1] = _max(_CMYK[1]);
            _CMYK[2] = _max(_CMYK[2]);
            _CMYK[3] = _max(_CMYK[3]);
        }

        constexpr void _set(const byte C, const byte M, const byte Y, const byte K) noexcept
        {
            _CMYK[0] = _max(C);
            _CMYK[1] = _max(M);
            _CMYK[2] = _max(Y);
            _CMYK[3] = _max(K);
        }

        constexpr void _set_at(const byte index, const byte Value) noexcept
        {
            _CMYK[index] = _max(Value);
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
            return _CMYK;
        }

        [[nodiscard]] constexpr byte C() const noexcept
        {
            return _CMYK[0];
        }

        [[nodiscard]] constexpr byte M() const noexcept
        {
            return _CMYK[1];
        }

        [[nodiscard]] constexpr byte Y() const noexcept
        {
            return _CMYK[2];
        }

        [[nodiscard]] constexpr byte K() const noexcept
        {
            return _CMYK[3];
        }


        [[nodiscard]] constexpr byte operator[](const byte index) const
        {
            if ( index > 3 )
                throw std::out_of_range("Array out of range.");
            return _CMYK[index];
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


}

#endif