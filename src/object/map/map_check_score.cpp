#include "map.hpp"

bool map::check_for_score() noexcept
{
    bool score_added = false;
    // number should be greater or equal 5 !
    auto get_scores = [](const uint8_t number) -> uint8_t {
        if ( number < 7 )
            return number * 2;
        if ( number == 7 )
            return 18;
        else if ( number == 8 )
            return 28;
        return 42;
    };
    // 5 balls 10 score
    // 6 balls 12 score
    // 7 balls 18 score
    // 8 balls 28 score
    // 9 balls 42 score


    for ( auto i : babel::ITERATOR::range<uint8_t>(0, 9) )
    {
        //horizontal check
        uint8_t horizontal = !grid[i][0].is_empty();
        uint8_t horizontal_start = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 8) )
        {
            if ( !grid[i][j].is_empty() && grid[i][j] == grid[i][j + 1] )
                ++horizontal;
            else if ( !grid[i][j + 1].is_empty() && horizontal < 5 )
            {
                horizontal_start = j + 1;
                horizontal = 1;
            } else if ( horizontal > 4 && grid[i][j] != grid[i][j + 1] )
                break;
        }
        // Check if there more than 4 balls(5, 6 , ..., 9)
        if ( horizontal > 4 )
        {
            _filled -= horizontal;
            score_added = true;
            score += get_scores(horizontal);
            _need_update = true;
            uint8_t end_in = horizontal_start + horizontal;
            do
            {
                grid[i][horizontal_start++].clear(); // Clear ball from grid
            } while ( horizontal_start != end_in );
        }


        // vertical check

        uint8_t vertical = !grid[0][i].is_empty();
        uint8_t vertical_start = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 8) )
        {
            if ( !grid[j][i].is_empty() && grid[j][i] == grid[j + 1][i] )
                ++vertical;
            else if ( !grid[j + 1][i].is_empty() && vertical < 5 )
            {
                vertical_start = j + 1;
                vertical = 1;
            } else if ( vertical > 4 && grid[j][i] != grid[j + 1][i] )
                break;
        }

        if ( vertical > 4 )
        {
            _filled -= vertical;
            score_added = true;
            score += get_scores(vertical);
            _need_update = true;
            uint8_t end_in = vertical_start + vertical;
            do
            {
                grid[vertical_start++][i].clear();
            } while ( vertical_start != end_in );
        }

    }



    //diagonal check left/right down
    for ( auto start : babel::ITERATOR::range<uint8_t>(0, 5) )
    {
        //diagonal check left down
        uint8_t diagonal = !grid[start][0].is_empty();
        std::pair<uint8_t, uint8_t> diagonal_start = {start, 0};
        uint8_t add_to_i = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 9 - start - 1) )
        {
            if ( !grid[start + add_to_i][j].is_empty() &&
                 grid[start + add_to_i][j] == grid[start + add_to_i + 1][j + 1] )
                ++diagonal;
            else if ( !grid[start + add_to_i + 1][j + 1].is_empty() && diagonal < 5 )
            {
                diagonal_start = {start + add_to_i + 1, j + 1};
                diagonal = 1;
            } else if ( diagonal > 4 && grid[start + add_to_i][j] != grid[start + add_to_i + 1][j + 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
        {
            _filled -= diagonal;
            score_added = true;
            score += get_scores(diagonal);
            _need_update = true;
            auto color_to_clear = grid[diagonal_start.first][diagonal_start.second].color();
            while ( diagonal_start.first < 9 && diagonal_start.second < 9 &&
                    at(diagonal_start).color() == color_to_clear )
            {
                at(diagonal_start).clear();
                ++diagonal_start.first;
                ++diagonal_start.second;
            }
        }

        //diagonal check right down
        diagonal = !grid[start][8].is_empty();
        diagonal_start = {start, 8};
        add_to_i = 0;
        for ( uint8_t j = 8 ; j > start ; --j )
        {
            if ( !grid[start + add_to_i][j].is_empty() &&
                 grid[start + add_to_i][j] == grid[start + add_to_i + 1][j - 1] )
                ++diagonal;
            else if ( !grid[start + add_to_i + 1][j - 1].is_empty() && diagonal < 5 )
            {
                diagonal_start = {start + add_to_i + 1, j - 1};
                diagonal = 1;
            } else if ( diagonal > 4 && grid[start + add_to_i][j] != grid[start + add_to_i + 1][j - 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
        {
            _filled -= diagonal;
            score_added = true;
            score += get_scores(diagonal);
            _need_update = true;
            auto color_to_clear = grid[diagonal_start.first][diagonal_start.second].color();
            while ( diagonal_start.first < 9 &&
                    at(diagonal_start).color() == color_to_clear )
            {
                at(diagonal_start).clear();
                ++diagonal_start.first;
                if ( diagonal_start.second != 0 )
                    --diagonal_start.second;
            }
        }
    }



    //diagonal check left up
    for ( auto start : babel::ITERATOR::range<uint8_t>(1, 5) )
    {
        uint8_t diagonal = !grid[0][start].is_empty();
        std::pair<uint8_t, uint8_t> diagonal_start = {0, start};
        uint8_t add_to_i = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 9 - start - 1) )
        {
            if ( !grid[j][start + add_to_i].is_empty() &&
                 grid[j][start + add_to_i] == grid[j + 1][start + add_to_i + 1] )
                ++diagonal;
            else if ( !grid[j + 1][start + add_to_i + 1].is_empty() && diagonal < 5 )
            {
                diagonal_start = {j + 1, start + add_to_i + 1};
                diagonal = 1;
            } else if ( diagonal > 4 && grid[j][start + add_to_i] != grid[j + 1][start + add_to_i + 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
        {
            _filled -= diagonal;
            score_added = true;
            score += get_scores(diagonal);
            _need_update = true;
            auto color_to_clear = grid[diagonal_start.first][diagonal_start.second].color();
            while ( diagonal_start.first < 9 && diagonal_start.second < 9 &&
                    at(diagonal_start).color() == color_to_clear )
            {
                at(diagonal_start).clear();
                ++diagonal_start.first;
                ++diagonal_start.second;
            }
        }
    }


    //diagonal check right up
    for ( uint8_t start = 7 ; start > 3 ; --start )
    {
        uint8_t diagonal = !grid[0][start].is_empty();
        std::pair<uint8_t, uint8_t> diagonal_start = {0, start};
        for ( uint8_t i = 0 ; i < start ; ++i )
        {
            if ( !grid[i][start - i].is_empty() && grid[i][start - i] == grid[i + 1][start - i - 1] )
                ++diagonal;
            else if ( !grid[i + 1][start - i - 1].is_empty() && diagonal < 5 )
            {
                diagonal_start = {i + 1, start - i - 1};
                diagonal = 1;
            } else if ( diagonal > 4 && grid[i][start - i] != grid[i + 1][start - i - 1] )
                break;
        }
        if ( diagonal > 4 )
        {
            _filled -= diagonal;
            score_added = true;
            score += get_scores(diagonal);
            _need_update = true;
            auto color_to_clear = grid[diagonal_start.first][diagonal_start.second].color();
            while ( diagonal_start.first < 9 &&
                    at(diagonal_start).color() == color_to_clear )
            {
                at(diagonal_start).clear();
                ++diagonal_start.first;
                if ( diagonal_start.second != 0 )
                    --diagonal_start.second;
            }
        }
    }

    return score_added;
}