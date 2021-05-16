//
// Created by Wojtek on 22.11.2020.
//

#ifndef KULKI_CRYPT_HPP
#define KULKI_CRYPT_HPP
#include "../babel/babel.hpp"
#include "random_generator.hpp"

//Easy crypted function
std::string crypt(uint16_t number)
{

    std::string encrypted = {random_generator::generate<char>(65, 90)};
    auto snum = babel::ALGO::asType<std::string>(number);
    for(auto ch : snum)
    {
        encrypted += char(ch+49);
        encrypted += random_generator::generate<char>(65, 90);
    }
    return encrypted;
}

// If crypted file is corrupted function throw std::out_of_range
uint16_t decrypt(const std::string& cr)
{
    if(cr.size()%2 == 0)
        throw std::out_of_range("bad decrypt");
    std::string decrypt;
    for(size_t i = 0 ; i < cr.size() ; ++i)
    {
        if (i%2 == 0)
        {
            if (cr[i] < 65 || cr[i] > 90)
                throw std::out_of_range("bad decrypt");
        }
        else
        {
            decrypt += char(cr[i]-49);
        }
    }
    return babel::ALGO::asType<uint16_t>(decrypt);
}

#endif //KULKI_CRYPT_HPP
