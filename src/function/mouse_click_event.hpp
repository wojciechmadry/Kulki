//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_MOUSE_CLICK_EVENT_HPP
#define KULKI_MOUSE_CLICK_EVENT_HPP

#include "thread_wrapper.hpp"


namespace MOUSE{
    void left_click(Thread &thread, sf::RenderWindow &window, std::pair<char, char> &new_pick,
                    std::pair<char, char> &picked, RedBox &redbox, map &Game,
                    std::unordered_map<std::string, std::unique_ptr<sf::Drawable>> &to_draw) noexcept
    {

        auto[width, height] = window.getSize();
        auto pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if ( pos.x > 0.3f * width &&
             pos.x < 0.3f * width + 9.f * GLOBAL::white_box_size().x &&
             pos.y > 0.02f * height &&
             pos.y < 0.02f * height + 9.f * GLOBAL::white_box_size().x ) // Position of grid of balls
        {
            new_pick = MapCorToGrid(pos);
            redbox.hide();
            if ( !Game.at(new_pick).is_empty() )
            {
                picked = new_pick; // Pick ball
            } else if ( picked.first != -1 && !Game.at(picked).is_empty() )
            {
                thread.operation(OperationType::MOVE); // MOVE BALL
            } else
            {
                picked = {-1, -1}; // Set no pick
            }

            if ( picked.first != -1 ) // -1 means no picked ball
            {
                // Set red outline on picked ball
                auto side_length = static_cast<float>(GLOBAL::white_box_size().x);
                redbox.set_position(
                        static_cast<float>(0.3f * GLOBAL::get_width() + side_length *
                                                                        static_cast<float>(picked.second)), // Scale picked ball to resolution
                        static_cast<float>(0.02f * GLOBAL::get_height() +
                                           side_length * static_cast<float>(picked.first)));
                thread.operation(OperationType::UPDATE);// Game need update here

            }
        } else if ( dynamic_cast<sf::RectangleShape *>(to_draw["..newgamebox"].get())->getGlobalBounds().contains(
                pos) )
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
