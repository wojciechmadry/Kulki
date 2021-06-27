//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_RED_BOX_HPP
#define KULKI_RED_BOX_HPP

#include <SFML/Graphics.hpp>
#include "resource.hpp"

class RedBox
{
    babel::ANY::PolAny::any _box;
    bool _text = false;

    //Set position of object
    template<typename T>
    void _set_position(T& Object, const sf::Vector2<float>& position) noexcept
    {
        Object.setPosition(position);
    }

//Set position of object to be outside screen
    template<typename T>
    void _put_out_of_screen(T& Object, const sf::Vector2<float>& size) noexcept
    {
        _set_position(Object, {-(1.5f * size.x), -(1.5f * size.y)});
    }
    using AnyType = std::reference_wrapper<sf::Drawable>;

    template<typename T>
    requires(!babel::CONCEPTS::IS_ANY_POINTER<T>)
    T& get_any() noexcept
    {
          return *babel::ALGO::CAST::asType<T*>(&_box.cast<AnyType>().get());
    }

public:
    RedBox() = delete;
    RedBox(ResourceHolder<sf::Drawable>& Resources, const bool Textured) noexcept
    : _text(Textured)
    {
        _box = AnyType(Resources.get_as<sf::Drawable>(ResourceType::PICKED));
        hide();
    }
    void set_position(const float x, const float y) noexcept
    {
        if (_text)
            get_any<sf::Sprite>().setPosition(x,y);
        else
            get_any<sf::RectangleShape>().setPosition(x,y);
    }
    void hide() noexcept
    {

        if (_text)
        {
            auto& sprite = get_any<sf::Sprite>();
            sf::Vector2f spriteSize(
                    static_cast<float>(sprite.getTexture()->getSize().x) * sprite.getScale().x,
                    static_cast<float>(sprite.getTexture()->getSize().y) * sprite.getScale().y);
            _put_out_of_screen(sprite, spriteSize);
        }
        else
        {
            auto& draw = get_any<sf::RectangleShape>();
            _put_out_of_screen(draw, draw.getSize());
        }
    }
    ~RedBox() = default;
};
#endif //KULKI_RED_BOX_HPP
