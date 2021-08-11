// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ALGORITHM_STRING_HPP_
#define BABLIB_ALGORITHM_STRING_HPP_

#include <string>

namespace babel::ALGO::STRING{
    /**
  *  @brief  Pop \n from last elements
  *  \Example_1 "test\n\n" ->  "test"
  *  \Example_2  "test\n" -> "test"
  *  \Example_2  "test" -> "test"
  *  \Example_3  "te \n st" -> "te \n st"
  *  @param  String to change
  *  @return String without \n at the end
  */
    inline void pop_newline_from_string(std::string &Str) noexcept
    {
        while ( !Str.empty() && Str[Str.size() - 1] == '\n' )
            Str.pop_back();
    }

    /**
*  @brief  Take numbers from string
*  \Example_1 "test52" ->  "52"
*  \Example_2  "5t8c2" -> "582"
*  \Example_3  "25ttt" -> "25"
*  \Example_4  "" -> "0"
*  @param  String to filter
*  @return All numbers form string
*/
    [[nodiscard]] inline std::string get_only_numbers(const std::string &Str) noexcept
    {
        if ( Str.empty() )
            return "0";
        std::string Res;
        std::for_each(Str.begin(), Str.end(),
                      [&Res](char CHAR) mutable {
                          if ( CHAR >= '0' && CHAR <= '9' )
                              Res.push_back(CHAR);
                      });
        return Res.empty() ? "0" : Res;
    }

    [[nodiscard]] inline std::string str_to_upper(const std::string &Str) noexcept
    {
        std::string Res = Str;
        std::for_each(Res.begin(), Res.end(), [](char &CHAR) {
            CHAR = static_cast<char>(std::toupper(CHAR));
        });
        return Res;
    }

    [[nodiscard]] inline std::string str_to_lower(const std::string &Str) noexcept
    {
        std::string Res = Str;
        std::for_each(Res.begin(), Res.end(), [](char &CHAR) {
            CHAR = static_cast<char>(std::tolower(CHAR));
        });
        return Res;
    }
}  // namespace babel::ALGO::STRING

#endif  // BABLIB_ALGORITHM_STRING_HPP_
