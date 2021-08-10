//
// Created by Wojtek on 16.11.2020.
//

#ifndef KULKI_MAP_HPP
#define KULKI_MAP_HPP

#include "object/ball/ball.hpp"

class map;

class map
{

    std::array<std::array<ball, 9>, 9> grid;
    std::array<ball, 3> next_three;
    uint16_t score = 0;
    uint8_t _filled = 0;
    bool _need_update = true;
    babel::ALGO::MATH::random_generator m_random;

    [[nodiscard]] bool is_free_at(std::pair<uint8_t, uint8_t> position) const noexcept;

    [[nodiscard]] bool is_free_at(uint8_t x, uint8_t y) const noexcept;

    void freed_on(std::pair<uint8_t, uint8_t> position) noexcept;

    void generate_next_three() noexcept;

    // Put next three (random) balls on the grid (max 81 ball on grid)
    void put_next_three() noexcept;

public:
    map() noexcept;

    bool check_for_score() noexcept; // ? private

    [[nodiscard]] bool score_there() const noexcept; // ? private

    [[nodiscard]] ball &at(std::pair<uint8_t, uint8_t> position);

    [[nodiscard]] ball at(std::pair<uint8_t, uint8_t> position) const;

    [[nodiscard]] ball &at(uint8_t i, uint8_t j);

    [[nodiscard]] ball at(uint8_t i, uint8_t j) const;

    //Check if ball on 'from' can move to 'to'
    [[nodiscard]] bool can_move(std::pair<uint8_t, uint8_t> from, std::pair<uint8_t, uint8_t> to) const noexcept;

    // try to move ball 'from' to 'to'
    bool move(std::pair<uint8_t, uint8_t> from, std::pair<uint8_t, uint8_t> to) noexcept;

    [[nodiscard]] uint16_t get_score() const noexcept;

    [[nodiscard]] const std::array<ball, 3> &get_next_three() const noexcept;

    [[nodiscard]] std::array<ball, 3> &get_next_three() noexcept;  // ? to del

    [[nodiscard]] const std::array<std::array<ball, 9>, 9> &get_grid() const noexcept;

    [[nodiscard]] std::array<std::array<ball, 9>, 9> &get_grid() noexcept;  // ? to del

    [[nodiscard]] bool need_update() const noexcept;

    [[nodiscard]] bool game_over() const noexcept;

    [[nodiscard]] uint16_t filled() const noexcept;

    void updated() noexcept;

    // If you do smth out of map class you need set _need_update manually.
    void set_update(bool status) noexcept;

    //Start new game
    void reset() noexcept;

    void set_score(uint16_t a_new_score);  // ? to del

    void set_filled(uint8_t a_new_fill);  // ? to del
};


#endif //KULKI_MAP_HPP
