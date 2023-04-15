#include "drawer.hpp"

sf::Text make_text(const std::string &text, const sf::Vector2f &pos,
                   const sf::Color color, const uint32_t size,
                   const sf::Font &font) {
  sf::Text tx(text, font);
  tx.setFillColor(color);
  tx.setPosition(pos);
  tx.setCharacterSize(size);
  return tx;
}

sf::RectangleShape make_rectangle(const sf::Vector2f Size,
                                  const sf::Vector2f Position,
                                  const sf::Color Color,
                                  const float OutlineThick,
                                  const sf::Color OutlineColor) noexcept {
  sf::RectangleShape rc(Size);
  rc.setFillColor(Color);
  rc.setOutlineColor(OutlineColor);
  rc.setOutlineThickness(OutlineThick);
  rc.setPosition(Position);
  return rc;
}

std::pair<int8_t, int8_t> MapCorToGrid(const sf::Vector2<float> cor) noexcept {
  auto low_x = 0.3f * static_cast<float>(GLOBAL::get_width());
  auto low_y = 0.02f * static_cast<float>(GLOBAL::get_height());

  auto x = (cor.x - low_x) / GLOBAL::get_white_box_size();
  auto y = (cor.y - low_y) / GLOBAL::get_white_box_size();

  return {static_cast<int8_t>(y), static_cast<int8_t>(x)};
}
