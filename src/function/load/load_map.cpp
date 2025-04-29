#include "crypt.hpp"
#include "load.hpp"
#include <fstream>
#include <string>

map load_map() noexcept {
  namespace fs = std::filesystem;
  try {
    if (!fs::exists("kulkim.bin"))
      return map{};
    std::ifstream f("kulkim.bin");
    if (!f.is_open())
      return map{};
    map Result;
    std::string line;
    std::getline(f, line); // just fake key
    auto _decrypt = [](const std::string &to_decode) -> ball {
      auto encrypt = static_cast<std::size_t>(
          std::count(to_decode.begin(), to_decode.end(), '1'));
      if (to_decode.size() != 40 || encrypt > 7)
        return ball(COLOR::empty);
      return ball(static_cast<COLOR>(encrypt - 1));
    };
    std::getline(f, line);
    auto score = decrypt(line);
    std::getline(f, line);
    auto filled = decrypt(line);
    std::getline(f, line);

    std::array<ball, 3> next_three;

    for (std::size_t i = 0U; i < next_three.size(); ++i) {
      next_three[i] = _decrypt(line.substr(i * 40, 40));
    }

    std::array<std::array<ball, 9>, 9> grid;

    std::for_each(grid.begin(), grid.end(), [&line, &f, &_decrypt](auto &Coll) {
      std::getline(f, line);
      for (std::size_t row = 0U; row < Coll.size(); ++row) {
        Coll[row] = _decrypt(line.substr(row * 40, 40));
      }
    });

    Result.load_game(score, static_cast<uint8_t>(filled), next_three, grid);
    Result.set_update(true);

    if (Result.score_there())
      return map{};

    uint8_t fill_fix = 0;
    std::for_each(
        Result.get_grid().begin(), Result.get_grid().end(),
        [&fill_fix](const auto &Row) mutable {
          fill_fix += static_cast<uint8_t>(std::count_if(
              std::begin(Row), std::end(Row),
              [](const auto &Ball) -> bool { return Ball.has_value(); }));
        });
    if (fill_fix != filled)
      return map{};
    return Result;
  } catch (...) {
    return map{};
  }
}

void save_map(const map &Map) noexcept {
  std::ofstream f("kulkim.bin");
  f << (static_cast<std::size_t>(Map.get_score() * Map.filled()) << 1) << '\n';
  auto sc_crypt = crypt(Map.get_score()); // encrypt score
  auto fil_crypt = crypt(Map.filled());   // encrypt filled number
  f << sc_crypt << '\n' << fil_crypt << '\n';
  auto encrypt = [](std::size_t to_encode) {
    std::string crypt(40, '0');
    std::fill_n(crypt.begin(), to_encode + 1, '1');
    return crypt;
  };
  auto next_three = Map.get_next_three();
  std::for_each(next_three.begin(), next_three.end(), [&](const auto &Ball) {
    f << encrypt(static_cast<std::size_t>(Ball.enum_color()));
  });
  f << "\n";
  std::for_each(
      Map.get_grid().begin(), Map.get_grid().end(), [&](const auto &Row) {
        std::for_each(std::begin(Row), std::end(Row), [&](const auto &Ball) {
          f << encrypt(static_cast<size_t>(Ball.enum_color()));
        });
        f << "\n";
      });
}
