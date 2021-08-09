//
// Created by Wojtek on 22.11.2020.
//

#ifndef KULKI_CRYPT_HPP
#define KULKI_CRYPT_HPP
#include "babel.hpp"

//Easy crypted function
std::string crypt(uint16_t number)
{

    std::string encrypted = {babel::ALGO::MATH::random_generator::generate<char>(65, 90)};
    auto snum = babel::ALGO::CAST::asType<std::string>(number);
    std::for_each(snum.begin(), snum.end(),[&encrypted](const char C) mutable
    {
        encrypted += static_cast<char>(C+49);
        encrypted += babel::ALGO::MATH::random_generator::generate<char>(65, 90);
    });
    return encrypted;
}

// If crypted file is corrupted function throw std::out_of_range
uint16_t decrypt(const std::string& cr)
{
    if(cr.size()%2 == 0)
        throw std::out_of_range("bad decrypt");
    std::string decrypt;
    for(auto i : babel::ITERATOR::range<std::size_t>(0, cr.size()))
    {
        if (i%2 == 0)
        {
            if (cr[i] < 65 || cr[i] > 90)
                throw std::out_of_range("bad decrypt");
        }
        else
        {
            decrypt += static_cast<char>(cr[i]-49);
        }
    }
    return babel::ALGO::CAST::asType<uint16_t>(decrypt);
}

#endif //KULKI_CRYPT_HPP
