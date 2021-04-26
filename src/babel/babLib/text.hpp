#ifndef BABEL_TEXT_HPP
#define BABEL_TEXT_HPP

#include "file_system.hpp"

namespace babel::TEXT{
    class text{

        std::string _str;
        std::array<std::vector<char*>, 256> _lett;

        template<typename T>
        void _set_text(T&& str) noexcept
        {
            _clear_vector();
            _str = std::forward<T>(str);
            for(  auto& CHAR : _str)
                _lett[static_cast<uint8_t>(CHAR)].emplace_back(&CHAR);
        }

        void _clear_vector() noexcept
        {
            std::for_each(std::begin(_lett), std::end(_lett), [](std::vector<char*>& Vec) { Vec.clear();});
        }
    public:

        text() noexcept = default;

        explicit text(const std::string& Str, const bool IsFilename = false) noexcept
        {
            if (!IsFilename)
                _set_text(Str);
            else
                _set_text(babel::FILE_SYS::load_txt(Str));
        }

        explicit text(std::string&& Str, const bool IsFilename = false) noexcept
        {
            if (!IsFilename)
                _set_text(std::move(Str));
            else
                _set_text(babel::FILE_SYS::load_txt(Str));
        }

        ~text() noexcept
        {
            clear();
        }

        void set_text(const std::string& Str) noexcept
        {
            _set_text(Str);
        }

        void set_text(std::string&& Str) noexcept
        {
            _set_text(std::move(Str));
        }

        void load_from_file(const std::string& filename) noexcept
        {
            _set_text(babel::FILE_SYS::load_txt(filename));
        }

        [[nodiscard]] size_t count(const char Char) const noexcept
        {
            return _lett[Char].size();
        }

        void clear() noexcept
        {
            _clear_vector();
            _str.clear();
        }

        [[nodiscard]] const char * find(const std::string& to_find) const noexcept
        {
            if(to_find.empty())
                return nullptr;

            for(size_t i = 0 ; i < _lett[to_find[0]].size() ; ++i)
            {
                size_t j;
                char* ptr = _lett[to_find[0]][i];
                bool same = true;
                for(j = 0 ; j < to_find.size() && *ptr != '\0'; ++j, ++ptr)
                    if (to_find[j] != *ptr)
                    {
                        same = false;
                        break;
                    }
                if (same && j == to_find.size())
                    return _lett[to_find[0]][i];

            }

            return nullptr;
        }

        [[nodiscard]] const std::string& get_string() const noexcept
        {
            return _str;
        }
    };
}


#endif
