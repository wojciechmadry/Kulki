//
// Created by Wojtek on 22.11.2020.
//

#ifndef KULKI_LOAD_HPP
#define KULKI_LOAD_HPP

#include "map.hpp"
#include <SFML/Graphics/Font.hpp>
#include <cstdint>
#include <string>

// load font
sf::Font load_font(const std::string &path);

uint32_t load_fps() noexcept;

// Check for encrypt record in file
// If file doesn't exist
// or encryption is broken
// record set to 0
uint16_t check_for_record();

// Save new record (crypt is very easy) to file
void save_record(uint16_t new_record);

map load_map() noexcept;

void save_map(const map &Map) noexcept;

#endif // KULKI_LOAD_HPP
