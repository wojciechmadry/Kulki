#include "randoms.hpp"

namespace rnd {
std::reference_wrapper<std::random_device> get_rnd_device() {
  static std::random_device rd{};
  return rd;
}

std::reference_wrapper<std::default_random_engine> get_rnd_eng() {
  auto &rd = get_rnd_device().get();
  static std::default_random_engine dre(rd());
  return dre;
}
} // namespace rnd
