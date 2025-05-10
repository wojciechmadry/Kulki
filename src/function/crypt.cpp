#include "crypt.hpp"
#include "randoms.hpp"
#include <algorithm>
#include <stdexcept>

std::string crypt(uint16_t number) {
  auto &e1 = rnd::get_rnd_eng().get();
  std::uniform_int_distribution<std::int8_t> uniform_dist(65, 90);
  std::string encrypted = {uniform_dist(e1)};
  auto s_num = std::to_string(number);
  std::for_each(s_num.begin(), s_num.end(), [&](const char C) {
    encrypted += static_cast<char>(C + 49);
    encrypted += uniform_dist(e1);
  });
  return encrypted;
}

uint16_t decrypt(const std::string &cr) {
  if (cr.size() % 2 == 0)
    throw std::out_of_range("bad decrypt");
  std::string decrypt;
  for (std::size_t i = 0U; i < cr.size(); ++i) {
    if (i % 2 == 0) {
      if (cr[i] < 65 || cr[i] > 90)
        throw std::out_of_range("bad decrypt");
    } else {
      decrypt += static_cast<char>(cr[i] - 49);
    }
  }
  return static_cast<std::uint16_t>(std::stoi(decrypt));
}
