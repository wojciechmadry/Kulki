#if !defined(BABEL_WIN_CONV) & defined(_WIN32)
#define BABEL_WIN_CONV

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

#endif