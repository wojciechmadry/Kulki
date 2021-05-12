//
// Created by Wojtek on 20.11.2020.
//

#ifndef KULKI_DRAWER_HPP
#define KULKI_DRAWER_HPP

#include "object/map.hpp"

class GLOBAL
{
    static std::unique_ptr<sf::RectangleShape> _map;//Map before grid
    static std::unique_ptr<sf::RectangleShape> _wb; // Whitebox

    static std::array<std::unique_ptr<sf::CircleShape>, 6> ball_shape; // Ball colors (no texture)
    static std::array<std::unique_ptr<sf::Sprite>, 6> sprites; // Scalled ball textures, ready to draw
    static std::array<std::unique_ptr<sf::Texture>, 6> textures; // Ball textures

    inline static bool _BALL_TEXTURE = false; // Texture to ball is load? //NOLINT
    inline static bool _BG_TEXTURE = false; // Texture background is load ? //NOLINT
    inline static bool _RED_BOX_TEXTURE = false; // Red box texture is load ? //NOLINT

    static std::unique_ptr<sf::Sprite> _bg_sprite; //Background sprite
    static std::unique_ptr<sf::Texture> _bg_texture; // Background texture

    static std::unique_ptr<sf::Sprite> _redbox_sprite; //Red box sprite
    static std::unique_ptr<sf::Texture> _redbox_texture; // Red box texture

    inline static std::size_t _width = 0; // Resolution of screen x
    inline static std::size_t _height = 0; // Resolution of screen y
public:

    static void INIT(const size_t Width, const size_t Height) noexcept
    {
        _width = Width;
        _height = Height;
        float a = ( 0.5f * static_cast<float>(_width) ) / 9.f; // side length of white box
        float radius = a / 2.5f; // radius of circle

        for ( byte i = 0 ; i < 6 ; ++i )
        {
            ball b(static_cast<COLOR>(i));
            ball_shape[i] = std::make_unique<sf::CircleShape>(radius);
            ball_shape[i]->setFillColor(b.color());
        }

        _wb = std::make_unique<sf::RectangleShape>(sf::Vector2<float> {a, a});
        _wb->setFillColor(sf::Color(0x8989A9));
        _wb->setOutlineThickness(1.0f);
        _wb->setOutlineColor(sf::Color::White);

        _map = std::make_unique<sf::RectangleShape>(sf::Vector2<float> {a * 9.f, a * 9.f});
        _map->setFillColor(sf::Color(0x8989A9));
        _map->setPosition({0.3f * static_cast<float>(_width), 0.02f * static_cast<float>(_height)});

        std::string texture_path;
        if (babel::FILE_SYS::folder_exist( "ball_texture"))
            texture_path = "ball_texture/";
        else
            texture_path = "../ball_texture/";

        static const std::array<std::string, 6> ball_name =
                {
                        "aquamarine.png",
                        "orange.png",
                        "yellow.png",
                        "light_blue.png",
                        "red.png",
                        "purple.png"
                };
        bool texture_is_loaded = true;
        for ( size_t i = 0 ; i < ball_name.size() ; ++i )
        {
            sprites[i] = std::make_unique<sf::Sprite>();
            textures[i] = std::make_unique<sf::Texture>();

            bool FileGood = textures[i]->loadFromFile(texture_path + ball_name[i]);
            texture_is_loaded &= FileGood;
            if ( !FileGood )
                break;
            textures[i]->setSmooth(true);
            auto size_texture = ( radius / static_cast<float>(textures[i]->getSize().x) ) * 2.f;
            sprites[i]->setTexture(*textures[i]);
            sprites[i]->setScale({size_texture, size_texture});

        }

        _BALL_TEXTURE = texture_is_loaded;

        _bg_texture = std::make_unique<sf::Texture>();

        _BG_TEXTURE = _bg_texture->loadFromFile(texture_path + "background.png");
        if ( _BG_TEXTURE )
        {
            _bg_sprite = std::make_unique<sf::Sprite>();

            _bg_texture->setSmooth(true);
            _bg_sprite->setTexture(*_bg_texture);
            auto text_size = _bg_texture->getSize();

            float scale_x = static_cast<float>(_width) / static_cast<float>(text_size.x);
            float scale_y = static_cast<float>(_height) / static_cast<float>(text_size.y);

            _bg_sprite->setScale({scale_x, scale_y});
        }

        _redbox_texture = std::make_unique<sf::Texture>();

        _RED_BOX_TEXTURE = _redbox_texture->loadFromFile(texture_path + "redbox.png");
        if ( _RED_BOX_TEXTURE )
        {
            _redbox_sprite = std::make_unique<sf::Sprite>();

            _redbox_texture->setSmooth(true);
            _redbox_sprite->setTexture(*_redbox_texture);
            auto text_size = _redbox_texture->getSize();

            float scale_x = static_cast<float>(_wb->getSize().x) / static_cast<float>(text_size.x);

            _redbox_sprite->setScale({scale_x, scale_x});
        }
    }

    [[nodiscard]] static size_t get_width() noexcept
    {
        return _width;
    }

    [[nodiscard]] static size_t get_height() noexcept
    {
        return _height;
    }

    [[nodiscard]]static const sf::RectangleShape &map() noexcept
    {
        return *_map;
    }

    [[nodiscard]] static const sf::CircleShape &get_ball(COLOR id, const sf::Vector2f &pos) noexcept
    {
        byte i = static_cast<byte>(id);
        ball_shape[i]->setPosition(pos);
        return *ball_shape[i];
    }

    [[nodiscard]] static auto ball_radius() noexcept
    {
        return ball_shape[0]->getRadius();
    }

    [[nodiscard]] static const sf::Sprite &get_ball_textured(COLOR id, const sf::Vector2f &pos) noexcept
    {
        byte i = static_cast<byte>(id);
        sprites[i]->setPosition(pos);
        return *sprites[i];
    }

    [[nodiscard]] static const sf::RectangleShape &white_box(const sf::Vector2f &pos) noexcept
    {
        _wb->setPosition(pos);
        return *_wb;
    }


    [[nodiscard]] static auto white_box_size() noexcept
    {
        return _wb->getSize();
    }

    [[nodiscard]] static bool BALL_TEXTURE() noexcept
    {
        return _BALL_TEXTURE;
    }

    [[nodiscard]] static bool BACKGROUND_TEXTURE() noexcept
    {
        return _BG_TEXTURE;
    }

    [[nodiscard]] static bool RED_BOX_TEXTURE() noexcept
    {
        return _RED_BOX_TEXTURE;
    }

    [[nodiscard]] static const sf::Sprite &background() noexcept
    {
        return *_bg_sprite;
    }

    [[nodiscard]] static std::unique_ptr<sf::Sprite> &&RedBox() noexcept
    {
        return std::move(_redbox_sprite);
    }


};

std::array<std::unique_ptr<sf::CircleShape>, 6>  GLOBAL::ball_shape; //NOLINT
std::array<std::unique_ptr<sf::Sprite>, 6>  GLOBAL::sprites;
std::array<std::unique_ptr<sf::Texture>, 6> GLOBAL::textures;
std::unique_ptr<sf::Sprite> GLOBAL::_bg_sprite;//Background sprite
std::unique_ptr<sf::Texture> GLOBAL::_bg_texture; // Background texture
std::unique_ptr<sf::RectangleShape> GLOBAL::_map;//Map before grid
std::unique_ptr<sf::RectangleShape> GLOBAL::_wb; // Whitebox
std::unique_ptr<sf::Sprite> GLOBAL::_redbox_sprite; //Red box sprite
std::unique_ptr<sf::Texture> GLOBAL::_redbox_texture; // Red box texture

void draw_window(sf::RenderWindow &window, map &Map,
                 const std::unordered_map<std::string, std::unique_ptr<sf::Drawable>> &to_draw)
{
    auto width = static_cast<float>(GLOBAL::get_width()); // RESOLUTION OF SCREEN
    auto height = static_cast<float>(GLOBAL::get_height());
    auto wb = static_cast<float>(GLOBAL::white_box_size().x); // whitebox size is ALWAYS A SQUARE!!

    window.clear(sf::Color(0x7174A0));
    if ( GLOBAL::BACKGROUND_TEXTURE() )
        window.draw(GLOBAL::background());


    window.draw(GLOBAL::map());
    // Next ball
    for ( byte i = 0 ; i < 3 ; ++i )
    {
        sf::Vector2f pos = {static_cast<float>(static_cast<size_t>(GLOBAL::get_width()) >> 4u) +
                            static_cast<float>(i) * GLOBAL::white_box_size().x, 0.671641f * static_cast<float>(GLOBAL::get_height())};
        window.draw(GLOBAL::white_box(pos));
        auto radius = wb / 2.0f - GLOBAL::ball_radius();
        pos.x += radius;
        pos.y += radius;
        if ( !GLOBAL::BALL_TEXTURE() )
            window.draw(GLOBAL::get_ball(Map.get_next_three()[i].enum_color(), pos));
        else
            window.draw(GLOBAL::get_ball_textured(Map.get_next_three()[i].enum_color(), pos));
    }

    // Map

    byte x_map = 0, y_map;


    for ( ; x_map < 9 ; ++x_map )
    {
        for ( y_map = 0 ; y_map < 9 ; ++y_map )
        {
            float x = 0.3f * width + static_cast<float>(x_map) * wb;
            float y = 0.02f * height + static_cast<float>(y_map) * wb;
            sf::Vector2f pos = {x, y};
            window.draw(GLOBAL::white_box(pos));
            if ( !Map.at(y_map, x_map).is_empty() )
            {
                auto radius = wb / 2.0f - GLOBAL::ball_radius();
                pos.x += radius;
                pos.y += radius;
                if ( !GLOBAL::BALL_TEXTURE() )
                    window.draw(GLOBAL::get_ball(Map.at(y_map, x_map).enum_color(), pos));
                else
                    window.draw(GLOBAL::get_ball_textured(Map.at(y_map, x_map).enum_color(), pos));

            }
        }
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


void draw_started_object(std::unordered_map<std::string, std::unique_ptr<sf::Drawable>> &_drawer, const sf::Font &font, const uint16_t record, const uint16_t score) noexcept
{
    auto width = static_cast<float>(GLOBAL::get_width());
    auto height = static_cast<float>(GLOBAL::get_height());
    auto Font_Size = static_cast<uint32_t>(( width * height ) * 0.000035f);

    auto x_start = static_cast<float>(static_cast<size_t>(width) >> 4u); // Where some text start drawing in axis X
    //Draw text "Punkty :" on screen
    _drawer["..score"] = std::make_unique<sf::Text>(
            make_text("Punkty :", {x_start, 0.12f * height}, sf::Color::Black, Font_Size, font));
    //Draw text "Rekord :" on screen
    _drawer["..record"] = std::make_unique<sf::Text>(
            make_text("Rekord :", {x_start, 0.34f * height}, sf::Color::Yellow, Font_Size, font));
    //Draw text "Nastepne:" on screen
    _drawer["..next_three"] = std::make_unique<sf::Text>(
            make_text("Nastepne :", {static_cast<float>(static_cast<size_t>(width) >> 4u), 0.57f * height},
                      sf::Color::Blue, static_cast<uint32_t>(static_cast<float>(Font_Size) * 0.75f), font));
    //This is map object to draw actually record (Only what you need to change is text
    _drawer["record"] = std::make_unique<sf::Text>(
            make_text(std::to_string(record), {0.116f * width, 0.43f * height}, sf::Color::White, static_cast<uint32_t>(0.80f * static_cast<float>(Font_Size)), font));
    //This is map object to draw score on actually game (Only what you need to change is text
    _drawer["score"] = std::make_unique<sf::Text>(
            make_text(std::to_string(score), {0.116f * width, 0.2f * height}, sf::Color::White, static_cast<uint32_t>(0.80f * static_cast<float>(Font_Size)), font));
    //"Pseudo button", when you click it new game has started.
    sf::Vector2<float> new_game_pos = {x_start, 0.85f * height};
    _drawer["..newgame"] = std::make_unique<sf::Text>(
            make_text("Nowa gra", new_game_pos, sf::Color::White, static_cast<uint32_t>(0.72f * static_cast<float>(Font_Size)), font));

    //RectangleShape is where mouse is detect click on new game
    sf::RectangleShape rc({static_cast<float>(Font_Size) * 3.2f, static_cast<float>(Font_Size)});
    rc.setFillColor(sf::Color::Transparent);
    rc.setOutlineColor(sf::Color::White);
    rc.setOutlineThickness(2.0f);

    rc.setPosition(new_game_pos);
    _drawer["..newgamebox"] = std::make_unique<sf::RectangleShape>(std::move(rc));
    // There is empty box with red outline to pick selected ball
    if ( !GLOBAL::RED_BOX_TEXTURE() )
    {
        sf::RectangleShape rc1(GLOBAL::white_box_size());
        rc1.setFillColor(sf::Color::Transparent);
        rc1.setOutlineColor(sf::Color::Red);
        rc1.setOutlineThickness(0.07f * GLOBAL::white_box_size().x);
        _drawer["picked"] = std::make_unique<sf::RectangleShape>(std::move(rc1));

    } else
    {
        _drawer["picked"] = GLOBAL::RedBox();
    }

}

//Scales cor on screen to cor on grid
// ex.: cor can be position on screen {320, 15}
// and return value is cor {x, y} on grid
// cor = {320, 15} or cor {325, 15} etc. will show the same position {x, y} on grid
// Every square of grid is 70x70 pixel.
std::pair<int8_t, int8_t> MapCorToGrid(const sf::Vector2<float> cor) noexcept
{
    auto low_x = 0.3f * static_cast<float>(GLOBAL::get_width());
    auto low_y = 0.02f * static_cast<float>(GLOBAL::get_height());

    auto x = ( cor.x - low_x ) / GLOBAL::white_box_size().x;
    auto y = ( cor.y - low_y ) / GLOBAL::white_box_size().x;

    return {static_cast<int8_t>(y), static_cast<int8_t>(x)};
}

#endif //KULKI_DRAWER_HPP
