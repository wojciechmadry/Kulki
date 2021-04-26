//
// Created by Wojtek on 22.11.2020.
//

#ifndef KULKI_LOAD_HPP
#define KULKI_LOAD_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>
#include "crypt.hpp"
#include "../object/map.hpp"

// load font
sf::Font load_font(const std::string &path)
{
    sf::Font font;
    if ( !font.loadFromFile(path) )
        throw std::out_of_range("Cant load font");
    return font;
}

std::pair<uint32_t, uint32_t> load_resolution() noexcept
{
    namespace fs = std::filesystem;
    if ( !fs::exists("resolution.cfg") )
    {
        std::ofstream f("resolution.cfg");
        f << 1920 << '\n' << 1020;
        babel::FILE_SYS::close_file(f);
        return {1920u, 1020u};
    }
    auto lines = babel::FILE_SYS::load_txt_to_vector("resolution.cfg");
    if (lines.size() != 2)
    {
        std::ofstream f("resolution.cfg");
        f << 1920 << '\n' << 1020;
        babel::FILE_SYS::close_file(f);
        return {1920u, 1020u};
    }
    auto x = babel::ALGO::string_to<uint32_t>(lines[0]);
    auto y = babel::ALGO::string_to<uint32_t>(lines[1]);
    return {x, y};

}
uint32_t load_fps() noexcept
{
    namespace fs = std::filesystem;
    if ( !fs::exists("fps.cfg") )
    {
        std::ofstream f("fps.cfg");
        f << 30;
        babel::FILE_SYS::close_file(f);
        return 30u;
    }
    return babel::ALGO::string_to<uint32_t>(babel::FILE_SYS::load_txt("fps.cfg"));

}

// Check for crypted record in file
// If file doesn't exist
// or crypted is broken
// record set to 0
uint16_t check_for_record()
{
    namespace fs = std::filesystem;

    if ( !fs::exists("kulki.bin") )
    {
        std::ofstream f("kulki.bin");
        f << crypt(0);
        babel::FILE_SYS::close_file(f);
    }
    std::ifstream file("kulki.bin");
    if ( !file.is_open() )
        throw std::out_of_range("Cant open kulki.bin");
    uint16_t decoded = 0;
    try
    {
        std::string line;
        std::getline(file, line);
        decoded = decrypt(line);
        babel::FILE_SYS::close_file(file);
    }
    catch ( ... )
    {
        babel::FILE_SYS::close_file(file);
        std::ofstream f("kulki.bin");
        f << crypt(0);
        decoded = 0;
        babel::FILE_SYS::close_file(f);
    }

    return decoded;
}

// Save new record (crypt is very easy) to file
void save_record(uint16_t new_record)
{
    std::ofstream f("kulki.bin");
    if ( !( f.is_open() && f.good() ) )
        throw std::out_of_range("Cant open kulki.bin");
    f << crypt(new_record);
    babel::FILE_SYS::close_file(f);
}

map load_map() noexcept
{
    namespace fs = std::filesystem;
    try
    {
        if ( !fs::exists("kulkim.bin") )
            return map();
        std::ifstream f("kulkim.bin");
        if ( !f.is_open() )
            return map();
        map Result;
        std::string line;
        std::getline(f, line); // just fake key
        auto _decrypt = [](const std::string &to_decode) -> ball {
            size_t encrypt {0};
            for ( auto ch : to_decode )
                if ( ch == '1' )
                    ++encrypt;
            if ( to_decode.size() != 40 || encrypt > 7 )
                return ball(COLOR::empty);
            return ball(static_cast<COLOR>(encrypt - 1));
        };
        std::getline(f, line);
        auto score = decrypt(line);
        std::getline(f, line);
        auto filled = decrypt(line);
        std::getline(f, line);
        for ( uint32_t i = 0 ; i < 3 ; ++i )
            Result.next_three[i] = _decrypt(line.substr(i * 40, 40));
        for ( uint32_t i = 0 ; i < 9 ; ++i )
        {
            std::getline(f, line);
            for ( uint32_t j = 0 ; j < 9 ; ++j )
                Result.grid[i][j] = _decrypt(line.substr(j * 40, 40));
        }
        babel::FILE_SYS::close_file(f);
        Result.score = score;
        Result._filled = filled;
        Result.set_update(true);
        if ( Result.check_for_score() )
            return map();
        byte fill_fix = 0;
        for ( byte i = 0 ; i < 9 ; ++i )
            for ( byte j = 0 ; j < 9 ; ++j )
                if ( !Result.grid[i][j].is_empty() )
                    ++fill_fix;
        if ( fill_fix != filled )
            return map();
        return Result;
    }
    catch ( ... )
    {
        return map();
    }
}

void save_map(const map &Map) noexcept
{

    std::ofstream f("kulkim.bin");
    auto key = random_generator::generate<size_t>(100000, 100000000);
    f << key << '\n';
    auto sc_crypt = crypt(Map.get_score()); // encrypt score
    auto fil_crypt = crypt(Map.filled()); // encrypt filled number
    f << sc_crypt << '\n' << fil_crypt << '\n';
    auto encrypt = [](size_t to_encode) -> std::string {
        ++to_encode;
        std::string crypt(40, '0');
        while ( to_encode > 0 )
        {
            auto pos = random_generator::generate<byte>(0, 39);
            if ( crypt[pos] == '0' )
            {
                crypt[pos] = '1';
                --to_encode;
            }
        }
        return crypt;
    };
    auto next_three = Map.get_next_three();
    for ( auto Bal : next_three )
        f << encrypt(static_cast<size_t>(Bal.enum_color()));
    f << '\n';
    for ( byte i = 0 ; i < 9 ; ++i )
    {
        for ( byte j = 0 ; j < 9 ; ++j )
            f << encrypt(static_cast<size_t>(Map.at(i, j).enum_color()));
        f << '\n';
    }
    babel::FILE_SYS::close_file(f);
}

#endif //KULKI_LOAD_HPP
