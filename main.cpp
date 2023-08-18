#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>

#include "load.hpp"
#include "mouse_click_event.hpp"
#include "red_box.hpp"
#include "tester.hpp"

#include <iostream>

static constexpr const char *VERSION = "1.4";

#define FPS 0 // Show fps in console

int main() {

  // Play_Test_Games(-1, 14); // Test if game crash.
  ResourceHolder<sf::Drawable, sf::Texture> Resource;

  map Game = load_map();
  uint16_t record = check_for_record(), old_score = Game.get_score();

  sf::Font font;
  font = load_font("font/NeverMindHand/ttf/NeverMindHand-Regular.ttf");
  GLOBAL::INIT(Resource, font, {record, old_score}, 1280,
               720); // Load textures, init default
                     // settings, draw started object etc

  RedBox redbox(
      Resource,
      GLOBAL::RED_BOX_TEXTURE()); // picked redbox (can be textured or not)

  sf::RenderWindow window(sf::VideoMode(1280, 720), VERSION, sf::Style::Default,
                          sf::ContextSettings{0, 0, 8});
  auto fps = load_fps();
  window.setFramerateLimit(fps);
  sf::Image icon;
  bool iconLoaded = true;
  if (babel::FILE_SYS::folder_exist("ball_texture"))
    icon.loadFromFile("ball_texture/orange.png");
  else if ((babel::FILE_SYS::folder_exist("../ball_texture")))
    icon.loadFromFile("../ball_texture/orange.png");
  else
    iconLoaded = false;

  if (iconLoaded)
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  // Operation on map is doing on another thread

  std::pair<char, char> picked = {-1, -1}, new_pick = {-1, -1};

  std::mutex Mutex;

  Thread thread(Game, picked, new_pick, Mutex);
#if FPS == 1
  float fps_f;
  sf::Clock clock;
  sf::Time prev = clock.getElapsedTime();
  sf::Time curr;
#endif

  sf::Event event; // NOLINT
  // GAME LOOP
  while (window.isOpen()) {

#if FPS == 1
    curr = clock.getElapsedTime();
    fps_f = 1.0f / (curr.asSeconds() - prev.asSeconds());
    std::cout << "FPS : " << fps_f << '\n';
#endif
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        thread.close_thread();
        save_map(Game);
        window.close();
      } else if (event.type == sf::Event::Resized ||
                 event.type == sf::Event::GainedFocus) {
        GLOBAL::UPDATE_RESOLUTION(Resource,
                                  static_cast<float>(window.getSize().x),
                                  static_cast<float>(window.getSize().y));
        thread.operation(OperationType::UPDATE); // Game need update here
        sf::FloatRect visibleArea(0, 0, static_cast<float>(window.getSize().x),
                                  static_cast<float>(window.getSize().y));
        window.setView(sf::View(visibleArea));
        MOUSE::right_click(thread, picked, redbox);
      } else if (event.type == sf::Event::MouseButtonPressed) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
          MOUSE::left_click(thread, window, new_pick, picked, redbox, Game,
                            Resource);
        else if (sf::Mouse::isButtonPressed(
                     sf::Mouse::Right)) // Right mouse click reset picked ball
          MOUSE::right_click(thread, picked, redbox);
      }
    }

    if (Game.get_score() != old_score) // check if score need update
    {
      old_score = Game.get_score();
      auto _str = std::to_string(old_score);
      if (old_score > record) // If record were break, then save it
      {
        record = old_score;
        save_record(record);
        Resource.get_as<sf::Text>(ResourceType::RECORD).setString(_str);
      }
      // Refresh score and record points
      Resource.get_as<sf::Text>(ResourceType::SCORE).setString(_str);
      thread.operation(OperationType::UPDATE); // Game need update here
    }

    // Game.random_move();

    // If game need update draw it
    if (Game.need_update())
      draw_window(window, Game, Resource);

    window.display();

#if FPS == 1
    prev = curr;
#endif
  }

  return 0;
}
