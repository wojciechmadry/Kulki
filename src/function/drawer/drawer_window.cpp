#include "drawer.hpp"

void draw_window(sf::RenderWindow &window, map &Map,
                 ResourceHolder<sf::Drawable> &Resource, float width,
                 float height) {
  auto wb = static_cast<float>(
      Resource.get_as<sf::RectangleShape>(ResourceType::WHITE_BOX)
          .getSize()
          .x); // whitebox size is ALWAYS A SQUARE!!
  auto &WhiteBox = Resource.get_as<sf::RectangleShape>(ResourceType::WHITE_BOX);

  // Return textured ball
  auto get_textured_ball =
      [&Resource](COLOR id,
                  const sf::Vector2f pos) mutable -> const sf::Sprite & {
    auto i = static_cast<std::size_t>(id);
    auto SpriteID = static_cast<ResourceType>(
        static_cast<std::size_t>(ResourceType::BALL_SPRITE_START) + i);
    auto &Sprite = Resource.get_as<sf::Sprite>(SpriteID);
    Sprite.setPosition(pos);
    return Sprite;
  };

  // Draw background
  window.clear(sf::Color(0x7174A0));
  if (GLOBAL::BACKGROUND_TEXTURE())
    window.draw(Resource.get_as<sf::Sprite>(ResourceType::BACKGROUND_SPRITE));

  // Draw map before grid 9x9 (darker aquamarine)
  window.draw(
      Resource.get_as<sf::RectangleShape>(ResourceType::MAP_BEFORE_GRID));

  // Draw 3 Next ball
  babel::ITERATOR::enumerator NextThreeEum(Map.get_next_three());
  std::for_each(
      NextThreeEum.begin(), NextThreeEum.end(), [&](const auto &NextEnum) {
        sf::Vector2f pos = {
            static_cast<float>(static_cast<size_t>(width) >> 4u) +
                static_cast<float>(NextEnum.first()) * wb,
            0.671641f * static_cast<float>(height)};
        WhiteBox.setPosition(pos);
        // Draw whitebox around ball.
        window.draw(WhiteBox);
        auto ballID =
            static_cast<ResourceType>(static_cast<decltype(NextEnum.first())>(
                                          ResourceType::BALL_CIRCLE_START) +
                                      NextEnum.first());
        auto &Ball =
            Resource.get_as<sf::CircleShape>(ballID); // No textured ball
        auto radius = wb / 2.0f - Ball.getRadius();
        pos.x += radius;
        pos.y += radius;
        // Draw ball (can be textured or not)
        if (!GLOBAL::BALL_TEXTURE()) {
          Ball.setPosition(pos);
          window.draw(Ball);
        } else {
          window.draw(get_textured_ball(NextEnum.second().enum_color(), pos));
        }
      });
  // Map

  // Draw ball on grid 9x9
  babel::ITERATOR::range<uint8_t> Range(
      0, static_cast<uint8_t>(Map.get_grid().size()));
  for (auto x_map : Range) {
    for (auto y_map : Range) {
      float x = 0.3f * width + static_cast<float>(x_map) * wb;
      float y = 0.02f * height + static_cast<float>(y_map) * wb;
      sf::Vector2f pos = {x, y};
      WhiteBox.setPosition(pos);
      // Draw whitebox around ball.
      window.draw(WhiteBox);
      if (Map.at(y_map, x_map).has_value()) {
        auto ballID = static_cast<ResourceType>(
            static_cast<std::size_t>(ResourceType::BALL_CIRCLE_START) +
            static_cast<std::size_t>(Map.at(y_map, x_map).enum_color()));
        auto &Ball =
            Resource.get_as<sf::CircleShape>(ballID); // No textured ball

        auto radius = wb / 2.0f - Ball.getRadius();
        pos.x += radius;
        pos.y += radius;
        // Draw ball (can be textured or not)
        if (!GLOBAL::BALL_TEXTURE()) {
          Ball.setPosition(pos);
          window.draw(Ball);
        } else
          window.draw(
              get_textured_ball(Map.at(y_map, x_map).enum_color(), pos));
      }
    }
  }

  // Draw other items where AutoDraw = true
  const auto &Res = Resource.get_resources();
  std::for_each(Res.cbegin(), Res.cend(), [&window](const auto &Item) mutable {
    if (Item)
      window.draw(*Item);
  });
  Map.updated();
}

void generate_started_object(ResourceHolder<sf::Drawable> &Resource,
                             const sf::Font &font, const uint16_t record,
                             const uint16_t score, float width,
                             float height) noexcept {
  auto Font_Size = static_cast<uint32_t>((width * height) * 0.000035f);

  auto x_start =
      static_cast<float>(static_cast<size_t>(width) >>
                         4u); // Where some text start drawing in axis X

  // Draw text "Punkty :" on screen

  Resource.insert(ResourceType::SCORE_TEXT,
                  make_text("Punkty :", {x_start, 0.12f * height},
                            sf::Color::Black, Font_Size, font));

  // Draw text "Rekord :" on screen

  Resource.insert(ResourceType::RECORD_TEXT,
                  make_text("Rekord :", {x_start, 0.34f * height},
                            sf::Color::Yellow, Font_Size, font));

  // Draw text "Nastepne:" on screen

  Resource.insert(
      ResourceType::NEXT_THREE_TEXT,
      make_text("Nastepne :",
                {static_cast<float>(static_cast<size_t>(width) >> 4u),
                 0.57f * height},
                sf::Color::Blue,
                static_cast<uint32_t>(static_cast<float>(Font_Size) * 0.75f),
                font));

  // This is map object to draw actually record (Only what you need to change is
  // text

  Resource.insert(
      ResourceType::RECORD,
      make_text(std::to_string(record), {0.116f * width, 0.43f * height},
                sf::Color::White,
                static_cast<uint32_t>(0.80f * static_cast<float>(Font_Size)),
                font));

  // This is map object to draw score on actually game (Only what you need to
  // change is text

  Resource.insert(
      ResourceType::SCORE,
      make_text(std::to_string(score), {0.116f * width, 0.2f * height},
                sf::Color::White,
                static_cast<uint32_t>(0.80f * static_cast<float>(Font_Size)),
                font));

  //"Pseudo button", when you click it new game has started.
  sf::Vector2<float> new_game_pos = {x_start, 0.85f * height};

  Resource.insert(
      ResourceType::NEW_GAME_TEXT,
      make_text("Nowa gra", new_game_pos, sf::Color::White,
                static_cast<uint32_t>(0.72f * static_cast<float>(Font_Size)),
                font));

  // RectangleShape is where mouse is detect click on new game
  Resource.insert(ResourceType::NEW_GAME_BOX,
                  make_rectangle({static_cast<float>(Font_Size) * 4.f,
                                  static_cast<float>(Font_Size)},
                                 new_game_pos, sf::Color::Transparent, 2.0f,
                                 sf::Color::White));
}
