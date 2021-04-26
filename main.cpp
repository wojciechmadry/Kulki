#include <SFML/Graphics.hpp>

#include "function/load.hpp"
#include "object/red_box.hpp"
#include "function/mouse_click_event.hpp"

#include <iostream>
#include <unordered_map>

static constexpr double VERSION = 1.02;

#define FPS 0 // Show fps in console


int main()
{
    std::string title = "Kulki ";
    title = title + "v." + std::to_string(VERSION);
    while ( title[title.size() - 1] == '0' )
        title.pop_back();
    auto [width, height] = load_resolution();

    GLOBAL::INIT(width, height);

    map Game = load_map();
    uint16_t record = check_for_record();
    uint16_t old_score = std::numeric_limits<uint16_t>::max();
    std::unordered_map<std::string, std::unique_ptr<sf::Drawable>> to_draw; // map of drawing object


    sf::Font font = load_font("arial.ttf"); // default font

    draw_started_object(to_draw, font);

    RedBox redbox(to_draw["picked"].get(), GLOBAL::RED_BOX_TEXTURE()); // picked redbox (can be textured or not)

    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

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

    Thread thread(Game, fps, picked, new_pick);
    std::set<OperationType> Operation; //Operations that must be performed before drawing

#if FPS == 1
    float fps_f;
    sf::Clock clock;
    sf::Time prev = clock.getElapsedTime();
    sf::Time curr;
#endif

    sf::Event event; //NOLINT
    // GAME LOOP
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
                thread.close_thread();
                save_map(Game);
                window.close();
            } else if ( event.type == sf::Event::Resized || event.type == sf::Event::GainedFocus )
            {
                Operation.insert(OperationType::UPDATE);// Game need update here
            } else if ( event.type == sf::Event::MouseButtonPressed )
            {
                if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
                {
                    MOUSE::left_click(Operation,window, new_pick, picked, redbox, Game, to_draw);
                }
                else if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) ) // Right mouse click reset picked ball
                {
                    MOUSE::right_click(Operation,picked, redbox);
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

            Operation.insert(OperationType::UPDATE);// Game need update here
        }
        for(auto op : Operation)
            thread.operation(op);
        Operation.clear();
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