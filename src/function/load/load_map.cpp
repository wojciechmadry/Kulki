#include "load.hpp"
#include "BabelLib/babel.hpp"
#include "function/crypt/crypt.hpp"

map load_map() noexcept
{
    namespace fs = std::filesystem;
    try
    {
        if ( !fs::exists("kulkim.bin") )
            return map{};
        std::ifstream f("kulkim.bin");
        if ( !f.is_open() )
            return map{};
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

        std::array<ball, 3> next_three;

        babel::ITERATOR::enumerator NextThreeEnum(next_three);
        std::for_each(NextThreeEnum.begin(), NextThreeEnum.end(),
                      [&_decrypt, &line](auto En_Ball) mutable {
                          En_Ball.second() = _decrypt(line.substr(static_cast<std::size_t>(En_Ball.first()) * 40, 40));
                      });

        std::array<std::array<ball, 9>, 9> grid;

        std::for_each(grid.begin(), grid.end(),
                      [&line, &f, &_decrypt](auto &Row) mutable {
                          std::getline(f, line);
                          babel::ITERATOR::enumerator RowEnum(Row);
                          std::for_each(RowEnum.begin(), RowEnum.end(),
                                        [&line, &_decrypt](auto Ball) mutable {
                                            Ball.second() = _decrypt(
                                                    line.substr(static_cast<std::size_t>(Ball.first()) * 40, 40));
                                        });
                      });

        babel::FILE_SYS::close_file(f);
        Result.load_game(score, static_cast<uint8_t>(filled), next_three, grid);
        Result.set_update(true);

        if ( Result.score_there() )
            return map { };

        uint8_t fill_fix = 0;
        std::for_each(Result.get_grid().begin(), Result.get_grid().end(),
                      [&fill_fix](const auto &Row) mutable {
                          fill_fix += static_cast<uint8_t>(std::count_if(std::begin(Row), std::end(Row),
                                                                         [](const auto &Ball) -> bool {
                                                                             return Ball.has_value();
                                                                         }));
                      });
        if ( fill_fix != filled )
            return map{};
        return Result;
    }
    catch ( ... )
    {
        return map{};
    }
}

void save_map(const map &Map) noexcept
{
    babel::ALGO::MATH::random_generator rg;
    std::ofstream f("kulkim.bin");
    auto key = rg.generate<size_t>(100000, 100000000);
    f << key << '\n';
    auto sc_crypt = crypt(Map.get_score()); // encrypt score
    auto fil_crypt = crypt(Map.filled()); // encrypt filled number
    f << sc_crypt << '\n' << fil_crypt << '\n';
    auto encrypt = [&rg](std::size_t to_encode) mutable -> std::string {
        std::string crypt(40, '0');
        std::fill_n(crypt.begin(), to_encode + 1, '1');
        rg.random_shuffle(crypt);
        return crypt;
    };
    auto next_three = Map.get_next_three();
    auto back_inserter_file = babel::ITERATOR::writer(f);
    std::transform(next_three.begin(), next_three.end(),
                   back_inserter_file.back_inserter(false),
                   [&encrypt](const auto &Ball) {
                       return encrypt(static_cast<std::size_t>(Ball.enum_color()));
                   });
    back_inserter_file.push_back("\n");
    std::for_each(Map.get_grid().begin(), Map.get_grid().end(),
                  [&back_inserter_file, &encrypt](const auto &Row) mutable {
                      std::transform(std::begin(Row), std::end(Row), back_inserter_file.back_inserter(false),
                                     [&encrypt](const auto &Ball) {
                                         return encrypt(static_cast<size_t>(Ball.enum_color()));
                                     });
                      back_inserter_file.push_back("\n");
                  });
    back_inserter_file.close();
}