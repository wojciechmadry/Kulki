#ifndef KULKI_RANDOM_HPP
#define KULKI_RANDOM_HPP

#include "BabelLib/babel.hpp"

class randomizer
{

public:
    static babel::ALGO::MATH::random_generator& get() noexcept;
};

#endif  // KULKI_RANDOM_HPP