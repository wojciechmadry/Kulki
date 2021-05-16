//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_RED_BOX_HPP
#define KULKI_RED_BOX_HPP

#include <SFML/Graphics.hpp>


class RedBox
{
    sf::Drawable* _draw = nullptr;
    bool _text = false;

//Set position of object to be outside screen
    template<typename T>
    void _put_out_of_screen(T Object, const sf::Vector2<float>& size) noexcept
    {
        Object->setPosition(sf::Vector2<float>{-(1.5f * size.x), -(1.5f * size.y)});
    }

public:
    RedBox() = delete;
    RedBox(sf::Drawable* Ptr, const bool Textured) noexcept
    : _draw(Ptr), _text(Textured)
    {
        hide();
    }
    void set_position(const float x, const float y) noexcept
    {
        if (_text)
           babel::ALGO::asType<sf::Sprite*>(_draw)->setPosition(x, y);
        else
            babel::ALGO::asType<sf::RectangleShape*>(_draw)->setPosition(x, y);
    }
    void hide() noexcept
    {

        if (_text)
        {
            auto sprite = babel::ALGO::asType<sf::Sprite*>(_draw);
            sf::Vector2f spriteSize(
                    static_cast<float>(sprite->getTexture()->getSize().x) * sprite->getScale().x,
                    static_cast<float>(sprite->getTexture()->getSize().y) * sprite->getScale().y);
            _put_out_of_screen(sprite, spriteSize);
        }
        else
        {
            auto draw = babel::ALGO::asType<sf::RectangleShape*>(_draw);
            _put_out_of_screen(draw, draw->getSize());
        }
    }
    ~RedBox() = default;
};
#endif //KULKI_RED_BOX_HPP
