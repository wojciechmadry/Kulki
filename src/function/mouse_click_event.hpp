//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_MOUSE_CLICK_EVENT_HPP
#define KULKI_MOUSE_CLICK_EVENT_HPP

#include "thread_wrapper.hpp"


namespace MOUSE{
    void left_click(Thread &thread, sf::RenderWindow &window, std::pair<char, char> &new_pick,
                    std::pair<char, char> &picked, RedBox &redbox, map &Game,
                    ResourceHolder<sf::Drawable>& Resource) noexcept
    {
        auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if ( Resource.get_as<sf::RectangleShape>(ResourceType::MAP_BEFORE_GRID).getGlobalBounds().contains(pos) ) // If you click to map grid
        {
            new_pick = MapCorToGrid(pos);
            if ( !Game.at(new_pick).is_empty() )
            {
                picked = new_pick; // Pick ball
            } else if ( picked.first != -1 && !Game.at(picked).is_empty() )
            {
                thread.operation(OperationType::MOVE); // MOVE BALL
            }

            if ( picked.first != -1 ) // -1 means no picked ball
            {
                // Set red outline on picked ball
                auto side_length = static_cast<float>(GLOBAL::white_box_size().x);
                auto grid_pos = Resource.get_as<sf::RectangleShape>(ResourceType::MAP_BEFORE_GRID).getPosition();
                redbox.set_position(
                        static_cast<float>(grid_pos.x + side_length * static_cast<float>(picked.second)),
                        static_cast<float>(grid_pos.y + side_length * static_cast<float>(picked.first)));
                thread.operation(OperationType::UPDATE);// Game need update here
            } else
                redbox.hide();

        }

        else if (  Resource.get_as<sf::RectangleShape>(ResourceType::NEW_GAME_BOX).getGlobalBounds().contains(pos) )
        {
            picked = {-1, -1};
            redbox.hide();
            thread.operation(OperationType::RESET);// reset game
        }
    }

    void right_click(Thread &thread, std::pair<char, char> &picked, RedBox &redbox) noexcept
    {
        if ( picked.first != -1 )
        {
            picked = {-1, -1};
            redbox.hide();
            thread.operation(OperationType::UPDATE); // update game
        }
    }

}

#endif //KULKI_MOUSE_CLICK_EVENT_HPP
