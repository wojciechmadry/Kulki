//
// Created by Wojtek on 19.11.2020.
//

#ifndef KULKI_BALL_HPP
#define KULKI_BALL_HPP


#include <cstdint>
#include <array>

#include "function/random_generator.hpp"

#include <SFML/Graphics.hpp>

using byte = u8;

enum class COLOR : byte
{
    aquamarine = 0,
    orange = 1,
    yellow = 2,
    light_blue = 3,
    red = 4,
    purple = 5,
    empty = 6
};

class ball
{
    static constexpr const std::array<std::array<byte, 4>, 7> _color
            {
                    {
                            {50, 100, 83, 255},
                            {254, 127, 0, 255},
                            {255, 255, 0, 255},
                            {173, 216, 230, 255},
                            {165, 42, 42, 255},
                            {128, 0, 128, 255},
                            {0, 0, 0, 0}
                    }
            };

    [[nodiscard]] static sf::Color sf_color(const COLOR Color, const int16_t alpha = -1) noexcept
    {
        auto ColorNumber = static_cast<byte>(Color);
        return sf::Color(
                _color[ColorNumber][0],
                _color[ColorNumber][1],
                _color[ColorNumber][2],
                ( alpha == -1 ? _color[ColorNumber][3] : static_cast<sf::Uint8>(alpha) )
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

    ball &swap(ball &other) noexcept
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

    [[nodiscard]] bool has_value() const noexcept
    {
        return _colorID != COLOR::empty;
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
