//
// Created by Wojtek on 20.11.2020.
//

#ifndef KULKI_DRAWER_HPP
#define KULKI_DRAWER_HPP

#include "object/map.hpp"
#include "object/resource.hpp"


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

    static void INIT(ResourceHolder<sf::Drawable> &Resource, const sf::Font &Font,
                     const std::pair<uint16_t, uint16_t> RECORDS) noexcept
    {
        auto res = load_resolution();
        _width = res.first;
        _height = res.second;
        float a = ( 0.5f * static_cast<float>(_width) ) / 9.f; // side length of white box
        float radius = a / 2.5f; // radius of circle
        for ( const auto i : babel::ITERATOR::range(0, 6) )
        {
            ball b(static_cast<COLOR>(i));
            auto ball_shape = std::make_unique<sf::CircleShape>(radius);
            ball_shape->setFillColor(b.color());
            auto ballID = static_cast<ResourceType>(static_cast<decltype(i)>(ResourceType::BALL_CIRCLE_START) + i);
            Resource.insert(ballID, std::move(ball_shape), false);
        }

        _wb_size = a;
        Resource.insert(ResourceType::WHITE_BOX,
                        make_rectangle({a, a}, {0, 0}, sf::Color(0x8989A9), 1.0f, sf::Color::White), false);

        Resource.insert(ResourceType::MAP_BEFORE_GRID,
                        make_rectangle({a * 9.f, a * 9.f},
                                       {0.3f * static_cast<float>(_width), 0.02f * static_cast<float>(_height)},
                                       sf::Color(0x8989A9)), false);


        std::string texture_path;
        if ( babel::FILE_SYS::folder_exist("ball_texture") )
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

        for ( auto i : babel::ITERATOR::range<std::size_t>(0, ball_name.size()))
        {
            auto sprite = std::make_unique<sf::Sprite>();
            auto texture = std::make_unique<sf::Texture>();

            bool FileGood = texture->loadFromFile(texture_path + ball_name[i]);
            texture_is_loaded &= FileGood;
            if ( !FileGood )
                break;
            texture->setSmooth(true);
            auto size_texture = ( radius / static_cast<float>(texture->getSize().x) ) * 2.f;
            auto TextID = static_cast<TextureType>(static_cast<std::size_t>(TextureType::BALL_TEXTURE_START) + i);
            Resource.insert(TextID, std::move(texture));

            sprite->setTexture(Resource.get_as(TextID));
            sprite->setScale({size_texture, size_texture});
            auto SpriteID = static_cast<ResourceType>(static_cast<std::size_t>(ResourceType::BALL_SPRITE_START) + i);
            Resource.insert(SpriteID, std::move(sprite), false);
        }

        _BALL_TEXTURE = texture_is_loaded;

        auto _bg_texture = std::make_unique<sf::Texture>();

        _BG_TEXTURE = _bg_texture->loadFromFile(texture_path + "background.png");
        if ( _BG_TEXTURE )
        {
            auto _bg_sprite = std::make_unique<sf::Sprite>();
            _bg_texture->setSmooth(true);
            auto text_size = _bg_texture->getSize();
            Resource.insert(TextureType::BACKGROUND, std::move(_bg_texture));
            _bg_sprite->setTexture(Resource.get_as(TextureType::BACKGROUND));

            float scale_x = static_cast<float>(_width) / static_cast<float>(text_size.x);
            float scale_y = static_cast<float>(_height) / static_cast<float>(text_size.y);

            _bg_sprite->setScale({scale_x, scale_y});

            Resource.insert(ResourceType::BACKGROUND_SPRITE, std::move(_bg_sprite), false);
        }

        auto _redbox_texture = std::make_unique<sf::Texture>();

        _RED_BOX_TEXTURE = _redbox_texture->loadFromFile(texture_path + "redbox.png");
        if ( _RED_BOX_TEXTURE )
        {
            auto _redbox_sprite = std::make_unique<sf::Sprite>();

            _redbox_texture->setSmooth(true);
            auto text_size = _redbox_texture->getSize();
            Resource.insert(TextureType::REDBOX, std::move(_redbox_texture));
            _redbox_sprite->setTexture(Resource.get_as(TextureType::REDBOX));

            float scale_x =
                    static_cast<float>(Resource.get_as<sf::RectangleShape>(ResourceType::WHITE_BOX).getSize().x) /
                    static_cast<float>(text_size.x);

            _redbox_sprite->setScale({scale_x, scale_x});

            Resource.insert(ResourceType::PICKED, std::move(_redbox_sprite));
        } else
        {
            // There is empty box with red outline to pick selected ball
            Resource.insert(ResourceType::PICKED, make_rectangle(
                    {_wb_size, _wb_size}, {0, 0}, sf::Color::Transparent, 0.07f * _wb_size, sf::Color::Red)
            );
        }

        draw_started_object(Resource, Font, RECORDS.first, RECORDS.second);
    }

    //Resolution of screen
    [[nodiscard]] static size_t get_width() noexcept
    {
        return _width;
    }

    //Resolution of screen
    [[nodiscard]] static size_t get_height() noexcept
    {
        return _height;
    }

    [[nodiscard]] static float get_white_box_size() noexcept
    {
        return _wb_size;
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


};


void draw_window(sf::RenderWindow &window, map &Map,
                 ResourceHolder<sf::Drawable> &Resource)
{
    auto width = static_cast<float>(GLOBAL::get_width()); // RESOLUTION OF SCREEN
    auto height = static_cast<float>(GLOBAL::get_height());
    auto wb = static_cast<float>(Resource.get_as<sf::RectangleShape>(
            ResourceType::WHITE_BOX).getSize().x); // whitebox size is ALWAYS A SQUARE!!
    auto &WhiteBox = Resource.get_as<sf::RectangleShape>(ResourceType::WHITE_BOX);

    // Return textured ball
    auto get_textured_ball = [&Resource](COLOR id, const sf::Vector2f pos) mutable -> const sf::Sprite & {
        auto i = static_cast<std::size_t>(id);
        auto SpriteID = static_cast<ResourceType>(static_cast<std::size_t>(ResourceType::BALL_SPRITE_START) + i);
        auto &Sprite = Resource.get_as<sf::Sprite>(SpriteID);
        Sprite.setPosition(pos);
        return Sprite;
    };

    // Draw background
    window.clear(sf::Color(0x7174A0));
    if ( GLOBAL::BACKGROUND_TEXTURE() )
        window.draw(Resource.get_as<sf::Sprite>(ResourceType::BACKGROUND_SPRITE));


    //Draw map before grid 9x9 (darker aquamarine)
    window.draw(Resource.get_as<sf::RectangleShape>(ResourceType::MAP_BEFORE_GRID));

    // Draw 3 Next ball
    babel::ITERATOR::enumerator NextThreeEum(Map.get_next_three());
    std::for_each(NextThreeEum.begin(), NextThreeEum.end(),
                  [&WhiteBox, &window, &Resource, wb, &get_textured_ball](const auto &NextEnum) mutable {
                      sf::Vector2f pos = {static_cast<float>(static_cast<size_t>(GLOBAL::get_width()) >> 4u) +
                                          static_cast<float>(NextEnum.first()) * wb,
                                          0.671641f * static_cast<float>(GLOBAL::get_height())};
                      WhiteBox.setPosition(pos);
                      // Draw whitebox around ball.
                      window.draw(WhiteBox);
                      auto ballID = static_cast<ResourceType>(
                              static_cast<decltype(NextEnum.first())>(ResourceType::BALL_CIRCLE_START) +
                              NextEnum.first());
                      auto &Ball = Resource.get_as<sf::CircleShape>(ballID); // No textured ball
                      auto radius = wb / 2.0f - Ball.getRadius();
                      pos.x += radius;
                      pos.y += radius;
                      //Draw ball (can be textured or not)
                      if ( !GLOBAL::BALL_TEXTURE() )
                      {
                          Ball.setPosition(pos);
                          window.draw(Ball);
                      } else
                      {
                          window.draw(get_textured_ball(NextEnum.second().enum_color(), pos));
                      }
                  });
    // Map

    //Draw ball on grid 9x9
    babel::ITERATOR::range<byte> Range(0, static_cast<byte>(Map.get_grid().size()));
    for ( auto x_map : Range )
    {
        for ( auto y_map : Range )
        {
            float x = 0.3f * width + static_cast<float>(x_map) * wb;
            float y = 0.02f * height + static_cast<float>(y_map) * wb;
            sf::Vector2f pos = {x, y};
            WhiteBox.setPosition(pos);
            // Draw whitebox around ball.
            window.draw(WhiteBox);
            if ( Map.at(y_map, x_map).has_value() )
            {
                auto ballID = static_cast<ResourceType>(static_cast<std::size_t>(ResourceType::BALL_CIRCLE_START) +
                                                        static_cast<std::size_t>(Map.at(y_map, x_map).enum_color()));
                auto &Ball = Resource.get_as<sf::CircleShape>(ballID); // No textured ball

                auto radius = wb / 2.0f - Ball.getRadius();
                pos.x += radius;
                pos.y += radius;
                //Draw ball (can be textured or not)
                if ( !GLOBAL::BALL_TEXTURE() )
                {
                    Ball.setPosition(pos);
                    window.draw(Ball);
                } else
                    window.draw(get_textured_ball(Map.at(y_map, x_map).enum_color(), pos));
            }
        }
    }

    //Draw other items where AutoDraw = true
    const auto &Res = Resource.get_resources();
    std::for_each(Res.cbegin(), Res.cend(), [&window](const auto &Item) mutable {
        if ( Item )
            window.draw(*Item);
    });
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

// Simplify sf::RectangleShape
sf::RectangleShape
make_rectangle(const sf::Vector2f Size, const sf::Vector2f Position, const sf::Color Color,
               const float OutlineThick,
               const sf::Color OutlineColor) noexcept
{
    sf::RectangleShape rc(Size);
    rc.setFillColor(Color);
    rc.setOutlineColor(OutlineColor);
    rc.setOutlineThickness(OutlineThick);
    rc.setPosition(Position);
    return rc;
}

void
draw_started_object(ResourceHolder<sf::Drawable> &Resource, const sf::Font &font, const uint16_t record,
                    const uint16_t score) noexcept
{
    auto width = static_cast<float>(GLOBAL::get_width());
    auto height = static_cast<float>(GLOBAL::get_height());
    auto Font_Size = static_cast<uint32_t>(( width * height ) * 0.000035f);

    auto x_start = static_cast<float>(static_cast<size_t>(width) >> 4u); // Where some text start drawing in axis X

    //Draw text "Punkty :" on screen

    Resource.insert(ResourceType::SCORE_TEXT,
                    make_text("Punkty :", {x_start, 0.12f * height}, sf::Color::Black, Font_Size, font));

    //Draw text "Rekord :" on screen

    Resource.insert(ResourceType::RECORD_TEXT,
                    make_text("Rekord :", {x_start, 0.34f * height}, sf::Color::Yellow, Font_Size, font));

    //Draw text "Nastepne:" on screen


    Resource.insert(ResourceType::NEXT_THREE_TEXT,
                    make_text("Nastepne :", {static_cast<float>(static_cast<size_t>(width) >> 4u), 0.57f * height},
                              sf::Color::Blue, static_cast<uint32_t>(static_cast<float>(Font_Size) * 0.75f), font));

    //This is map object to draw actually record (Only what you need to change is text

    Resource.insert(ResourceType::RECORD,
                    make_text(std::to_string(record), {0.116f * width, 0.43f * height}, sf::Color::White,
                              static_cast<uint32_t>(0.80f * static_cast<float>(Font_Size)), font));

    //This is map object to draw score on actually game (Only what you need to change is text

    Resource.insert(ResourceType::SCORE,
                    make_text(std::to_string(score), {0.116f * width, 0.2f * height}, sf::Color::White,
                              static_cast<uint32_t>(0.80f * static_cast<float>(Font_Size)), font));

    //"Pseudo button", when you click it new game has started.
    sf::Vector2<float> new_game_pos = {x_start, 0.85f * height};


    Resource.insert(ResourceType::NEW_GAME_TEXT, make_text("Nowa gra", new_game_pos, sf::Color::White,
                                                           static_cast<uint32_t>(0.72f *
                                                                                 static_cast<float>(Font_Size)),
                                                           font));


    //RectangleShape is where mouse is detect click on new game
    Resource.insert(ResourceType::NEW_GAME_BOX, make_rectangle(
            {static_cast<float>(Font_Size) * 3.2f, static_cast<float>(Font_Size)}, new_game_pos,
            sf::Color::Transparent,
            2.0f, sf::Color::White)
    );


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

    auto x = ( cor.x - low_x ) / GLOBAL::get_white_box_size();
    auto y = ( cor.y - low_y ) / GLOBAL::get_white_box_size();

    return {static_cast<int8_t>(y), static_cast<int8_t>(x)};
}

#endif //KULKI_DRAWER_HPP
