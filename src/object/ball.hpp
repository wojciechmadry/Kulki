//
// Created by Wojtek on 19.11.2020.
//

#ifndef KULKI_BALL_HPP
#define KULKI_BALL_HPP



#include <cstdint>
#include <array>
#include <tuple>

#include "function/random_generator.hpp"

#include <SFML/Graphics.hpp>

using byte = unsigned char;

enum class COLOR : byte
{
    aquamarine = 0,
    orange = 1,
    yellow = 2,
    light_blue = 3,
    brown = 4,
    purple = 5,
    empty = 6
};


class ball
{
    [[nodiscard]] static sf::Color sf_color(const COLOR Color, int alpha = -1) noexcept
    {
        static constexpr const std::array<std::tuple<byte, byte, byte, byte>, 7> _color
                {
                        std::make_tuple<byte, byte, byte, byte>(50,100,83, 255),
                        std::make_tuple<byte, byte, byte, byte>(254, 127, 0, 255),
                        std::make_tuple<byte, byte, byte, byte>(255, 255, 0, 255),
                        std::make_tuple<byte, byte, byte, byte>(173, 216, 230, 255),
                        std::make_tuple<byte, byte, byte, byte>(165,42,42, 255),
                        std::make_tuple<byte, byte, byte, byte>(128, 0, 128, 255),
                        std::make_tuple<byte, byte, byte, byte>(0, 0, 0, 0)
                };
        return sf::Color(
                std::get<0>(_color[static_cast<byte>(Color)]),
                std::get<1>(_color[static_cast<byte>(Color)]),
                std::get<2>(_color[static_cast<byte>(Color)]),
                (alpha == -1 ? std::get<3>(_color[static_cast<byte>(Color)]) : alpha)
        );
    }

    COLOR _colorID = COLOR::empty;
public:
    ball() = default;

    ~ball() = default;

    ball(const ball &other) = default;

    explicit ball(const COLOR color) noexcept: _colorID(color)
    { }

    ball &operator=(const ball other) noexcept
    {
        _colorID = other._colorID;
        return *this;
    }
    ball& swap(ball& other) noexcept
    {
        COLOR oth = other._colorID;
        other._colorID = _colorID;
        _colorID = oth;
        return *this;
    }
    ball &operator=(const COLOR color) noexcept
    {
        _colorID = color;
        return *this;
    }

    [[nodiscard]] bool operator==(const ball other) const noexcept
    {
        return _colorID == other._colorID;
    }

    [[nodiscard]] bool operator==(const COLOR color) const noexcept
    {
        return _colorID == color;
    }

    [[nodiscard]] bool operator!=(const ball other) const noexcept
    {
        return _colorID != other._colorID;
    }

    [[nodiscard]] bool operator!=(const COLOR color) const noexcept
    {
        return _colorID != color;
    }
    [[nodiscard]] COLOR enum_color() const noexcept
    {
        return _colorID;
    }
    [[nodiscard]] sf::Color color() const noexcept
    {
        return sf_color(_colorID);
    }

    [[nodiscard]] sf::Color color(byte Alpha) const noexcept
    {
        return sf_color(_colorID, Alpha);
    }



    [[nodiscard]] bool is_empty() const noexcept
    {
        return _colorID == COLOR::empty;
    }
    void clear() noexcept
    {
        _colorID = COLOR::empty;
    }
    void set(const COLOR color) noexcept
    {
        _colorID = color;
    }

    void random() noexcept
    {
        //Generate random NOT EMPTY, color
        _colorID = static_cast<COLOR>(random_generator::generate<byte>(0, 5));
    }
};


#endif //KULKI_BALL_HPP
