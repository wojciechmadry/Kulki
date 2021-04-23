#ifndef BABEL_TEXT_HPP
#define BABEL_TEXT_HPP

#include "file_system.hpp"

namespace babel::TEXT{
    class text{

        std::string _str;
        std::array<std::vector<char*>, 256> _lett;

        template<typename T>
        void _add_text(T&& str) noexcept
        {
            _str = std::forward<T>(str);
            for(  auto& CHAR : _str)
                _lett[static_cast<uint8_t>(CHAR)].emplace_back(&CHAR);
        }

    public:

        text() noexcept = default;

        explicit text(const std::string& Str, const bool IsFilename = false) noexcept
        {
            if (!IsFilename)
                _add_text(Str);
            else
                _add_text(babel::FILE_SYS::load_txt(Str));
        }

        explicit text(std::string&& Str, const bool IsFilename = false) noexcept
        {
            if (!IsFilename)
                _add_text(std::move(Str));
            else
                _add_text(babel::FILE_SYS::load_txt(Str));
        }

        ~text() noexcept
        {
            clear();
        }

        void clear() noexcept
        {
            for(auto& Vec : _lett)
                Vec.clear();
            _str.clear();
        }

        [[nodiscard]] const std::string& get_string() const noexcept
        {
            return _str;
        }
    };
}


#endif
