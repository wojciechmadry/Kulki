#if !defined(BABEL_WINDOWS) & defined(_WIN32)
#define BABEL_WINDOWS

#include "../must_have.hpp"


namespace babel::WINDOWS::CONVERSION {

    [[nodiscard]] auto str_to_lpcwstr(const std::string &to_conv) noexcept
    {
        class LCPWSTR_HOLDER
        {
            std::wstring ws;
        public:
            LCPWSTR_HOLDER() = delete;
            explicit LCPWSTR_HOLDER(const std::string &str) noexcept: ws(str.begin(), str.end())
            {}

            ~LCPWSTR_HOLDER() = default;

            [[nodiscard]] LPCWSTR get_LPCWSTR() noexcept
            {
                return ws.c_str();
            }

            [[nodiscard]] LPCWSTR get_LPCWSTR() const noexcept
            {
                return ws.c_str();
            }

            [[nodiscard]] std::wstring &get_wstring() noexcept
            {
                return ws;
            }

            [[nodiscard]] const std::wstring &get_wstring() const noexcept
            {
                return ws;
            }
        };

        return LCPWSTR_HOLDER(to_conv);
    }

}

namespace babel::WINDOWS::DISPLAY
{
    /**
*  @brief  Return resolution of screen
 *  \Example_1 return {1920, 1080}
 *  \Example_2 return {1080, 720}
*  @return Pair of first ( width ) and second ( height)
*/
    [[nodiscard]] std::pair<std::size_t, std::size_t> get_screen_resolution() noexcept
    {
        RECT rect;
        GetClientRect(GetDesktopWindow(), &rect);
        return {static_cast<std::size_t>(rect.right - rect.left), static_cast<std::size_t>(rect.bottom - rect.top)};
    }
}

namespace babel::WINDOWS::SYSTEM{
    /**
*  @brief  Find all avaliable disc
*  @return Vector of discs ex.: "C:/", "D:/" etc.
*/
    std::vector<std::string> all_discs() noexcept
    {
        std::vector<std::string> Discs;
        for ( char alph = 'A' ; alph <= 'Z' ; ++alph )
        {
            std::string disc;
            disc = alph;
            disc += ":/";
            if ( babel::FILE_SYS::folder_exist(disc) )
                Discs.emplace_back(std::move(disc));
        }
        return Discs;
    }
}
#endif