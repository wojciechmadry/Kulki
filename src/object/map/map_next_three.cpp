#include "map.hpp"

#include "babel/babel.hpp"

#include "function/random/random.hpp"

void map::generate_next_three() noexcept
{
    //Generate random next three balls, which show in the next move
    auto type = randomizer::get().generate<uint8_t>(1, 100);
    if ( type <= 33 ) // X% to generate different next_three then before
    {
        std::array<ball, 3> nb;
        std::for_each(std::begin(nb), std::end(nb), [&](ball &b) {
            b.random();
            while ( b == m_next_three[0] || b == m_next_three[1] || b == m_next_three[2] )
                b.random();
        });

        if ( nb[2] == nb[1] && nb[2] == nb[0] )
            while ( nb[2] == nb[1] || nb[2] == m_next_three[0] || nb[2] == m_next_three[1] || nb[2] == m_next_three[2] )
                nb[2].random();
        m_next_three = nb;
    } else if ( type <= 45 ) // (X - Y) % you get the least popular balls in board
    {
        std::array<std::pair<uint8_t, uint8_t>, 5> color = {std::make_pair(0, 0), {0, 1}, {0, 2}, {0, 3}, {0, 4}};
        std::for_each(m_grid.begin(), m_grid.end(),
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
        std::transform(Range.begin(), Range.end(), m_next_three.begin(),
                       [&color](const std::size_t i) {
                           return ball(static_cast<COLOR>(color[i].second));
                       });
    } else
    {
        std::for_each(std::begin(m_next_three), std::end(m_next_three),
                      [](ball &Ball) { Ball.random(); });

        while ( m_next_three[2] == m_next_three[0] || m_next_three[2] == m_next_three[1] )
            m_next_three[2].random();

        if ( randomizer::get().generate<uint8_t>(1, 100) <= 5 ) // X% to TWO same ball in next round
        {
            m_next_three[0] = m_next_three[1];
            if ( randomizer::get().random_generator::generate<uint8_t>(0, 1) == 0 )
            {
                auto rnd = randomizer::get().generate<uint8_t>(0, 1);
                m_next_three[2].swap(m_next_three[rnd]);
            }
        } else
        {
            while ( m_next_three[1] == m_next_three[0] || m_next_three[1] == m_next_three[2] )
                m_next_three[1].random();
        }
    }
}

void map::put_next_three() noexcept
{
    if ( m_filled == 81 )
        return;
    std::vector<std::pair<uint8_t, uint8_t>> free_pos;
    babel::ITERATOR::enumerator GridEnum(m_grid);
    std::for_each(GridEnum.begin(), GridEnum.end(), [&free_pos](const auto &RowEn) mutable {
        babel::ITERATOR::enumerator RowEnum(RowEn.second());
        std::for_each(RowEnum.begin(), RowEnum.end(),
                      [&free_pos, &RowEn](const auto &BallEnum) mutable {
                          if ( BallEnum.second().is_empty() )
                              free_pos.template emplace_back(std::make_pair(RowEn.first(), BallEnum.first()));
                      });

    });

    randomizer::get().random_shuffle(free_pos);

    auto to_insert = static_cast<uint8_t>(babel::ALGO::MATH::min(free_pos.size(), static_cast<size_t>(3)));
    int probe = 3;

    // Try to add three ball, in good position ( no score added )
    while ( to_insert > 0 )
    {
        auto pos = randomizer::get().generate<size_t>(0, free_pos.size() - 1);
        if ( at(free_pos[pos]).is_empty() )
        {
            at(free_pos[pos]) = m_next_three[to_insert - 1];
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
                        m_next_three[1].swap(m_next_three[2]);
                        at(free_pos[pos]) = m_next_three[2];
                        if ( score_there() )
                        {
                            m_next_three[0].swap(m_next_three[2]);
                            at(free_pos[pos]) = m_next_three[2];
                        }
                    } else if ( to_insert == 2 )
                    {
                        m_next_three[0].swap(m_next_three[1]);
                        at(free_pos[pos]) = m_next_three[1];
                    } else
                    {
                        auto found = std::find_if(std::begin(free_pos), std::end(free_pos), [&](std::pair<uint8_t, uint8_t> all_pos){
                            return  all_pos != free_pos[pos] && at(all_pos).is_empty();
                        });

                        if (found != std::end(free_pos))
                        {
                            at(*found) = m_next_three[0];
                        }
                        else
                        {
                            at(free_pos[pos]) = m_next_three[0];
                        }
                    }
                    --to_insert;
                    probe = 3;
                }
            }
        }
    }
    m_filled = static_cast<uint8_t>(babel::ALGO::MATH::min(m_filled + 3, 81));
    generate_next_three();
    check_for_score();
    m_need_update = true;
}