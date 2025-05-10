#ifndef KULKI_RANDOMS_HPP
#define KULKI_RANDOMS_HPP

#include <functional>
#include <random>

namespace rnd {

std::reference_wrapper<std::random_device> get_rnd_device();

std::reference_wrapper<std::default_random_engine> get_rnd_eng();

} // namespace rnd

#endif // KULKI_RANDOMS_HPP
