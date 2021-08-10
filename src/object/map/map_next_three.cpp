#include "map.hpp"

void map::generate_next_three() noexcept
{
    //Generate random next three balls, which show in the next move
    auto type = m_random.generate<uint8_t>(1, 100);
    if ( type <= 33 ) // X% to generate diffrent next_three then before
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
        std::array<std::pair<uint8_t, uint8_t>, 5> color = {std::make_pair(0, 0), {0, 1}, {0, 2}, {0, 3}, {0, 4}};
        std::for_each(grid.begin(), grid.end(),
                      [&color](const auto &Row) mutable {
                          std::for_each(std::begin(Row), std::end(Row),
                                        [&color](const auto &Ball) mutable {
                                            if ( Ball.has_value() )
                                                ++color[static_cast<std::size_t>(Ball.enum_color())].first;
                                        });
                      });

        std::sort(std::begin(color), std::end(color),
                  [](const std::pair<uint8_t, uint8_t> lhs, const std::pair<uint8_t, uint8_t> rhs) {
                      return lhs.first < rhs.first;
                  });

        babel::ITERATOR::range Range(0, 3);
        std::transform(Range.begin(), Range.end(), next_three.begin(),
                       [&color](const std::size_t i) {
                           return ball(static_cast<COLOR>(color[i].second));;
                       });
    } else
    {
        std::for_each(std::begin(next_three), std::end(next_three),
                      [](ball &Ball) { Ball.random(); });

        while ( next_three[2] == next_three[0] || next_three[2] == next_three[1] )
            next_three[2].random();

        if ( m_random.generate<uint8_t>(1, 100) <= 5 ) // X% to TWO same ball in next round
        {
            next_three[0] = next_three[1];
            if ( m_random.random_generator::generate<uint8_t>(0, 1) == 0 )
            {
                auto rnd = m_random.generate<uint8_t>(0, 1);
                next_three[2].swap(next_three[rnd]);
            }
        } else
        {
            while ( next_three[1] == next_three[0] || next_three[1] == next_three[2] )
                next_three[1].random();
        }
    }
}

void map::put_next_three() noexcept
{
    if ( _filled == 81 )
        return;
    std::vector<std::pair<uint8_t, uint8_t>> free_pos;
    babel::ITERATOR::enumerator GridEnum(grid);
    std::for_each(GridEnum.begin(), GridEnum.end(), [&free_pos](const auto &RowEn) mutable {
        babel::ITERATOR::enumerator RowEnum(RowEn.second());
        std::for_each(RowEnum.begin(), RowEnum.end(),
                      [&free_pos, &RowEn](const auto &BallEnum) mutable {
                          if ( BallEnum.second().is_empty() )
                              free_pos.template emplace_back(std::make_pair(RowEn.first(), BallEnum.first()));
                      });

    });

    m_random.random_shuffle(free_pos);

    uint8_t to_insert = static_cast<uint8_t>(babel::ALGO::MATH::min(free_pos.size(), static_cast<size_t>(3)));
    int probe = 3;

    // Try add three ball, in good position ( no score added )
    while ( to_insert > 0 )
    {
        auto pos = m_random.generate<size_t>(0, free_pos.size() - 1);
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
    _filled = static_cast<uint8_t>(babel::ALGO::MATH::min(_filled + 3, 81));
    generate_next_three();
    check_for_score();
    _need_update = true;
}