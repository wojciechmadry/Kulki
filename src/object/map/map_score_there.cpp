#include "map.hpp"

bool map::score_there() const noexcept
{
    for ( auto i : babel::ITERATOR::range<uint8_t>(0, 9) )
    {
        //horizontal check
        uint8_t horizontal = !grid[i][0].is_empty();
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 8) )
        {
            if ( !grid[i][j].is_empty() && grid[i][j] == grid[i][j + 1] )
                ++horizontal;
            else if ( !grid[i][j + 1].is_empty() && horizontal < 5 )
            {
                horizontal = 1;
            } else if ( horizontal > 4 && grid[i][j] != grid[i][j + 1] )
                break;
        }
        if ( horizontal > 4 )
            return true;


        // vertical check

        uint8_t vertical = !grid[0][i].is_empty();
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 8) )
        {
            if ( !grid[j][i].is_empty() && grid[j][i] == grid[j + 1][i] )
                ++vertical;
            else if ( !grid[j + 1][i].is_empty() && vertical < 5 )
            {
                vertical = 1;
            } else if ( vertical > 4 && grid[j][i] != grid[j + 1][i] )
                break;
        }

        if ( vertical > 4 )
            return true;

    }



    //diagonal check left/right down
    for ( auto start : babel::ITERATOR::range<uint8_t>(0, 5) )
    {
        //diagonal check left down
        uint8_t diagonal = !grid[start][0].is_empty();
        uint8_t add_to_i = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 9 - start - 1) )
        {
            if ( !grid[start + add_to_i][j].is_empty() &&
                 grid[start + add_to_i][j] == grid[start + add_to_i + 1][j + 1] )
                ++diagonal;
            else if ( !grid[start + add_to_i + 1][j + 1].is_empty() && diagonal < 5 )
            {
                diagonal = 1;
            } else if ( diagonal > 4 && grid[start + add_to_i][j] != grid[start + add_to_i + 1][j + 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
            return true;

        //diagonal check right down
        diagonal = !grid[start][8].is_empty();
        add_to_i = 0;
        for ( uint8_t j = 8 ; j > start ; --j )
        {
            if ( !grid[start + add_to_i][j].is_empty() &&
                 grid[start + add_to_i][j] == grid[start + add_to_i + 1][j - 1] )
                ++diagonal;
            else if ( !grid[start + add_to_i + 1][j - 1].is_empty() && diagonal < 5 )
            {
                diagonal = 1;
            } else if ( diagonal > 4 && grid[start + add_to_i][j] != grid[start + add_to_i + 1][j - 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
            return true;
    }



    //diagonal check left up
    for ( auto start : babel::ITERATOR::range<uint8_t>(1, 5) )
    {
        uint8_t diagonal = !grid[0][start].is_empty();
        uint8_t add_to_i = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 9 - start - 1) )
        {
            if ( !grid[j][start + add_to_i].is_empty() &&
                 grid[j][start + add_to_i] == grid[j + 1][start + add_to_i + 1] )
                ++diagonal;
            else if ( !grid[j + 1][start + add_to_i + 1].is_empty() && diagonal < 5 )
            {
                diagonal = 1;
            } else if ( diagonal > 4 && grid[j][start + add_to_i] != grid[j + 1][start + add_to_i + 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
            return true;
    }


    //diagonal check right up
    for ( uint8_t start = 7 ; start > 3 ; --start )
    {
        uint8_t diagonal = !grid[0][start].is_empty();
        for ( uint8_t i = 0 ; i < start ; ++i )
        {
            if ( !grid[i][start - i].is_empty() && grid[i][start - i] == grid[i + 1][start - i - 1] )
                ++diagonal;
            else if ( !grid[i + 1][start - i - 1].is_empty() && diagonal < 5 )
            {
                diagonal = 1;
            } else if ( diagonal > 4 && grid[i][start - i] != grid[i + 1][start - i - 1] )
                break;
        }
        if ( diagonal > 4 )
            return true;
    }

    return false;
}