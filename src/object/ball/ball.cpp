#include "ball.hpp"

#include <array>

static constexpr const std::array<std::array<unsigned char, 4>, 7> _color
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

[[nodiscard]] sf::Color ball::sf_color(const COLOR Color, const short alpha) noexcept
{
    auto ColorNumber = static_cast<unsigned char>(Color);
    return {
            _color[ColorNumber][0],
            _color[ColorNumber][1],
            _color[ColorNumber][2],
            ( alpha == -1 ? _color[ColorNumber][3] : static_cast<sf::Uint8>(alpha) )
    };
}

ball::ball()
{
    _colorID = COLOR::empty;
}

ball::~ball() = default;

ball::ball(const ball &other) = default;

ball::ball(const COLOR color) noexcept: _colorID(color)
{ }

ball &ball::operator=(const ball other) noexcept
{
    _colorID = other._colorID;
    return *this;
}

ball &ball::swap(ball &other) noexcept
{
    COLOR oth = other._colorID;
    other._colorID = _colorID;
    _colorID = oth;
    return *this;
}

ball &ball::operator=(const COLOR color) noexcept
{
    _colorID = color;
    return *this;
}


bool ball::operator==(const ball other) const noexcept
{
    return _colorID == other._colorID;
}

bool ball::operator==(const COLOR color) const noexcept
{
    return _colorID == color;
}


bool ball::operator!=(const ball other) const noexcept
{
    return _colorID != other._colorID;
}

bool ball::operator!=(const COLOR color) const noexcept
{
    return _colorID != color;
}

COLOR ball::enum_color() const noexcept
{
    return _colorID;
}

sf::Color ball::color() const noexcept
{
    return sf_color(_colorID);
}


sf::Color ball::color(unsigned char Alpha) const noexcept
{
    return sf_color(_colorID, Alpha);
}

bool ball::is_empty() const noexcept
{
    return _colorID == COLOR::empty;
}

bool ball::has_value() const noexcept
{
    return _colorID != COLOR::empty;
}


void ball::clear() noexcept
{
    _colorID = COLOR::empty;
}

void ball::set(const COLOR color) noexcept
{
    _colorID = color;
}

void ball::random() noexcept
{
    //Generate random NOT EMPTY, color
    _colorID = static_cast<COLOR>(m_random_generator.generate<unsigned char>(0, 5));
}