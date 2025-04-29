
#include "map.hpp"
#include <algorithm>
#include <random>

void map::generate_next_three() noexcept {
  static std::random_device r;
  static std::default_random_engine e1(r());
  std::uniform_int_distribution<std::uint8_t> uniform_dist(1, 100);
  std::uniform_int_distribution<std::uint8_t> bool_dist(0, 1);
  // Generate random next three balls, which show in the next move
  auto type = uniform_dist(e1);
  if (type <= 33) // X% to generate different next_three then before
  {
    std::array<ball, 3> nb;
    std::for_each(std::begin(nb), std::end(nb), [&](ball &b) {
      b.random();
      while (b == m_next_three[0] || b == m_next_three[1] ||
             b == m_next_three[2])
        b.random();
    });

    if (nb[2] == nb[1] && nb[2] == nb[0])
      while (nb[2] == nb[1] || nb[2] == m_next_three[0] ||
             nb[2] == m_next_three[1] || nb[2] == m_next_three[2])
        nb[2].random();
    m_next_three = nb;

  } else if (type <= 45) // (X - Y) % you get the least popular balls in board
  {
    std::array<std::pair<uint8_t, uint8_t>,
               static_cast<std::size_t>(COLOR::empty)>
        color = {std::make_pair(0, 0), {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}};
    std::for_each(
        m_grid.begin(), m_grid.end(), [&color](const auto &Row) mutable {
          std::for_each(std::begin(Row), std::end(Row),
                        [&color](const auto &Ball) mutable {
                          if (Ball.has_value()) {
                            const auto id =
                                static_cast<std::size_t>(Ball.enum_color());
                            ++color[id].first;
                          }
                        });
        });

    std::sort(std::begin(color), std::end(color),
              [](const std::pair<uint8_t, uint8_t> lhs,
                 const std::pair<uint8_t, uint8_t> rhs) {
                return lhs.first < rhs.first;
              });

    for (std::size_t i = 0U; i < m_next_three.size(); ++i) {
      m_next_three[i] = ball(static_cast<COLOR>(color[i].second));
    }

  } else {

    std::for_each(std::begin(m_next_three), std::end(m_next_three),
                  [](ball &Ball) { Ball.random(); });

    while (m_next_three[2] == m_next_three[0] ||
           m_next_three[2] == m_next_three[1])
      m_next_three[2].random();

    if (uniform_dist(e1) <= 5) // X% to TWO same ball in next round
    {
      m_next_three[0] = m_next_three[1];
      if (bool_dist(e1) == 0) {
        auto rnd = bool_dist(e1);
        m_next_three[2].swap(m_next_three[rnd]);
      }
    } else {
      while (m_next_three[1] == m_next_three[0] ||
             m_next_three[1] == m_next_three[2])
        m_next_three[1].random();
    }
  }
}

void map::put_next_three() noexcept {
  if (m_filled == 81)
    return;
  std::vector<std::pair<uint8_t, uint8_t>> free_pos;
  for (std::size_t col = 0U; col < m_grid.size(); ++col) {
    for (std::size_t row = 0U; row < m_grid[col].size(); ++row) {
      if (m_grid[col][row].is_empty())
        free_pos.emplace_back(std::make_pair(col, row));
    }
  }

  static std::random_device r;
  static std::default_random_engine e1(r());
  std::uniform_int_distribution<std::size_t> uniform_dist(0,
                                                          free_pos.size() - 1);

  std::shuffle(free_pos.begin(), free_pos.end(), e1);

  auto to_insert =
      static_cast<uint8_t>(std::min(free_pos.size(), static_cast<size_t>(3)));
  int probe = 3;

  // Try to add three ball, in good position ( no score added )
  while (to_insert > 0) {
    auto pos = uniform_dist(e1);
    if (at(free_pos[pos]).is_empty()) {
      at(free_pos[pos]) = m_next_three[to_insert - 1];
      if (!score_there()) {
        --to_insert;
        probe = 3;
      } else {
        at(free_pos[pos]).set(COLOR::empty);
        --probe;
        if (probe == 0) {
          if (to_insert == 3) {
            m_next_three[1].swap(m_next_three[2]);
            at(free_pos[pos]) = m_next_three[2];
            if (score_there()) {
              m_next_three[0].swap(m_next_three[2]);
              at(free_pos[pos]) = m_next_three[2];
            }
          } else if (to_insert == 2) {
            m_next_three[0].swap(m_next_three[1]);
            at(free_pos[pos]) = m_next_three[1];
          } else {
            bool added = false;
            for (auto all_pos : free_pos) {
              if (all_pos != free_pos[pos] && at(all_pos).is_empty()) {
                at(all_pos) = m_next_three[0];
                added = true;
                break;
              }
            }
            if (!added) {
              at(free_pos[pos]) = m_next_three[0];
            }
          }
          --to_insert;
          probe = 3;
        }
      }
    }
  }
  m_filled = static_cast<uint8_t>(std::min(m_filled + 3, 81));
  generate_next_three();
  check_for_score();
  m_need_update = true;
}
