#include "map.hpp"

map::map() noexcept
{
    //Map started with 3 balls.
    generate_next_three();
    reset();
}

uint16_t map::get_score() const noexcept
{
    return score;
}

const std::array<ball, 3> &map::get_next_three() const noexcept
{
    return next_three;
}

std::array<ball, 3> &map::get_next_three() noexcept
{
    return next_three;
}

const std::array<std::array<ball, 9>, 9> &map::get_grid() const noexcept
{
    return grid;
}

std::array<std::array<ball, 9>, 9> &map::get_grid() noexcept
{
    return grid;
}

bool map::need_update() const noexcept
{
    return _need_update;
}

bool map::game_over() const noexcept
{
    return _filled == 81;
}

uint16_t map::filled() const noexcept
{
    return static_cast<uint16_t>(_filled);
}

void map::updated() noexcept
{
    _need_update = false;
}

void map::set_update(bool status) noexcept
{
    _need_update = status;
}

void map::reset() noexcept
{
    _need_update = true;
    _filled = 0;
    std::for_each(grid.begin(), grid.end(),
                  [](auto &Row) {
                      std::for_each(std::begin(Row), std::end(Row), [](auto &Ball) {
                          Ball.clear();
                      });
                  });
    put_next_three();
    score = 0;
}

void map::set_score(uint16_t a_new_score)
{
    score = a_new_score;
}

void map::set_filled(uint8_t a_new_fill)
{
    _filled = a_new_fill;
}
