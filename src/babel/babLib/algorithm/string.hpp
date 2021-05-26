#ifndef BABEL_ALGO_STRING
#define BABEL_ALGO_STRING

#include "../must_have.hpp"

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
    void pop_newline_from_string(std::string &Str) noexcept
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
    [[nodiscard]] std::string get_only_numbers(const std::string &Str) noexcept
    {
        if ( Str.empty() )
            return "0";
        std::string Res;
        for ( const auto Element : Str )
        {
            if ( Element >= '0' && Element <= '9' )
                Res.push_back(Element);
        }
        return Res.empty() ? "0" : Res;
    }

    [[nodiscard]] std::string str_to_upper(const std::string &Str) noexcept
    {
        std::string Res = Str;
        for ( auto &CHAR : Res )
            CHAR = static_cast<std::decay_t<decltype(CHAR)>>(std::toupper(CHAR));
        return Res;
    }

    [[nodiscard]] std::string str_to_lower(const std::string &Str) noexcept
    {
        std::string Res = Str;
        for ( auto &CHAR : Res )
            CHAR = static_cast<std::decay_t<decltype(CHAR)>>(std::tolower(CHAR));
        return Res;
    }
}

#endif