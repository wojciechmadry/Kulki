// Copyright [2021] <Wojtek>"
#if !defined(BABLIB_SYSTEM_WINDOWS_HPP_) & defined(_WIN32)
#define BABLIB_SYSTEM_WINDOWS_HPP_

#include <windows.h>


namespace babel::WINDOWS::CONVERSION {

    [[nodiscard]] auto str_to_lpcwstr(const std::string &to_conv) noexcept
    {
        class LCPWSTR_HOLDER
        {
            std::wstring m_ws;
        public:
            LCPWSTR_HOLDER() = delete;
            explicit LCPWSTR_HOLDER(const std::string &str) noexcept: m_ws(str.begin(), str.end())
            {}

            ~LCPWSTR_HOLDER() = default;

            [[nodiscard]] LPCWSTR get_LPCWSTR() noexcept
            {
                return m_ws.c_str();
            }

            [[nodiscard]] LPCWSTR get_LPCWSTR() const noexcept
            {
                return m_ws.c_str();
            }

            [[nodiscard]] std::wstring &get_wstring() noexcept
            {
                return m_ws;
            }

            [[nodiscard]] const std::wstring &get_wstring() const noexcept
            {
                return m_ws;
            }
        };

        return LCPWSTR_HOLDER(to_conv);
    }

}  // namespace babel::WINDOWS::CONVERSION

namespace babel::WINDOWS::DISPLAY
{
    /**
*  @brief  Return resolution of screen
 *  \Example_1 return {1920, 1080}
 *  \Example_2 return {1080, 720}
*  @return Pair of first ( width ) and second ( height)
*/
    [[nodiscard]] inline std::pair<std::size_t, std::size_t> get_screen_resolution() noexcept
    {
        RECT rect;
        GetClientRect(GetDesktopWindow(), &rect);
        return {static_cast<std::size_t>(rect.right - rect.left), static_cast<std::size_t>(rect.bottom - rect.top)};
    }
}

namespace babel::WINDOWS::SYSTEM{
    /**
*  @brief  Find all available disc
*  @return Vector of discs ex.: "C:/", "D:/" etc.
*/
    inline std::vector<std::string> all_discs() noexcept
    {
        std::vector<std::string> Discs;
        for ( char letter = 'A' ; letter <= 'Z' ; ++letter )
        {
            std::string disc;
            disc = letter;
            disc += ":/";
            if ( babel::FILE_SYS::folder_exist(disc) )
                Discs.emplace_back(std::move(disc));
        }
        return Discs;
    }
}  // namespace babel::WINDOWS::DISPLAY
#endif  // BABLIB_SYSTEM_WINDOWS_HPP_
