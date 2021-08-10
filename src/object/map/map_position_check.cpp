#include "map.hpp"

bool map::is_free_at(const std::pair<uint8_t, uint8_t> position) const noexcept
{
    return grid[position.first][position.second].is_empty();
}

bool map::is_free_at(const uint8_t x, const uint8_t y) const noexcept
{
    return grid[x][y].is_empty();
}

void map::freed_on(const std::pair<uint8_t, uint8_t> position) noexcept
{
    grid[position.first][position.second].clear();
}

ball &map::at(const std::pair<uint8_t, uint8_t> position)
{
    if ( position.first > 8 || position.second > 8 )
        throw std::out_of_range("Grid out ouf range");
    return grid[position.first][position.second];
}

ball map::at(const std::pair<uint8_t, uint8_t> position) const
{
    if ( position.first > 8 || position.second > 8 )
        throw std::out_of_range("Grid out ouf range");
    return grid[position.first][position.second];
}

ball &map::at(uint8_t i, uint8_t j)
{
    if ( i > 8 || j > 8 )
        throw std::out_of_range("Grid out ouf range");
    return grid[i][j];
}

ball map::at(uint8_t i, uint8_t j) const
{
    if ( i > 8 || j > 8 )
        throw std::out_of_range("Grid out ouf range");
    return grid[i][j];
}