#include "ball.hpp"

#include <array>

#include "function/random/random.hpp"

static constexpr const std::array<std::array<unsigned char, 4>, 7> a_color{
    {{50, 100, 83, 255},
     {254, 127, 0, 255},
     {255, 255, 0, 255},
     {173, 216, 230, 255},
     {165, 42, 42, 255},
     {128, 0, 128, 255},
     {0, 0, 0, 0}}};

[[nodiscard]] sf::Color ball::sf_color(const COLOR Color,
                                       const short alpha) noexcept {
  auto ColorNumber = static_cast<unsigned char>(Color);
  return {
      a_color[ColorNumber][0], a_color[ColorNumber][1], a_color[ColorNumber][2],
      (alpha == -1 ? a_color[ColorNumber][3] : static_cast<sf::Uint8>(alpha))};
}

ball::ball() { m_colorID = COLOR::empty; }

ball::~ball() = default;

ball::ball(const ball &other) = default;

ball::ball(const COLOR color) noexcept : m_colorID(color) {}

ball &ball::operator=(const ball &other) noexcept = default;

ball &ball::swap(ball &other) noexcept {
  COLOR oth = other.m_colorID;
  other.m_colorID = m_colorID;
  m_colorID = oth;
  return *this;
}

ball &ball::operator=(const COLOR color) noexcept {
  m_colorID = color;
  return *this;
}

bool ball::operator==(const ball &other) const noexcept {
  return m_colorID == other.m_colorID;
}

bool ball::operator==(const COLOR color) const noexcept {
  return m_colorID == color;
}

bool ball::operator!=(const ball &other) const noexcept {
  return m_colorID != other.m_colorID;
}

bool ball::operator!=(const COLOR color) const noexcept {
  return m_colorID != color;
}

COLOR ball::enum_color() const noexcept { return m_colorID; }

sf::Color ball::color() const noexcept { return sf_color(m_colorID); }

sf::Color ball::color(unsigned char Alpha) const noexcept {
  return sf_color(m_colorID, Alpha);
}

bool ball::is_empty() const noexcept { return m_colorID == COLOR::empty; }

bool ball::has_value() const noexcept { return m_colorID != COLOR::empty; }

void ball::clear() noexcept { m_colorID = COLOR::empty; }

void ball::set(const COLOR color) noexcept { m_colorID = color; }

void ball::random() noexcept {
  // Generate random NOT EMPTY, color
  m_colorID =
      static_cast<COLOR>(randomizer::get().generate<unsigned char>(0, 5));
}
