#include "crypt.hpp"
#include "BabelLib/babel.hpp"

std::string crypt(uint16_t number)
{
    babel::ALGO::MATH::random_generator rg;
    std::string encrypted = {rg.generate<char>(65, 90)};
    auto s_num = babel::ALGO::CAST::asType<std::string>(number);
    std::for_each(s_num.begin(), s_num.end(), [&encrypted, &rg](const char C) mutable {
        encrypted += static_cast<char>(C + 49);
        encrypted += rg.generate<char>(65, 90);
    });
    return encrypted;
}

uint16_t decrypt(const std::string &cr)
{
    if ( cr.size() % 2 == 0 )
        throw std::out_of_range("bad decrypt");
    std::string decrypt;
    for ( auto i : babel::ITERATOR::range<std::size_t, std::size_t>(0, cr.size()) )
    {
        if ( i % 2 == 0 )
        {
            if ( cr[i] < 65 || cr[i] > 90 )
                throw std::out_of_range("bad decrypt");
        } else
        {
            decrypt += static_cast<char>(cr[i] - 49);
        }
    }
    return babel::ALGO::CAST::asType<uint16_t>(decrypt);
}