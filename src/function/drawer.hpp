//
// Created by Wojtek on 20.11.2020.
//

#ifndef KULKI_DRAWER_HPP
#define KULKI_DRAWER_HPP

#include "object/map.hpp"

class GLOBAL
{
    inline static sf::RectangleShape _map = sf::RectangleShape({630, 630}); //NOLINT
    inline static  sf::RectangleShape _wb = sf::RectangleShape({70, 70}); //NOLINT white box
    static sf::CircleShape ball_shape[7];
public:
    static void INIT()
    {
        _map.setFillColor(sf::Color(0x8989A9));
        _map.setPosition({1280u >> 2u, 15});
        for(byte i = 0 ; i < 7 ; ++i)
        {
            ball b(static_cast<COLOR>(i));
            ball_shape[i] = sf::CircleShape(25);
            ball_shape[i].setFillColor(b.color());
        }
        _wb.setFillColor(sf::Color(0x8989A9));
        _wb.setOutlineThickness(1.0f);
        _wb.setOutlineColor(sf::Color::White);
    }
    [[nodiscard]]static const sf::RectangleShape& map() noexcept
    {
        return _map;
    }
    [[nodiscard]] static const sf::CircleShape& get_ball(COLOR id, const sf::Vector2f& pos)
    {
        byte i = static_cast<byte>(id);
        ball_shape[i].setPosition(pos);
        return ball_shape[i];
    }
    [[nodiscard]] static const sf::RectangleShape& white_box(const sf::Vector2f& pos)
    {
        _wb.setPosition(pos);
        return _wb;
    }

};

sf::CircleShape GLOBAL::ball_shape[7]; //NOLINT

void draw_window(sf::RenderWindow &window, map &Map,
                 const std::unordered_map<std::string, std::unique_ptr<sf::Drawable>> &to_draw)
{
    window.clear(sf::Color(0x7174A0));
    window.draw(GLOBAL::map());

    // Next ball
    for ( byte i = 0 ; i < 3 ; ++i )
    {
        sf::Vector2f pos = {static_cast<float>(30 + 70 * i), 450};
        window.draw(GLOBAL::white_box(pos));
        window.draw(GLOBAL::get_ball(Map.get_next_three()[i].enum_color(), {pos.x + 10, pos.y + 10}));
    }

    // Map
    byte i_map = 0, j_map;
    for ( size_t i = 15 ; i < 645 ; i += 70 ) // for ( size_t i = 15 ; i < 15 + 630 ; i += 70 )
    {
        j_map = 0;
        for ( size_t j = 320 ; j < 950 ; j += 70 ) // for ( size_t j = 1280u >> 2u ; j < ( 1280u >> 2u ) + 630 ; j += 70 )
        {
            sf::Vector2f pos = {static_cast<float>(j), static_cast<float>(i)};
            window.draw(GLOBAL::white_box(pos));
            if ( !Map.at(i_map, j_map).is_empty() )
            {
                pos.x += 10.f;
                pos.y += 10.f;
                window.draw(GLOBAL::get_ball(Map.at(i_map, j_map).enum_color(), pos));
            }
            ++j_map;
        }
        ++i_map;
    }

    //Draw all object from map (object to draw)
    for ( const auto &Item : to_draw )
        if ( Item.second )
            window.draw(*Item.second);
    Map.updated();
}


// Simplify sf::Text
sf::Text make_text(const std::string &text, const sf::Vector2f &pos, const sf::Color color, const uint32_t size,
                   const sf::Font &font)
{
    sf::Text tx(text, font);
    tx.setFillColor(color);
    tx.setPosition(pos);
    tx.setCharacterSize(size);
    return tx;
}


void draw_started_object(std::unordered_map<std::string, std::unique_ptr<sf::Drawable>> &_drawer, const sf::Font &font)
{
    //Draw text "Punkty :" on screen
    _drawer["..score"] = std::make_unique<sf::Text>(
            make_text("Punkty :", {1280u >> 4u, 100}, sf::Color::Black, 30, font));
    //Draw text "Rekord :" on screen
    _drawer["..record"] = std::make_unique<sf::Text>(
            make_text("Rekord :", {1280u >> 4u, 250}, sf::Color::Yellow, 30, font));
    //Draw text "Nastepne:" on screen
    _drawer["..next_three"] = std::make_unique<sf::Text>(make_text("Nastepne :", {30, 415}, sf::Color::Blue, 20, font));
    //This is map object to draw actually record (Only what you need to change is text
    _drawer["record"] = std::make_unique<sf::Text>(make_text("0", {116, 290}, sf::Color::White, 25, font));
    //This is map object to draw score on actually game (Only what you need to change is text
    _drawer["score"] = std::make_unique<sf::Text>(make_text("0", {116, 140}, sf::Color::White, 25, font));
    //"Pseudo button", when you click it new game has started.
    _drawer["..newgame"] = std::make_unique<sf::Text>(
            make_text("Nowa gra", {(1280u >> 4u) + 10, 550}, sf::Color::White, 20, font));
    //RectangleShape is where mouse is detect click on new game
    sf::RectangleShape rc({90, 30});
    rc.setFillColor(sf::Color::Transparent);
    rc.setOutlineColor(sf::Color::White);
    rc.setOutlineThickness(2.0f);
    rc.setPosition({(1280u >> 4u) + 10, 549});
    _drawer["..newgamebox"] = std::make_unique<sf::RectangleShape>(std::move(rc));
    // There is empty box with outline to pick selected ball
    sf::RectangleShape rc1({70, 70});
    rc1.setFillColor(sf::Color::Transparent);
    rc1.setOutlineColor(sf::Color::Red);
    _drawer["picked"] = std::make_unique<sf::RectangleShape>(std::move(rc1));

}

#endif //KULKI_DRAWER_HPP
