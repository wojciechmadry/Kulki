#include "map.hpp"

#include "babel/babel.hpp"

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
        uint8_t horizontal = !m_grid[i][0].is_empty();
        uint8_t horizontal_start = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 8) )
        {
            if ( !m_grid[i][j].is_empty() && m_grid[i][j] == m_grid[i][j + 1] )
                ++horizontal;
            else if ( !m_grid[i][j + 1].is_empty() && horizontal < 5 )
            {
                horizontal_start = j + 1;
                horizontal = 1;
            } else if ( horizontal > 4 && m_grid[i][j] != m_grid[i][j + 1] )
                break;
        }
        // Check if their more than 4 balls(5, 6 , ..., 9)
        if ( horizontal > 4 )
        {
            m_filled -= horizontal;
            score_added = true;
            m_score += get_scores(horizontal);
            m_need_update = true;
            uint8_t end_in = horizontal_start + horizontal;
            do
            {
                m_grid[i][horizontal_start++].clear(); // Clear ball from m_grid
            } while ( horizontal_start != end_in );
        }


        // vertical check

        uint8_t vertical = !m_grid[0][i].is_empty();
        uint8_t vertical_start = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 8) )
        {
            if ( !m_grid[j][i].is_empty() && m_grid[j][i] == m_grid[j + 1][i] )
                ++vertical;
            else if ( !m_grid[j + 1][i].is_empty() && vertical < 5 )
            {
                vertical_start = j + 1;
                vertical = 1;
            } else if ( vertical > 4 && m_grid[j][i] != m_grid[j + 1][i] )
                break;
        }

        if ( vertical > 4 )
        {
            m_filled -= vertical;
            score_added = true;
            m_score += get_scores(vertical);
            m_need_update = true;
            uint8_t end_in = vertical_start + vertical;
            do
            {
                m_grid[vertical_start++][i].clear();
            } while ( vertical_start != end_in );
        }

    }



    //diagonal check left/right down
    for ( auto start : babel::ITERATOR::range<uint8_t>(0, 5) )
    {
        //diagonal check left down
        uint8_t diagonal = !m_grid[start][0].is_empty();
        std::pair<uint8_t, uint8_t> diagonal_start = {start, 0};
        uint8_t add_to_i = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 9 - start - 1) )
        {
            if ( !m_grid[start + add_to_i][j].is_empty() &&
                 m_grid[start + add_to_i][j] == m_grid[start + add_to_i + 1][j + 1] )
                ++diagonal;
            else if ( !m_grid[start + add_to_i + 1][j + 1].is_empty() && diagonal < 5 )
            {
                diagonal_start = {start + add_to_i + 1, j + 1};
                diagonal = 1;
            } else if ( diagonal > 4 && m_grid[start + add_to_i][j] != m_grid[start + add_to_i + 1][j + 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
        {
            m_filled -= diagonal;
            score_added = true;
            m_score += get_scores(diagonal);
            m_need_update = true;
            auto color_to_clear = m_grid[diagonal_start.first][diagonal_start.second].color();
            while ( diagonal_start.first < 9 && diagonal_start.second < 9 &&
                    at(diagonal_start).color() == color_to_clear )
            {
                at(diagonal_start).clear();
                ++diagonal_start.first;
                ++diagonal_start.second;
            }
        }

        //diagonal check right down
        diagonal = !m_grid[start][8].is_empty();
        diagonal_start = {start, 8};
        add_to_i = 0;
        for ( uint8_t j = 8 ; j > start ; --j )
        {
            if ( !m_grid[start + add_to_i][j].is_empty() &&
                 m_grid[start + add_to_i][j] == m_grid[start + add_to_i + 1][j - 1] )
                ++diagonal;
            else if ( !m_grid[start + add_to_i + 1][j - 1].is_empty() && diagonal < 5 )
            {
                diagonal_start = {start + add_to_i + 1, j - 1};
                diagonal = 1;
            } else if ( diagonal > 4 && m_grid[start + add_to_i][j] != m_grid[start + add_to_i + 1][j - 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
        {
            m_filled -= diagonal;
            score_added = true;
            m_score += get_scores(diagonal);
            m_need_update = true;
            auto color_to_clear = m_grid[diagonal_start.first][diagonal_start.second].color();
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
        uint8_t diagonal = !m_grid[0][start].is_empty();
        std::pair<uint8_t, uint8_t> diagonal_start = {0, start};
        uint8_t add_to_i = 0;
        for ( auto j : babel::ITERATOR::range<uint8_t>(0, 9 - start - 1) )
        {
            if ( !m_grid[j][start + add_to_i].is_empty() &&
                 m_grid[j][start + add_to_i] == m_grid[j + 1][start + add_to_i + 1] )
                ++diagonal;
            else if ( !m_grid[j + 1][start + add_to_i + 1].is_empty() && diagonal < 5 )
            {
                diagonal_start = {j + 1, start + add_to_i + 1};
                diagonal = 1;
            } else if ( diagonal > 4 && m_grid[j][start + add_to_i] != m_grid[j + 1][start + add_to_i + 1] )
                break;
            ++add_to_i;
        }
        if ( diagonal > 4 )
        {
            m_filled -= diagonal;
            score_added = true;
            m_score += get_scores(diagonal);
            m_need_update = true;
            auto color_to_clear = m_grid[diagonal_start.first][diagonal_start.second].color();
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
        uint8_t diagonal = !m_grid[0][start].is_empty();
        std::pair<uint8_t, uint8_t> diagonal_start = {0, start};
        for ( uint8_t i = 0 ; i < start ; ++i )
        {
            if ( !m_grid[i][start - i].is_empty() && m_grid[i][start - i] == m_grid[i + 1][start - i - 1] )
                ++diagonal;
            else if ( !m_grid[i + 1][start - i - 1].is_empty() && diagonal < 5 )
            {
                diagonal_start = {i + 1, start - i - 1};
                diagonal = 1;
            } else if ( diagonal > 4 && m_grid[i][start - i] != m_grid[i + 1][start - i - 1] )
                break;
        }
        if ( diagonal > 4 )
        {
            m_filled -= diagonal;
            score_added = true;
            m_score += get_scores(diagonal);
            m_need_update = true;
            auto color_to_clear = m_grid[diagonal_start.first][diagonal_start.second].color();
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