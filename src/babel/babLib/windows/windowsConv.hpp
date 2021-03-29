#ifndef BABEL_WIN_CONV
#define BABEL_WIN_CONV

#include "../must_have.hpp"


namespace babel::WINDOWS::CONVERSION {

    auto str_to_lpcwstr(const std::string &to_conv)
    {
        class LCPWSTR_HOLDER
        {
            std::wstring ws;
        public:
            explicit LCPWSTR_HOLDER(const std::string &str) noexcept: ws(str.begin(), str.end())
            {}

            ~LCPWSTR_HOLDER() = default;

            LPCWSTR get_LPCWSTR() noexcept
            {
                return ws.c_str();
            }

            std::wstring &get_wstring() noexcept
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