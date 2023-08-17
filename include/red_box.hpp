//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_RED_BOX_HPP
#define KULKI_RED_BOX_HPP

#include "babel.hpp"
#include "resource.hpp"

class RedBox {
  babel::ANY::PolAny::any m_box;
  bool m_text = false;

  using AnyType = std::reference_wrapper<sf::Drawable>;

  template <typename T>
    requires(!babel::CONCEPTS::IS_ANY_POINTER<T>)
  T &get_any() noexcept {
    return *babel::ALGO::CAST::asType<T *>(&m_box.cast<AnyType>().get());
  }

public:
  RedBox() = delete;

  RedBox(ResourceHolder<sf::Drawable> &Resources, bool Textured) noexcept;

  void set_position(float x, float y) noexcept;

  void hide() noexcept;

  ~RedBox() = default;
};

#endif // KULKI_RED_BOX_HPP
