//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_RED_BOX_HPP
#define KULKI_RED_BOX_HPP

#include "resource.hpp"
#include <type_traits>

class RedBox {
  std::reference_wrapper<sf::Drawable> m_box;
  bool m_text = false;

  template <typename T>
    requires(!std::is_pointer_v<T>)
  T &get_any() noexcept {
    return dynamic_cast<T &>(m_box.get());
  }

public:
  RedBox() = delete;

  RedBox(ResourceHolder<sf::Drawable> &Resources, bool Textured) noexcept;

  void set_position(float x, float y) noexcept;

  void hide() noexcept;

  ~RedBox() = default;
};

#endif // KULKI_RED_BOX_HPP
