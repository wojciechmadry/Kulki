#ifndef KULKI_RESOURCE_HPP
#define KULKI_RESOURCE_HPP

#include <SFML/Graphics.hpp>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <type_traits>

enum class ResourceType {
  PICKED = 0,        // Red box on screen
  RECORD = 1,        // Record score number (10,20 etc.)
  RECORD_TEXT,       // Record text "Record:"
  SCORE,             // Actual score number (10,20 etc.)
  SCORE_TEXT,        // Score text "Score:"
  NEW_GAME_BOX,      // Box "New game"
  NEW_GAME_TEXT,     // Text in box "New game"
  NEXT_THREE_TEXT,   // Text "Next three balls"
  MAP_BEFORE_GRID,   // Darker aquamarine before grid 9x9
  WHITE_BOX,         // Whit box around ball
  BACKGROUND_SPRITE, // Background sprite (aquamarine bg)
  BALL_SPRITE_START, // Scaled ball textures, ready to draw (6 sprites)
  BALL_SPRITE_END =
      BALL_SPRITE_START + 5, // END Scaled ball textures, ready to draw
  BALL_CIRCLE_START,         // Ball colors (no texture) (6 sf::CircleShape)
  BALL_CIRCLE_END = BALL_CIRCLE_START + 5, // END ball colors
  ENUM_SIZE
};

enum class TextureType {
  BACKGROUND = 0,                            // BACKGROUND TEXTURE
  REDBOX = 1,                                // REDBOX TEXTURE
  BALL_TEXTURE_START,                        // Start ball texture
  BALL_TEXTURE_END = BALL_TEXTURE_START + 5, // 6 textured ball in container
  ENUM_SIZE
};

template <typename Resource = sf::Drawable, typename Texture = sf::Texture>
  requires(!std::is_pointer_v<Resource> &&
           !std::is_pointer_v<Texture>)
class ResourceHolder {
  template <typename T>
  [[nodiscard]] constexpr std::size_t cast(const T type) const noexcept {
    return static_cast<std::size_t>(type);
  }

  class Object {
    friend class ResourceHolder<Resource>;

    bool m_autodraw; // Auto draw in loop every frame
    std::unique_ptr<Resource> m_res;

    [[nodiscard]] Resource *_get() noexcept { return m_res.get(); }

    [[nodiscard]] const Resource *_get() const noexcept { return m_res.get(); }

  public:
    Object() noexcept {
      m_res = nullptr;
      m_autodraw = false;
    }

    explicit Object(std::unique_ptr<Resource> &&res, bool autodraw) noexcept
        : m_autodraw(autodraw), m_res(std::move(res)) {}

    Object(Object &&Obj) noexcept {
      m_autodraw = Obj.m_autodraw;
      m_res = std::move(Obj.m_res);
    }

    Object(const Object &) = delete;

    ~Object() = default;

    Object &operator=(const Object &) = delete;

    Object &operator=(Object &&Obj) noexcept {
      m_autodraw = Obj.m_autodraw;
      m_res = std::move(Obj.m_res);
      return *this;
    }

    bool is_nullptr() const noexcept { return m_res == nullptr; }

    [[nodiscard]] explicit operator bool() const noexcept {
      return m_autodraw && m_res;
    }

    const Resource &operator*() const noexcept { return *m_res; }

    Resource &operator*() noexcept { return *m_res; }
  };

  std::vector<Object> m_resource{cast(ResourceType::ENUM_SIZE)};
  std::vector<std::unique_ptr<Texture>> m_textures{
      cast(TextureType::ENUM_SIZE)};

public:
  ResourceHolder() = default;

  ~ResourceHolder() = default;

  // Drawable object
  template <typename T>
    requires(!std::is_pointer_v<T> &&
             (std::is_convertible_v<T, Resource> ||
              std::is_base_of_v<Resource, T>))
  void insert(const ResourceType Key, T &&Value,
              bool AutoDraw = true) noexcept {
    m_resource[cast(Key)] =
        Object(std::make_unique<T>(std::forward<T>(Value)), AutoDraw);
  }

  template <typename T>
    requires(!std::is_pointer_v<T> &&
             (std::is_convertible_v<T, Resource> ||
              std::is_base_of_v<Resource, T>))
  void create_if_not_exist(const ResourceType Key,
                           bool AutoDraw = true) noexcept {
    const auto idx = cast(Key);
    if (m_resource[idx].is_nullptr()) {
      m_resource[idx] = Object(std::make_unique<T>(), AutoDraw);
    }
  }

  template <typename T>
    requires(std::is_base_of_v<Resource, T>)
  void insert(const ResourceType Key, std::unique_ptr<T> &&ValuePTR,
              bool AutoDraw = true) noexcept {
    m_resource[cast(Key)] = Object(std::move(ValuePTR), AutoDraw);
  }

  template <typename T>
    requires(std::is_base_of_v<Resource, T>)
  [[nodiscard]] T &get_as(const ResourceType Key) noexcept {
    return *dynamic_cast<T *>(m_resource[cast(Key)]._get());
  }

  template <typename T>
    requires(std::is_base_of_v<Resource, T>)
  [[nodiscard]] const T &get_as(const ResourceType Key) const noexcept {
    return *dynamic_cast<const T *>(m_resource[cast(Key)]._get());
  }

  [[nodiscard]] const decltype(m_resource) &get_resources() const noexcept {
    return m_resource;
  }

  // Textures

  [[nodiscard]] const decltype(m_textures) &get_textures() const noexcept {
    return m_textures;
  }

  template <typename T>
    requires(!std::is_pointer_v<T> &&
             (std::is_convertible_v<T, Texture> ||
              std::is_base_of_v<Texture, T>))
  void insert(const TextureType Key, T &&Value) noexcept {
    m_textures[cast(Key)] = std::make_unique<T>(std::forward<T>(Value));
  }

  template <typename T>
    requires(std::is_base_of_v<Texture, T>)
  void insert(const TextureType Key, std::unique_ptr<T> &&ValuePTR) noexcept {
    m_textures[cast(Key)] = std::move(ValuePTR);
  }

  template <typename T = Texture>
    requires(std::is_base_of_v<Texture, T>)
  [[nodiscard]] T &get_as(const TextureType Key) noexcept {
    return *dynamic_cast<T *>(m_textures[cast(Key)].get());
  }

  template <typename T = sf::Texture>
    requires(std::is_base_of_v<Texture, T>)
  [[nodiscard]] const T &get_as(const TextureType Key) const noexcept {
    return *dynamic_cast<const T *>(m_textures[cast(Key)].get());
  }
};

#endif
