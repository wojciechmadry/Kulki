#include <SFML/Graphics.hpp>

#include "function/drawer.hpp"
#include "function/load.hpp"


#include <iostream>
#include <unordered_map>

static constexpr double VERSION = 1.01;

#define FPS 0 // Show fps in console
#define MULTITHREAD 1 // 1 - 2 core, 0 - 1 core


#if MULTITHREAD == 1

#include "function/waiter.hpp"

void
game_thr(map &Map, const uint32_t fps, std::pair<char, char> &from, const std::pair<char, char> &to,
         std::atomic<int> &operation)
{
    uint32_t _fps = babel::MATH::min(1000 / fps, 244);
    while ( operation != -1 )
    {
        if ( operation > 0 )
        {
            if ( operation == 2 )
            {
                Map.set_update(true);
            } else if ( operation == 1 )
            {
                if ( Map.move(from, to) )
                {
                    from = {-1, -1};
                }
            } else if ( operation == 3 )
            {
                Map.reset();
            }
            operation = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(_fps));
    }
}

#endif
// END MULTITHREAD

int main()
{
    std::string title = "Kulki ";
    title = title + "v." + std::to_string(VERSION);
    while(title[title.size() - 1] == '0')
        title.pop_back();
    size_t width = 1920, height = 1080;
   //size_t width = 640, height = 480;
   //size_t width = 1280, height = 720;
   //size_t width = 1600, height = 1000;
   // size_t width = 4096, height = 3112;

    GLOBAL::INIT(width, height);

    map Game = load_map();
    uint16_t record = check_for_record();
    uint16_t old_score = std::numeric_limits<uint16_t>::max();
    std::unordered_map<std::string, std::unique_ptr<sf::Drawable>> to_draw; // map of drawing object


    sf::Font font = load_font("arial.ttf"); // default font

    draw_started_object(to_draw, font);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(GLOBAL::get_width(), GLOBAL::get_height()), title, sf::Style::Default,
                            settings);

    auto fps = babel::MATH::min(load_fps(), 240u);
    window.setFramerateLimit(fps);
    sf::Image icon;
    icon.loadFromFile("ball.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //Operation on map is doing on another thread

    std::pair<char, char> picked = {-1, -1};
    std::pair<char, char> new_pick = {-1, -1};

#if MULTITHREAD == 1
    std::atomic<int> operation(0);
    waiter<decltype(operation)> Waiter(operation, fps);
    std::thread th(game_thr, std::ref(Game), fps, std::ref(picked), std::ref(new_pick), std::ref(operation));
#endif

#if FPS == 1
    float fps_f;
    sf::Clock clock;
    sf::Time prev = clock.getElapsedTime();
    sf::Time curr;
#endif

    sf::Event event; //NOLINT
    while ( window.isOpen() )
    {
#if FPS == 1
        curr = clock.getElapsedTime();
        fps_f = 1.0f/(curr.asSeconds()-prev.asSeconds());
        std::cout << "FPS : " << fps_f << '\n';
#endif
        while ( window.pollEvent(event) )
        {
            if ( event.type == sf::Event::Closed )
            {
#if MULTITHREAD == 1
                operation = -1;
                th.join();
#endif
                save_map(Game);
                window.close();
            } else if ( event.type == sf::Event::Resized || event.type == sf::Event::GainedFocus )
            {
#if MULTITHREAD == 1
                Waiter.set_and_wait(2, 0);// Game need update here
#elif MULTITHREAD == 0
                Game.set_update(true);
#endif
            } else if ( event.type == sf::Event::MouseButtonPressed )
            {

                auto rect_ptr = dynamic_cast<sf::RectangleShape *>(to_draw["picked"].get()); // Pointer to red box (picked ball)
                if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
                {
                    auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if ( pos.x > 0.3f * width &&
                         pos.x < 0.3f * width + 9.f * GLOBAL::white_box_size().x &&
                         pos.y > 0.02f * height &&
                         pos.y < 0.02f * height + 9.f * GLOBAL::white_box_size().x ) // Position of grid of balls
                    {
                        new_pick = MapCorToGrid(pos);
                        rect_ptr->setOutlineThickness(0.0f);
                        if ( !Game.at(new_pick).is_empty() )
                        {
                            picked = new_pick; // Pick ball
                        } else if ( picked.first != -1 && !Game.at(picked).is_empty() )
                        {
#if MULTITHREAD == 1
                            Waiter.set_and_wait(1, 0);// MOVE BALL
#elif MULTITHREAD == 0
                            if ( Game.move(picked, new_pick) ) // Try to move ball from picked to new_pick
                            {
                                picked = {-1, -1}; // if it successful, then set no picked ball.
                            }
#endif
                        } else
                        {
                            picked = {-1, -1}; // Set no pick
                        }

                        if ( picked.first != -1 ) // -1 means no picked ball
                        {
                            // Set red outline on picked ball
                            auto side_length = static_cast<float>(GLOBAL::white_box_size().x);
                            rect_ptr->setOutlineThickness(0.07f * GLOBAL::white_box_size().x);
                            rect_ptr->setPosition(
                                    static_cast<float>(0.3f * GLOBAL::get_width() + side_length * static_cast<float>(picked.second)), // Scale picked ball to resolution
                                    static_cast<float>(0.02f * GLOBAL::get_height() + side_length * static_cast<float>(picked.first)));
#if MULTITHREAD == 1
                            Waiter.set_and_wait(2, 0); // Game need update here
#elif MULTITHREAD == 0
                            Game.set_update(true); // Game need update here
#endif
                        }
                    } else if ( dynamic_cast<sf::RectangleShape *>(to_draw["..newgamebox"].get())->getGlobalBounds().contains(
                            pos) )
                    {
                        picked = {-1, -1};
                        rect_ptr->setOutlineThickness(0.f);
#if MULTITHREAD == 1
                        Waiter.set_and_wait(3, 0);// reset game
#elif MULTITHREAD == 0
                        Game.reset();
#endif
                    }
                } else if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) ) // Right mouse click reset picked ball
                {
                    if ( picked.first != -1 )
                    {
                        picked = {-1, -1};
                        rect_ptr->setOutlineThickness(0.0f);
#if MULTITHREAD == 1
                        Waiter.set_and_wait(2, 0);
#elif MULTITHREAD == 0
                        Game.set_update(true);
#endif
                    }
                }

            }


        }
        if ( Game.get_score() != old_score ) // check if score need update
        {
            std::string _scr;
            sf::Text *ptr_text;
            old_score = Game.get_score();
            if ( old_score > record ) // If record were break, then save it
            {
                record = old_score;
                save_record(record);
            }
            // Refresh score and record points
            ptr_text = dynamic_cast<sf::Text *>(to_draw["score"].get());
            ptr_text->setString(std::to_string(old_score));

            ptr_text = dynamic_cast<sf::Text *>(to_draw["record"].get());
            ptr_text->setString(std::to_string(record));
#if MULTITHREAD == 1
            Waiter.set_and_wait(2, 0);// Game need update here
#elif MULTITHREAD == 0
            Game.set_update(true);
#endif
        }
        //If game need update draw it
        if ( Game.need_update() )
            draw_window(window, Game, to_draw);
        window.display();
#if FPS == 1
        prev = curr;
#endif
    }

    return 0;
}