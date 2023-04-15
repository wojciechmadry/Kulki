#include "red_box.hpp"

// Set position of object
template <typename T>
void set_position(T &Object, const sf::Vector2<float> &position) noexcept {
  Object.setPosition(position);
}

// Set position of object to be outside screen
template <typename T>
void put_out_of_screen(T &Object, const sf::Vector2<float> &size) noexcept {
  set_position(Object, {-(1.5f * size.x), -(1.5f * size.y)});
}

RedBox::RedBox(ResourceHolder<sf::Drawable> &Resources,
               const bool Textured) noexcept
    : m_box(AnyType(Resources.get_as<sf::Drawable>(ResourceType::PICKED))),
      m_text(Textured) {
  hide();
}

void RedBox::set_position(const float x, const float y) noexcept {
  if (m_text)
    get_any<sf::Sprite>().setPosition(x, y);
  else
    get_any<sf::RectangleShape>().setPosition(x, y);
}

void RedBox::hide() noexcept {
  if (m_text) {
    auto &sprite = get_any<sf::Sprite>();
    sf::Vector2f spriteSize(
        static_cast<float>(sprite.getTexture()->getSize().x) *
            sprite.getScale().x,
        static_cast<float>(sprite.getTexture()->getSize().y) *
            sprite.getScale().y);
    put_out_of_screen(sprite, spriteSize);
  } else {
    auto &draw = get_any<sf::RectangleShape>();
    put_out_of_screen(draw, draw.getSize());
  }
}
