//
// Created by Wojtek on 20.11.2020.
//

#ifndef KULKI_DRAWER_HPP
#define KULKI_DRAWER_HPP

#include "object/map/map.hpp"
#include "object/resource/resource.hpp"


void
draw_started_object(ResourceHolder<sf::Drawable> &Resource, const sf::Font &font, uint16_t record,
                    uint16_t score) noexcept;

sf::RectangleShape make_rectangle(sf::Vector2f Size, sf::Vector2f Position, sf::Color Color, float OutlineThick = 0.0f,
                                  sf::Color OutlineColor = sf::Color::Transparent) noexcept;

class GLOBAL
{

    inline static bool _BALL_TEXTURE = false; // Texture to ball is load? //NOLINT
    inline static bool _BG_TEXTURE = false; // Texture background is load ? //NOLINT
    inline static bool _RED_BOX_TEXTURE = false; // Red box texture is load ? //NOLINT

    inline static std::size_t _width {0}; // Resolution of screen x
    inline static std::size_t _height {0}; // Resolution of screen y
    inline static float _wb_size {0.0f}; // Side length of white box
public:

    static void INIT(ResourceHolder<sf::Drawable> &Resource, const sf::Font &sfFont,
                     std::pair<uint16_t, uint16_t> RECORDS) noexcept;

    //Resolution of screen
    [[nodiscard]] static size_t get_width() noexcept;

    //Resolution of screen
    [[nodiscard]] static size_t get_height() noexcept;

    [[nodiscard]] static float get_white_box_size() noexcept;

    [[nodiscard]] static bool BALL_TEXTURE() noexcept;

    [[nodiscard]] static bool BACKGROUND_TEXTURE() noexcept;

    [[nodiscard]] static bool RED_BOX_TEXTURE() noexcept;


};


void draw_window(sf::RenderWindow &window, map &Map,
                 ResourceHolder<sf::Drawable> &Resource);


// Simplify sf::Text
sf::Text make_text(const std::string &text, const sf::Vector2f &pos, const sf::Color color, const uint32_t size,
                   const sf::Font &font);

//Scales cor on screen to cor on grid
// ex.: cor can be position on screen {320, 15}
// and return value is cor {x, y} on grid
// cor = {320, 15} or cor {325, 15} etc. will show the same position {x, y} on grid
// Every square of grid is 70x70 pixel.
std::pair<int8_t, int8_t> MapCorToGrid(sf::Vector2<float> cor) noexcept;

#endif //KULKI_DRAWER_HPP
