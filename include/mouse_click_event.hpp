//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_MOUSE_CLICK_EVENT_HPP
#define KULKI_MOUSE_CLICK_EVENT_HPP

#include "red_box.hpp"
#include "thread_wrapper.hpp"

namespace MOUSE {
void left_click(Thread &thread, sf::RenderWindow &window,
                std::pair<char, char> &new_pick, std::pair<char, char> &picked,
                RedBox &redbox, map &Game,
                ResourceHolder<sf::Drawable> &Resource) noexcept;

void right_click(Thread &thread, std::pair<char, char> &picked,
                 RedBox &redbox) noexcept;

} // namespace MOUSE

#endif // KULKI_MOUSE_CLICK_EVENT_HPP
