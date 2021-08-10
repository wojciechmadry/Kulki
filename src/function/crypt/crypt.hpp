//
// Created by Wojtek on 22.11.2020.
//

#ifndef KULKI_CRYPT_HPP
#define KULKI_CRYPT_HPP

#include <string>
#include <cstdint>

//Easy crypted function
std::string crypt(uint16_t number);


// If crypted file is corrupted function throw std::out_of_range
uint16_t decrypt(const std::string& cr);

#endif //KULKI_CRYPT_HPP
