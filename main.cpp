#include <SFML/Graphics.hpp>
#include <cmath>

#include "function/load/load.hpp"
#include "object/red_box/red_box.hpp"
#include "function/mouse/mouse_click_event.hpp"
#include "function/tester/tester.hpp"
#include "function/font/search_font.hpp"


#include <iostream>

static constexpr const char* VERSION = "1.3";

#define FPS 0 // Show fps in console

int main()
{

   //Play_Test_Games(-1, 14); // Test if game crush.
    ResourceHolder<sf::Drawable, sf::Texture> Resource;

    map Game = load_map();
    uint16_t record = check_for_record(), old_score = Game.get_score();

    sf::Font font;

    auto PathFont = search_font();

    if ( PathFont.has_value() )
        font = load_font(PathFont.value()); // default font
    else
    {
        std::cout << "Cant find any font\n";
        std::cin.get();
        std::cin.get();
        return 1;
    }

    GLOBAL::INIT(Resource, font, {record, old_score} ); // Load textures, init default settings, draw started object etc

    RedBox redbox(Resource, GLOBAL::RED_BOX_TEXTURE()); // picked redbox (can be textured or not)


    sf::RenderWindow window(
            sf::VideoMode(static_cast<uint32_t>(GLOBAL::get_width()), static_cast<uint32_t>(GLOBAL::get_height())),
            VERSION, sf::Style::Default,
            sf::ContextSettings {0, 0, 8});

    auto fps = load_fps();
    window.setFramerateLimit(fps);
    sf::Image icon;

    if ( babel::FILE_SYS::folder_exist("ball_texture") )
        icon.loadFromFile("ball_texture/orange.png");
    else if (( babel::FILE_SYS::folder_exist("../ball_texture") ))
        icon.loadFromFile("../ball_texture/orange.png");

    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //Operation on map is doing on another thread

    std::pair<char, char> picked = {-1, -1}, new_pick = {-1, -1};

    std::mutex Mutex;

    Thread thread(Game, picked, new_pick, Mutex);
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
                thread.operation(OperationType::UPDATE);// Game need update here
            } else if ( event.type == sf::Event::MouseButtonPressed )
            {
                if ( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
                    MOUSE::left_click(thread, window, new_pick, picked, redbox, Game,Resource);
                else if ( sf::Mouse::isButtonPressed(sf::Mouse::Right) ) // Right mouse click reset picked ball
                    MOUSE::right_click(thread, picked, redbox);
            }
        }

        if ( Game.get_score() != old_score ) // check if score need update
        {
            old_score = Game.get_score();
            auto _str = std::to_string(old_score);
            if ( old_score > record ) // If record were break, then save it
            {
                record = old_score;
                save_record(record);
                Resource.get_as<sf::Text>(ResourceType::RECORD).setString(_str);
            }
            // Refresh score and record points
            Resource.get_as<sf::Text>(ResourceType::SCORE).setString(_str);
            thread.operation(OperationType::UPDATE);// Game need update here
        }

       // Game.random_move();

        //If game need update draw it
        if ( Game.need_update() )
            draw_window(window, Game, Resource);

        window.display();

#if FPS == 1
        prev = curr;
#endif

    }

    return 0;
}