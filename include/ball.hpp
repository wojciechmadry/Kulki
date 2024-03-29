//
// Created by Wojtek on 19.11.2020.
//
#ifndef KULKI_BALL_HPP
#define KULKI_BALL_HPP

#include <SFML/Graphics.hpp>

enum class COLOR : unsigned char {
  aquamarine = 0,
  orange = 1,
  yellow = 2,
  light_blue = 3,
  red = 4,
  purple = 5,
  empty = 6
};

class ball {
  [[nodiscard]] static sf::Color sf_color(COLOR Color,
                                          short alpha = -1) noexcept;

  COLOR m_colorID;

public:
  ball();

  ~ball();

  ball(const ball &other);

  explicit ball(COLOR color) noexcept;

  ball &operator=(const ball &other) noexcept;

  ball &swap(ball &other) noexcept;

  ball &operator=(COLOR color) noexcept;

  [[nodiscard]] bool operator==(const ball &other) const noexcept;

  [[nodiscard]] bool operator==(COLOR color) const noexcept;

  [[nodiscard]] bool operator!=(const ball &other) const noexcept;

  [[nodiscard]] bool operator!=(COLOR color) const noexcept;

  [[nodiscard]] COLOR enum_color() const noexcept;

  [[nodiscard]] sf::Color color() const noexcept;

  [[nodiscard]] sf::Color color(unsigned char Alpha) const noexcept;

  [[nodiscard]] bool is_empty() const noexcept;

  [[nodiscard]] bool has_value() const noexcept;

  void clear() noexcept;

  void set(COLOR color) noexcept;

  void random() noexcept;
};

#endif // KULKI_BALL_HPP
