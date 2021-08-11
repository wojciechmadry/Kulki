#include "map.hpp"

map::map() noexcept
{
    //Map started with 3 balls.
    generate_next_three();
    reset();
}

uint16_t map::get_score() const noexcept
{
    return m_score;
}

const std::array<ball, 3> &map::get_next_three() const noexcept
{
    return m_next_three;
}

const std::array<std::array<ball, 9>, 9> &map::get_grid() const noexcept
{
    return m_grid;
}

bool map::need_update() const noexcept
{
    return m_need_update;
}

bool map::game_over() const noexcept
{
    return m_filled == 81;
}

uint16_t map::filled() const noexcept
{
    return static_cast<uint16_t>(m_filled);
}

void map::updated() noexcept
{
    m_need_update = false;
}

void map::set_update(bool status) noexcept
{
    m_need_update = status;
}

void map::reset() noexcept
{
    m_need_update = true;
    m_filled = 0;
    std::for_each(m_grid.begin(), m_grid.end(),
                  [](auto &Row) {
                      std::for_each(std::begin(Row), std::end(Row), [](auto &Ball) {
                          Ball.clear();
                      });
                  });
    put_next_three();
    m_score = 0;
}

void map::load_game(const uint16_t a_new_score, const uint8_t a_new_fill, const std::array<ball, 3> &a_new_next_three,
                    const std::array<std::array<ball, 9>, 9> &a_new_grid)
{
    m_score = a_new_score;
    m_filled = a_new_fill;
    m_next_three = a_new_next_three;
    m_grid = a_new_grid;
}