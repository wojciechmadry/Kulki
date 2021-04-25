//
// Created by Wojtek on 16.11.2020.
//

#ifndef KULKI_MAP_HPP
#define KULKI_MAP_HPP

#include "ball.hpp"
#include <iostream>

class map;

map load_map() noexcept;

class map
{
    friend map load_map() noexcept;

    std::array<std::array<ball, 9>, 9> grid;
    std::array<ball, 3> next_three;
    uint16_t score = 0;
    byte _filled = 0;
    bool _need_update = true;


    [[nodiscard]] bool is_free_at(const std::pair<byte, byte> position) const noexcept
    {
        return grid[position.first][position.second].is_empty();
    }

    [[nodiscard]] bool is_free_at(const byte x, const byte y) const noexcept
    {
        return grid[x][y].is_empty();
    }


    void free_on(const std::pair<byte, byte> position) noexcept
    {
        grid[position.first][position.second].clear();
    }

    [[nodiscard]] bool score_there() const noexcept
    {
        for ( byte i = 0 ; i < 9 ; ++i )
        {
            //horizontal check
            byte horizontal = !grid[i][0].is_empty();
            for ( byte j = 0 ; j < 8 ; ++j )
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

            byte vertical = !grid[0][i].is_empty();
            for ( byte j = 0 ; j < 8 ; ++j )
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
        for ( byte start = 0 ; start < 5 ; ++start )
        {
            //diagonal check left down
            byte diagonal = !grid[start][0].is_empty();
            std::pair<byte, byte> diagonal_start = {start, 0};
            byte add_to_i = 0;
            for ( byte j = 0 ; j < static_cast<byte>(9 - start - 1) ; ++j )
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
                return true;

            //diagonal check right down
            diagonal = !grid[start][8].is_empty();
            diagonal_start = {start, 8};
            add_to_i = 0;
            for ( byte j = 8 ; j > start ; --j )
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
                return true;
        }



        //diagonal check left up
        for ( byte start = 1 ; start < 5 ; ++start )
        {
            byte diagonal = !grid[0][start].is_empty();
            std::pair<byte, byte> diagonal_start = {0, start};
            byte add_to_i = 0;
            for ( byte j = 0 ; j < static_cast<byte>(9 - start - 1) ; ++j )
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
                return true;
        }


        //diagonal check right up
        for ( byte start = 7 ; start > 3 ; --start )
        {
            byte diagonal = !grid[0][start].is_empty();
            std::pair<byte, byte> diagonal_start = {0, start};
            for ( byte i = 0 ; i < start ; ++i )
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
                return true;
        }

        return false;
    }

    bool check_for_score() noexcept
    {
        bool score_added = false;
        // number should be greater or equal 5 !
        auto get_scores = [](const byte number) -> byte {
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


        for ( byte i = 0 ; i < 9 ; ++i )
        {
            //horizontal check
            byte horizontal = !grid[i][0].is_empty();
            byte horizontal_start = 0;
            for ( byte j = 0 ; j < 8 ; ++j )
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
                byte end_in = horizontal_start + horizontal;
                do
                {
                    grid[i][horizontal_start++].clear(); // Clear ball from grid
                } while ( horizontal_start != end_in );
            }


            // vertical check

            byte vertical = !grid[0][i].is_empty();
            byte vertical_start = 0;
            for ( byte j = 0 ; j < 8 ; ++j )
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
                byte end_in = vertical_start + vertical;
                do
                {
                    grid[vertical_start++][i].clear();
                } while ( vertical_start != end_in );
            }

        }



        //diagonal check left/right down
        for ( byte start = 0 ; start < 5 ; ++start )
        {
            //diagonal check left down
            byte diagonal = !grid[start][0].is_empty();
            std::pair<byte, byte> diagonal_start = {start, 0};
            byte add_to_i = 0;
            for ( byte j = 0 ; j < static_cast<byte>(9 - start - 1) ; ++j )
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
            for ( byte j = 8 ; j > start ; --j )
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
                while ( diagonal_start.first < 9 && diagonal_start.second >= 0 &&
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
        for ( byte start = 1 ; start < 5 ; ++start )
        {
            byte diagonal = !grid[0][start].is_empty();
            std::pair<byte, byte> diagonal_start = {0, start};
            byte add_to_i = 0;
            for ( byte j = 0 ; j < static_cast<byte>(9 - start - 1) ; ++j )
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
        for ( byte start = 7 ; start > 3 ; --start )
        {
            byte diagonal = !grid[0][start].is_empty();
            std::pair<byte, byte> diagonal_start = {0, start};
            for ( byte i = 0 ; i < start ; ++i )
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
                while ( diagonal_start.first < 9 && diagonal_start.second >= 0 &&
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


    void generate_next_three() noexcept
    {
        //Generate random next three balls, which show in the next move
        auto type = random_generator::generate<byte>(1, 100);
        if ( type <= 33 ) // X% to generate diffrent next_three than before
        {
            std::array<ball, 3> nb;
            std::for_each(std::begin(nb), std::end(nb), [&](ball &b) {
                b.random();
                while ( b == next_three[0] || b == next_three[1] || b == next_three[2] )
                    b.random();
            });

            if ( nb[2] == nb[1] && nb[2] == nb[0] )
                while ( nb[2] == nb[1] || nb[2] == next_three[0] || nb[2] == next_three[1] || nb[2] == next_three[2] )
                    nb[2].random();
            next_three = nb;
        } else if ( type <= 45 ) // (X - Y) % you get the least popular balls in board
        {
            std::array<std::pair<byte, byte>, 5> color = {std::make_pair(0, 0), {0, 1}, {0, 2}, {0, 3}, {0, 4}};
            for ( const auto &ARRAY : grid )
                for ( auto BALL : ARRAY )
                    if ( !BALL.is_empty() )
                        ++color[static_cast<std::size_t>(BALL.enum_color())].first;

            std::sort(std::begin(color), std::end(color),
                      [](const std::pair<byte, byte> lhs, const std::pair<byte, byte> rhs) {
                          return lhs.first < rhs.first;
                      });

            for ( byte i = 0 ; i < 3 ; ++i )
                next_three[i] = ball(static_cast<COLOR>(color[i].second));


        } else
        {
            std::for_each(std::begin(next_three), std::end(next_three),
                          [](ball &Ball) { Ball.random(); });

            while ( next_three[2] == next_three[0] || next_three[2] == next_three[1] )
                next_three[2].random();

            if ( random_generator::generate<byte>(1, 100) <= 5 ) // X% to TWO same ball in next round
            {
                next_three[0] = next_three[1];
                if ( random_generator::generate<byte>(0, 1) == 0 )
                {
                    auto rnd = random_generator::generate<byte>(0, 1);
                    next_three[2].swap(next_three[rnd]);
                }
            } else
            {
                while ( next_three[1] == next_three[0] || next_three[1] == next_three[2] )
                    next_three[1].random();
            }
        }
    }

public:
    // Put next three (random) balls on the grid (max 81 ball on grid)
    void put_next_three() noexcept
    {
        if ( _filled == 81 )
            return;
        std::vector<std::pair<byte, byte>> free_pos;
        for ( byte i = 0 ; i < 9 ; ++i )
            for ( byte j = 0 ; j < 9 ; ++j )
                if ( grid[i][j].is_empty() )
                    free_pos.emplace_back(std::make_pair(i, j));

        random_generator::random_shuffle(free_pos);

        byte to_insert = babel::MATH::min(free_pos.size(), static_cast<size_t>(3));
        int probe = 3;

        // Try add three ball, in good position ( no score added )
        while ( to_insert > 0 )
        {
            auto pos = random_generator::generate<size_t>(0, free_pos.size() - 1);
            if ( at(free_pos[pos]).is_empty() )
            {
                at(free_pos[pos]) = next_three[to_insert - 1];
                if ( !score_there() )
                {
                    --to_insert;
                    probe = 3;
                } else
                {
                    at(free_pos[pos]).set(COLOR::empty);
                    --probe;
                    if ( probe == 0 )
                    {
                        if ( to_insert == 3 )
                        {
                            next_three[1].swap(next_three[2]);
                            at(free_pos[pos]) = next_three[2];
                            if ( score_there() )
                            {
                                next_three[0].swap(next_three[2]);
                                at(free_pos[pos]) = next_three[2];
                            }
                        } else if ( to_insert == 2 )
                        {
                            next_three[0].swap(next_three[1]);
                            at(free_pos[pos]) = next_three[1];
                        } else
                        {
                            bool added = false;
                            for ( auto all_pos : free_pos )
                            {
                                if ( all_pos != free_pos[pos] && at(all_pos).is_empty() )
                                {
                                    at(all_pos) = next_three[0];
                                    added = true;
                                    break;
                                }
                            }
                            if ( !added )
                            {
                                at(free_pos[pos]) = next_three[0];
                            }
                        }
                        --to_insert;
                        probe = 3;
                    }
                }
            }
        }
        _filled = babel::MATH::min(_filled + 3, 81);
        generate_next_three();
        check_for_score();
        _need_update = true;
    }

public:
    map() noexcept
    {
        //Map started with 3 balls.
        do
        {
            auto x = random_generator::generate<byte>(0, 8);
            auto y = random_generator::generate<byte>(0, 8);
            if ( is_free_at(x, y) )
            {
                grid[x][y].random();
                ++_filled;
            }
        } while ( _filled != 3 );
        generate_next_three();
    }

    [[nodiscard]] ball &at(const std::pair<byte, byte> position)
    {
        if ( position.first > 8 || position.second > 8 )
            throw std::out_of_range("Grid out ouf range");
        return grid[position.first][position.second];
    }

    [[nodiscard]] ball at(const std::pair<byte, byte> position) const
    {
        if ( position.first > 8 || position.second > 8 )
            throw std::out_of_range("Grid out ouf range");
        return grid[position.first][position.second];
    }

    [[nodiscard]] ball &at(byte i, byte j)
    {
        if ( i > 8 || j > 8 )
            throw std::out_of_range("Grid out ouf range");
        return grid[i][j];
    }

    [[nodiscard]] ball at(byte i, byte j) const
    {
        if ( i > 8 || j > 8 )
            throw std::out_of_range("Grid out ouf range");
        return grid[i][j];
    }

    //Check if ball on 'from' can move to 'to'
    [[nodiscard]] bool can_move(std::pair<byte, byte> from, std::pair<byte, byte> to) const noexcept
    {
        if ( at(from).is_empty() || !at(to).is_empty() || from == to )
            return false;
        auto cor_is_correct = [this](const std::pair<char, char> cor) -> bool {
            return !( cor.first > 8 || cor.first < 0 || cor.second > 8 || cor.second < 0 ||
                      !grid[cor.first][cor.second].is_empty() );
        };
        std::pair<char, char> from_c = {from.first, from.second};
        std::pair<char, char> to_c = {to.first, to.second};

        std::vector<std::pair<char, char> > vec(81, std::make_pair(-1, -1));
        std::array<std::pair<char, char>, 4> Coordinate;
        size_t _size = 1, _start = 0;
        vec[0] = to_c;
        size_t vec_size;
        do
        {
            vec_size = _size;
            for ( size_t i = _start ; i < vec_size ; ++i )
            {
                auto Cor = vec[i];
                Coordinate[0].first = Cor.first + 1;
                Coordinate[0].second = Cor.second;

                Coordinate[1].first = Cor.first - 1;
                Coordinate[1].second = Cor.second;

                Coordinate[2].first = Cor.first;
                Coordinate[2].second = Cor.second + 1;

                Coordinate[3].first = Cor.first;
                Coordinate[3].second = Cor.second - 1;

                for ( const auto Item : Coordinate )
                {
                    if ( Item == from_c )
                        return true;
                    if ( cor_is_correct(Item) && std::find(vec.begin(), vec.end(), Item) == vec.end() )
                        vec[_size++] = Item;
                }
                ++_start;
            }

        } while ( vec_size != _size );

        return false;
    }

    // try to move ball 'from' to 'to'
    bool move(const std::pair<byte, byte> from, const std::pair<byte, byte> to) noexcept
    {
        if ( can_move(from, to) )
        {
            at(from).swap(at(to));
            if ( !check_for_score() )
                put_next_three();
            return true;
        }
        return false;
    }

    [[nodiscard]] uint16_t get_score() const noexcept
    {
        return score;
    }

    [[nodiscard]] const auto &get_next_three() const noexcept
    {
        return next_three;
    }

    [[nodiscard]] const auto &get_grid() const noexcept
    {
        return grid;
    }

    [[nodiscard]] bool need_update() const noexcept
    {
        return _need_update;
    }

    [[nodiscard]] bool game_over() const noexcept
    {
        return _filled == 81;
    }

    [[nodiscard]] uint16_t filled() const noexcept
    {
        return static_cast<uint16_t>(_filled);
    }

    void updated() noexcept
    {
        _need_update = false;
    }

    // If you do smth out of map class you need set _need_update manually.
    void set_update(bool status) noexcept
    {
        _need_update = status;
    }

    //Start new game
    void reset() noexcept
    {
        _need_update = true;
        _filled = 0;
        for ( auto &Array : grid )
            for ( auto &Ball : Array )
                Ball.clear();
        put_next_three();
        score = 0;
    }
};



#endif //KULKI_MAP_HPP
