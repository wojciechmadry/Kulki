#include <algorithm>

#include "drawer.hpp"
#include "function/load/load.hpp"

void GLOBAL::INIT(ResourceHolder<sf::Drawable> &Resource,
                  const sf::Font &sfFont,
                  const std::pair<uint16_t, uint16_t> RECORDS) noexcept {
  const auto res = load_resolution();
  m_width = res.first;
  m_height = res.second;
  m_width = std::min(static_cast<std::size_t>(1920), m_width);
  m_height = std::min(m_height, static_cast<std::size_t>(1080));
  float a =
      (0.5f * static_cast<float>(m_width)) / 9.f; // side length of white box
  float radius = a / 2.5f;                        // radius of circle
  for (const auto i : babel::ITERATOR::range(0, 6)) {
    ball b(static_cast<COLOR>(i));
    auto ball_shape = std::make_unique<sf::CircleShape>(radius);
    ball_shape->setFillColor(b.color());
    auto ballID =
        static_cast<ResourceType>(static_cast<std::decay_t<decltype(i)>>(
                                      ResourceType::BALL_CIRCLE_START) +
                                  i);
    Resource.insert(ballID, std::move(ball_shape), false);
  }

  m_wb_size = a;
  Resource.insert(ResourceType::WHITE_BOX,
                  make_rectangle({a, a}, {0, 0}, sf::Color(0x8989A9), 1.0f,
                                 sf::Color::White),
                  false);

  Resource.insert(ResourceType::MAP_BEFORE_GRID,
                  make_rectangle({a * 9.f, a * 9.f},
                                 {0.3f * static_cast<float>(m_width),
                                  0.02f * static_cast<float>(m_height)},
                                 sf::Color(0x8989A9)),
                  false);

  std::string texture_path;
  if (babel::FILE_SYS::folder_exist("ball_texture"))
    texture_path = "ball_texture/";
  else
    texture_path = "../ball_texture/";

  static const std::array<std::string, 6> ball_name = {
      "aquamarine.png", "orange.png", "yellow.png",
      "light_blue.png", "red.png",    "purple.png"};
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

    float scale_x =
        static_cast<float>(m_width) / static_cast<float>(text_size.x);
    float scale_y =
        static_cast<float>(m_height) / static_cast<float>(text_size.y);

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
                    make_rectangle({m_wb_size, m_wb_size}, {0, 0},
                                   sf::Color::Transparent, 0.07f * m_wb_size,
                                   sf::Color::Red));
  }

  draw_started_object(Resource, sfFont, RECORDS.first, RECORDS.second);
}

size_t GLOBAL::get_width() noexcept { return m_width; }

// Resolution of screen
size_t GLOBAL::get_height() noexcept { return m_height; }

float GLOBAL::get_white_box_size() noexcept { return m_wb_size; }

bool GLOBAL::BALL_TEXTURE() noexcept { return m_BALL_TEXTURE; }

bool GLOBAL::BACKGROUND_TEXTURE() noexcept { return m_BG_TEXTURE; }

bool GLOBAL::RED_BOX_TEXTURE() noexcept { return m_RED_BOX_TEXTURE; }
