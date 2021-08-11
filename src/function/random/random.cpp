#include "random.hpp"

babel::ALGO::MATH::random_generator& randomizer::get() noexcept
{
    static babel::ALGO::MATH::random_generator m_rg;
    return m_rg;
}