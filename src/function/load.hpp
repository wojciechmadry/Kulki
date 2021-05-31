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
    const std::string FileName = "resolution.cfg";
    auto load_default_settings = [&FileName]() -> std::pair<uint32_t, uint32_t> {
        std::pair<uint32_t, uint32_t> res = babel::WINDOWS::DISPLAY::get_screen_resolution();
        std::ofstream f(FileName);
        f << res.first << '\n' << res.second;
        babel::FILE_SYS::close_file(f);
        return {res.first, res.second};

    };
    namespace fs = std::filesystem;
    if ( !fs::exists(FileName) )
    {
        return load_default_settings();
    }
    auto lines = babel::FILE_SYS::load_txt_to_vector(FileName);
    std::for_each(lines.begin(), lines.end(), babel::ALGO::STRING::get_only_numbers);
    if ( lines.size() != 2 || lines[0].size() > 4 || lines[1].size() > 4 || lines[0].size() <= 2 ||
         lines[1].size() <= 2 )
    {
        return load_default_settings();
    }
    return {babel::ALGO::CAST::asType<uint32_t>(lines[0]), babel::ALGO::CAST::asType<uint32_t>(lines[1])};

}

uint32_t load_fps() noexcept
{
    const std::string FileName = "fps.cfg";
    const constexpr uint32_t DefaultFPS = 30u;
    auto LoadDefault = [&FileName]() -> uint32_t {
        std::ofstream f(FileName);
        f << DefaultFPS;
        babel::FILE_SYS::close_file(f);
        return DefaultFPS;
    };
    namespace fs = std::filesystem;
    if ( !fs::exists(FileName) )
    {
        return LoadDefault();
    }
    auto FPS = babel::FILE_SYS::load_txt(FileName);


    auto uFPS = babel::ALGO::CAST::asType<uint32_t>(babel::ALGO::STRING::get_only_numbers(FPS));

    uFPS = babel::ALGO::MATH::min(uFPS, 10u * DefaultFPS);
    uFPS = babel::ALGO::MATH::max(uFPS, DefaultFPS);

    return uFPS;

}

// Check for crypted record in file
// If file doesn't exist
// or crypted is broken
// record set to 0
uint16_t check_for_record()
{
    namespace fs = std::filesystem;
    const std::string FileName = "kulki.bin";

    if ( !fs::exists(FileName) )
    {
        std::ofstream f(FileName);
        f << crypt(0);
        babel::FILE_SYS::close_file(f);
    }
    std::ifstream file(FileName);
    if ( !file.is_open() )
        throw std::out_of_range("Cant open " + FileName);
    uint16_t decoded;
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
        std::ofstream f(FileName);
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
            auto encrypt = static_cast<std::size_t>(std::count(to_decode.begin(), to_decode.end(), '1'));
            if ( to_decode.size() != 40 || encrypt > 7 )
                return ball(COLOR::empty);
            return ball(static_cast<COLOR>(encrypt - 1));
        };
        std::getline(f, line);
        auto score = decrypt(line);
        std::getline(f, line);
        auto filled = decrypt(line);
        std::getline(f, line);
        //TODO need to implement enumerate iterator in babLib
        std::size_t i {0};
        std::for_each(Result.next_three.begin(), Result.next_three.end(),
                      [&i, &_decrypt, &line](auto &Ball) mutable {
                          Ball = _decrypt(line.substr(( i++ ) * 40, 40));
                      });

        std::for_each(Result.grid.begin(), Result.grid.end(),
                      [&line, &f, &_decrypt](auto &Row) mutable {
                          std::getline(f, line);
                          std::size_t j {0};
                          std::for_each(std::begin(Row), std::end(Row),
                                        [&j, &line, &_decrypt](auto &Ball) mutable {
                                            Ball = _decrypt(line.substr(( j++ ) * 40, 40));
                                        });
                      });

        babel::FILE_SYS::close_file(f);
        Result.score = score;
        Result._filled = static_cast<byte>(filled);
        Result.set_update(true);
        if ( Result.check_for_score() )
            return map();
        byte fill_fix = 0;
        std::for_each(Result.grid.begin(), Result.grid.end(),
                      [&fill_fix](const auto &Row) mutable {
                          fill_fix += static_cast<byte>(std::count_if(std::begin(Row), std::end(Row),
                                                                      [](const auto &Ball) -> bool {
                                                                          return Ball.has_value();
                                                                      }));
                      });
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
        std::string crypt(40, '0');
        std::fill_n(crypt.begin(), to_encode + 1, '1');
        random_generator::random_shuffle(crypt);
        return crypt;
    };
    auto next_three = Map.get_next_three();
    std::for_each(next_three.begin(), next_three.end(),
                  [&f, &encrypt](const auto &Ball) mutable {
                      f << encrypt(static_cast<size_t>(Ball.enum_color()));;
                  });
    f << '\n';
    //TODO Add back inserter iterator to insert to file in babLib
    std::for_each(Map.get_grid().begin(), Map.get_grid().end(),
                  [&f, &encrypt](const auto &Row) mutable {
                      std::for_each(std::begin(Row), std::end(Row),
                                    [&f, &encrypt](const auto &Ball) mutable {
                                        f << encrypt(static_cast<size_t>(Ball.enum_color()));
                                    });
                      f << '\n';
                  });
    babel::FILE_SYS::close_file(f);
}


[[nodiscard]] std::string generate_window_name(const double Version) noexcept
{
    std::string title = "Kulki v.";
    title = title + std::to_string(Version);
    while ( title[title.size() - 1] == '0' )
        title.pop_back();
    return title;
}

#endif //KULKI_LOAD_HPP
