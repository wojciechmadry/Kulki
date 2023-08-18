#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <algorithm>

#include "drawer.hpp"
#include "load.hpp"
#include "resource.hpp"

static constexpr inline std::array<const char *, 6> ball_name = {
    "aquamarine.png", "orange.png", "yellow.png",
    "light_blue.png", "red.png",    "purple.png"};

void GLOBAL::INIT(ResourceHolder<sf::Drawable> &Resource,
                  const sf::Font &sfFont,
                  const std::pair<uint16_t, uint16_t> RECORDS, float width,
                  float height) noexcept {
  calculate_static_vars(width, height);
  create_ball(Resource);
  create_white_box(Resource);
  create_map_before_grid(Resource, width, height);

  std::string texture_path;
  if (babel::FILE_SYS::folder_exist("ball_texture"))
    texture_path = "ball_texture/";
  else
    texture_path = "../ball_texture/";

  bool texture_is_loaded = true;

  for (auto i :
       babel::ITERATOR::range<std::size_t, std::size_t>(0, ball_name.size())) {
    auto sprite = std::make_unique<sf::Sprite>();
    auto texture = std::make_unique<sf::Texture>();

    bool FileGood = texture->loadFromFile(texture_path + ball_name[i]);
    texture_is_loaded &= FileGood;
    if (!FileGood)
      break;
    texture->setSmooth(true);
    auto size_texture =
        (radius / static_cast<float>(texture->getSize().x)) * 2.f;
    auto TextID = static_cast<TextureType>(
        static_cast<std::size_t>(TextureType::BALL_TEXTURE_START) + i);
    Resource.insert(TextID, std::move(texture));

    sprite->setTexture(Resource.get_as(TextID));
    sprite->setScale({size_texture, size_texture});
    auto SpriteID = static_cast<ResourceType>(
        static_cast<std::size_t>(ResourceType::BALL_SPRITE_START) + i);
    Resource.insert(SpriteID, std::move(sprite), false);
  }

  m_BALL_TEXTURE = texture_is_loaded;

  auto _bg_texture = std::make_unique<sf::Texture>();

  m_BG_TEXTURE = _bg_texture->loadFromFile(texture_path + "background.png");
  if (m_BG_TEXTURE) {
    auto _bg_sprite = std::make_unique<sf::Sprite>();
    _bg_texture->setSmooth(true);
    auto text_size = _bg_texture->getSize();
    Resource.insert(TextureType::BACKGROUND, std::move(_bg_texture));
    _bg_sprite->setTexture(Resource.get_as(TextureType::BACKGROUND));

    float scale_x = width / static_cast<float>(text_size.x);
    float scale_y = height / static_cast<float>(text_size.y);

    _bg_sprite->setScale({scale_x, scale_y});

    Resource.insert(ResourceType::BACKGROUND_SPRITE, std::move(_bg_sprite),
                    false);
  }
  auto _redbox_texture = std::make_unique<sf::Texture>();

  m_RED_BOX_TEXTURE =
      _redbox_texture->loadFromFile(texture_path + "redbox.png");
  if (m_RED_BOX_TEXTURE) {
    auto _redbox_sprite = std::make_unique<sf::Sprite>();

    _redbox_texture->setSmooth(true);
    auto text_size = _redbox_texture->getSize();
    Resource.insert(TextureType::REDBOX, std::move(_redbox_texture));
    _redbox_sprite->setTexture(Resource.get_as(TextureType::REDBOX));

    float scale_x =
        static_cast<float>(
            Resource.get_as<sf::RectangleShape>(ResourceType::WHITE_BOX)
                .getSize()
                .x) /
        static_cast<float>(text_size.x);

    _redbox_sprite->setScale({scale_x, scale_x});

    Resource.insert(ResourceType::PICKED, std::move(_redbox_sprite));
  } else {
    // There is empty box with red outline to pick selected ball
    Resource.insert(ResourceType::PICKED,
                    make_rectangle({a, a}, {0, 0}, sf::Color::Transparent,
                                   0.07f * a, sf::Color::Red));
  }
  generate_started_object(Resource, sfFont, RECORDS.first, RECORDS.second,
                          width, height);
}

void GLOBAL::UPDATE_RESOLUTION(ResourceHolder<sf::Drawable> &Resource,
                               float width, float height) {
  calculate_static_vars(width, height);
  create_ball(Resource);
  create_white_box(Resource);
  create_map_before_grid(Resource, width, height);
  update_ball_texture(Resource);
  update_background_texture(Resource, width, height);
  update_redbox_texture(Resource);
  update_started_objects(Resource, width, height);
}

void GLOBAL::update_started_objects(ResourceHolder<sf::Drawable> &Resource,
                                    float width, float height) {
  auto Font_Size = static_cast<uint32_t>((width * height) * 0.000035f);
  auto x_start =
      static_cast<float>(static_cast<size_t>(width) >>
                         4u); // Where some text start drawing in axis X
  auto update_text = [&](ResourceType type, std::uint32_t font_size,
                         sf::Vector2f pos) {
    auto &text = Resource.get_as<sf::Text>(type);
    text.setPosition(pos);
    text.setCharacterSize(font_size);
  };
  update_text(ResourceType::SCORE_TEXT, Font_Size, {x_start, 0.12f * height});
  update_text(ResourceType::RECORD_TEXT, Font_Size, {x_start, 0.34f * height});
  update_text(
      ResourceType::NEXT_THREE_TEXT,
      static_cast<std::uint32_t>(static_cast<float>(Font_Size) * 0.75f),
      {static_cast<float>(static_cast<size_t>(width) >> 4u), 0.57f * height});
  update_text(ResourceType::RECORD,
              static_cast<uint32_t>(0.80f * static_cast<float>(Font_Size)),
              {0.116f * width, 0.43f * height});
  update_text(ResourceType::SCORE,
              static_cast<uint32_t>(0.80f * static_cast<float>(Font_Size)),
              {0.116f * width, 0.2f * height});
  sf::Vector2<float> new_game_pos = {x_start, 0.85f * height};
  update_text(ResourceType::NEW_GAME_TEXT,
              static_cast<uint32_t>(0.72f * static_cast<float>(Font_Size)),
              new_game_pos);
  auto &ngBoxSpriteRes =
      Resource.get_as<sf::RectangleShape>(ResourceType::NEW_GAME_BOX);
  ngBoxSpriteRes.setSize(
      {static_cast<float>(Font_Size) * 4.f, static_cast<float>(Font_Size)});
  ngBoxSpriteRes.setPosition(new_game_pos);
}

void GLOBAL::update_redbox_texture(ResourceHolder<sf::Drawable> &Resource) {
  if (GLOBAL::RED_BOX_TEXTURE()) {
    auto &textRes = Resource.get_as<sf::Texture>(TextureType::REDBOX);
    auto &spriteRes = Resource.get_as<sf::Sprite>(ResourceType::PICKED);

    textRes.setSmooth(true);
    auto text_size = textRes.getSize();

    float scale_x =
        static_cast<float>(
            Resource.get_as<sf::RectangleShape>(ResourceType::WHITE_BOX)
                .getSize()
                .x) /
        static_cast<float>(text_size.x);

    spriteRes.setScale({scale_x, scale_x});
  } else {
    auto &rectRes = Resource.get_as<sf::RectangleShape>(ResourceType::PICKED);
    rectRes.setSize({a, a});
    rectRes.setPosition({0, 0});
    rectRes.setFillColor(sf::Color::Transparent);
    rectRes.setOutlineThickness(0.07f * 1);
    rectRes.setOutlineColor(sf::Color::Red);
  }
}

void GLOBAL::update_background_texture(ResourceHolder<sf::Drawable> &Resource,
                                       float width, float height) {
  if (!GLOBAL::BACKGROUND_TEXTURE()) {
    return;
  }
  auto &bgRes = Resource.get_as<sf::Sprite>(ResourceType::BACKGROUND_SPRITE);
  auto bgTextureRes = Resource.get_as<sf::Texture>(TextureType::BACKGROUND);
  bgTextureRes.setSmooth(true);
  auto text_size = bgTextureRes.getSize();

  float scale_x = width / static_cast<float>(text_size.x);
  float scale_y = height / static_cast<float>(text_size.y);

  bgRes.setScale({scale_x, scale_y});
}

void GLOBAL::update_ball_texture(ResourceHolder<sf::Drawable> &Resource) {
  if (!GLOBAL::BALL_TEXTURE()) {
    return;
  }
  for (auto i :
       babel::ITERATOR::range<std::size_t, std::size_t>(0, ball_name.size())) {
    auto TextID = static_cast<TextureType>(
        static_cast<std::size_t>(TextureType::BALL_TEXTURE_START) + i);
    auto &textureRes = Resource.get_as<sf::Texture>(TextID);
    textureRes.setSmooth(true);
    auto size_texture =
        (radius / static_cast<float>(textureRes.getSize().x)) * 2.f;

    auto SpriteID = static_cast<ResourceType>(
        static_cast<std::size_t>(ResourceType::BALL_SPRITE_START) + i);
    auto &spriteRes = Resource.get_as<sf::Sprite>(SpriteID);
    spriteRes.setScale({size_texture, size_texture});
  }
}

void GLOBAL::calculate_static_vars(float width, float) {
  a = (0.5f * width) / 9.f;
  radius = a / 2.5f;
}

void GLOBAL::create_map_before_grid(ResourceHolder<sf::Drawable> &Resource,
                                    float width, float height) {
  Resource.create_if_not_exist<sf::RectangleShape>(
      ResourceType::MAP_BEFORE_GRID, false);
  auto &mapRes =
      Resource.get_as<sf::RectangleShape>(ResourceType::MAP_BEFORE_GRID);
  mapRes.setSize({a * 9.f, a * 9.f});
  mapRes.setPosition({0.3f * width, 0.02f * height});
  mapRes.setFillColor(sf::Color(0x8989A9));
}

void GLOBAL::create_white_box(ResourceHolder<sf::Drawable> &Resource) {
  Resource.create_if_not_exist<sf::RectangleShape>(ResourceType::WHITE_BOX,
                                                   false);
  auto &boxRes = Resource.get_as<sf::RectangleShape>(ResourceType::WHITE_BOX);
  boxRes.setSize({a, a});
  boxRes.setPosition({0, 0});
  boxRes.setFillColor(sf::Color(0x8989A9));
  boxRes.setOutlineThickness(1.f);
  boxRes.setOutlineColor(sf::Color::White);
}

void GLOBAL::create_ball(ResourceHolder<sf::Drawable> &Resource) {
  for (const auto i : babel::ITERATOR::range(0, 6)) {
    auto ballID =
        static_cast<ResourceType>(static_cast<std::decay_t<decltype(i)>>(
                                      ResourceType::BALL_CIRCLE_START) +
                                  i);
    Resource.create_if_not_exist<sf::CircleShape>(ballID, false);
    auto &ballRes = Resource.get_as<sf::CircleShape>(ballID);
    ballRes.setRadius(radius);
    const auto color = ball(static_cast<COLOR>(i)).color();
    ballRes.setFillColor(color);
  }
}
float GLOBAL::get_white_box_size() noexcept { return a; }

bool GLOBAL::BALL_TEXTURE() noexcept { return m_BALL_TEXTURE; }

bool GLOBAL::BACKGROUND_TEXTURE() noexcept { return m_BG_TEXTURE; }

bool GLOBAL::RED_BOX_TEXTURE() noexcept { return m_RED_BOX_TEXTURE; }
