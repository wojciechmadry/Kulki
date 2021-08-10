// Copyright [2021] <Wojtek>"
#if !defined(BABLIB_SYSTEM_LINUX_HPP_) & defined(linux)
#define BABLIB_SYSTEM_LINUX_HPP_

#include <utility>
#include <cstdint>
#include <vector>
#include <string>


namespace babel::LINUX::DISPLAY{
    /**
*  @brief  Return resolution of screen
 *  \Example_1 return {1920, 1080}
 *  \Example_2 return {1080, 720}
*  @return Pair of first ( width ) and second ( height)
*/
    [[nodiscard]] inline std::pair<std::size_t, std::size_t> get_screen_resolution() noexcept
    {
        std::pair<std::size_t, std::size_t> Resolution = {1280, 720};
        system("xdpyinfo | grep dimensions |  cut -d' ' -f7 > babel_temporary_file");
        std::fstream res_file("babel_temporary_file", std::ios::in | std::ios::binary);
        if ( res_file.good() && res_file.is_open() )
        {
            std::string line;
            std::getline(res_file, line);
            res_file.close();
            auto find_x = line.find('x');
            if ( find_x == std::string::npos )
                return Resolution;
            Resolution.first = std::stoull(line.substr(0, find_x));
            Resolution.second = std::stoull(line.substr(find_x + 1));
            system("rm babel_temporary_file");
        }
        return Resolution;
    }
}  // namespace babel::LINUX::DISPLAY

namespace babel::LINUX::SYSTEM{
    /**
*  @brief  Find all available disc
*  @return Return empty vector on linux
*/
    inline std::vector<std::string> all_discs() noexcept
    {
        return { };
    }
}  // namespace babel::LINUX::SYSTEM
#endif  // BABLIB_SYSTEM_LINUX_HPP_
