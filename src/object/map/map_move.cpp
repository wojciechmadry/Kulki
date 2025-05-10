#include "map.hpp"
#include "randoms.hpp"

bool map::can_move(std::pair<uint8_t, uint8_t> from,
                   std::pair<uint8_t, uint8_t> to) const noexcept {
  if (at(from).is_empty() || !at(to).is_empty() || from == to) {
    return false;
  }
  auto cor_is_correct = [this](const std::pair<char, char> cor) -> bool {
    return !(cor.first > 8 || cor.first < 0 || cor.second > 8 ||
             cor.second < 0 ||
             !m_grid[static_cast<std::size_t>(static_cast<uint8_t>(cor.first))]
                    [static_cast<std::size_t>(cor.second)]
                        .is_empty());
  };
  std::pair<char, char> from_c = {from.first, from.second};
  std::pair<char, char> to_c = {to.first, to.second};

  std::array<std::pair<char, char>, 81> vec;
  std::array<std::pair<char, char>, 4> Coordinate;
  size_t _size = 1, _start = 0;
  vec[0] = to_c;
  size_t vec_size;

  do {
    vec_size = _size;
    auto found =
        std::find_if(vec.begin() + _start, vec.begin() + vec_size,
                     [&](const auto &Cor) mutable -> bool {
                       Coordinate[0].first = Cor.first + 1;
                       Coordinate[0].second = Cor.second;

                       Coordinate[1].first = Cor.first - 1;
                       Coordinate[1].second = Cor.second;

                       Coordinate[2].first = Cor.first;
                       Coordinate[2].second = Cor.second + 1;

                       Coordinate[3].first = Cor.first;
                       Coordinate[3].second = Cor.second - 1;

                       auto found_cor = std::find_if(
                           Coordinate.begin(), Coordinate.end(),
                           [&from_c, &cor_is_correct, &vec,
                            &_size](const auto &Item) mutable -> bool {
                             bool res_type = (Item == from_c);
                             if (!res_type) {
                               if (cor_is_correct(Item) &&
                                   std::find(vec.begin(), vec.begin() + _size,
                                             Item) == vec.begin() + _size)
                                 vec[_size++] = Item;
                             }
                             return res_type;
                           });
                       if (found_cor != Coordinate.end())
                         return true;
                       ++_start;
                       return false;
                     });
    if (found != vec.begin() + vec_size)
      return true;
  } while (vec_size != _size);

  return false;
}

bool map::move(const std::pair<uint8_t, uint8_t> from,
               const std::pair<uint8_t, uint8_t> to) noexcept {
  if (can_move(from, to)) {
    at(from).swap(at(to));
    if (!check_for_score())
      put_next_three();
    return true;
  }
  return false;
}

void map::random_move() noexcept {
  auto& e1 = rnd::get_rnd_eng().get();
  std::uniform_int_distribution<std::uint8_t> uniform_dist(0, 8);
  if (this->game_over()) {
    this->reset();
    return;
  }
  uint8_t x_from = 0, y_from = 0;
  uint8_t x_to = 0, y_to = 0;

  while (!this->is_free_at(x_to, y_to)) {
    x_to = uniform_dist(e1);
    y_to = uniform_dist(e1);
  }
  while (!this->can_move({x_from, y_from}, {x_to, y_to})) {
    x_from = uniform_dist(e1);
    y_from = uniform_dist(e1);
  }

  this->move({x_from, y_from}, {x_to, y_to});
}
