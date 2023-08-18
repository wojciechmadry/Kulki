//
// Created by Wojtek on 20.11.2020.
//

#ifndef KULKI_DRAWER_HPP
#define KULKI_DRAWER_HPP

#include "map.hpp"
#include "resource.hpp"

void generate_started_object(ResourceHolder<sf::Drawable> &Resource,
                             const sf::Font &font, uint16_t record,
                             uint16_t score, float width,
                             float height) noexcept;

sf::RectangleShape
make_rectangle(sf::Vector2f Size, sf::Vector2f Position, sf::Color Color,
               float OutlineThick = 0.0f,
               sf::Color OutlineColor = sf::Color::Transparent) noexcept;

class GLOBAL {
public:
  static void INIT(ResourceHolder<sf::Drawable> &Resource,
                   const sf::Font &sfFont,
                   std::pair<uint16_t, uint16_t> RECORDS, float width,
                   float height) noexcept;
  static void UPDATE_RESOLUTION(ResourceHolder<sf::Drawable> &Resource,
                                float width, float height);

  [[nodiscard]] static float get_white_box_size() noexcept;

  [[nodiscard]] static bool BALL_TEXTURE() noexcept;

  [[nodiscard]] static bool BACKGROUND_TEXTURE() noexcept;

  [[nodiscard]] static bool RED_BOX_TEXTURE() noexcept;

private:
  inline static bool m_BALL_TEXTURE =
      false; // Texture to ball is load? //NOLINT
  inline static bool m_BG_TEXTURE =
      false; // Texture background is load ? //NOLINT
  inline static bool m_RED_BOX_TEXTURE =
      false; // Red box texture is load ? //NOLINT

  inline static float a{0.0f};      // Side length of white box
  inline static float radius{0.0f}; // Radius of circle

  static void calculate_static_vars(float width, float height);
  static void create_ball(ResourceHolder<sf::Drawable> &Resource);
  static void create_white_box(ResourceHolder<sf::Drawable> &Resource);
  static void create_map_before_grid(ResourceHolder<sf::Drawable> &Resource,
                                     float width, float height);
  static void update_ball_texture(ResourceHolder<sf::Drawable> &Resource);
  static void update_redbox_texture(ResourceHolder<sf::Drawable> &Resource);
  static void update_background_texture(ResourceHolder<sf::Drawable> &Resource,
                                        float width, float height);
  static void update_started_objects(ResourceHolder<sf::Drawable> &Resource,
                                     float width, float height);
};

void draw_window(sf::RenderWindow &window, map &Map,
                 ResourceHolder<sf::Drawable> &Resource, float width,
                 float height);

// Simplify sf::Text
sf::Text make_text(const std::string &text, const sf::Vector2f &pos,
                   sf::Color color, uint32_t size, const sf::Font &font);

// Scales cor on screen to cor on grid
//  ex.: cor can be position on screen {320, 15}
//  and return value is cor {x, y} on grid
//  cor = {320, 15} or cor {325, 15} etc. will show the same position {x, y} on
//  grid Every square of grid is 70x70 pixel.
std::pair<int8_t, int8_t> MapCorToGrid(sf::Vector2<float> cor, float width,
                                       float height) noexcept;

#endif // KULKI_DRAWER_HPP
