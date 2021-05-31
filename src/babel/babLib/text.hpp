#ifndef BABEL_TEXT_HPP
#define BABEL_TEXT_HPP

#include "file_system.hpp"

namespace babel::TEXT{
    class text
    {

        std::string _str;
        std::array<std::vector<char *>, 256> _lett;

        template< typename T >
        void _set_text(T &&str) noexcept
        {
            _clear_vector();
            _str = std::forward<T>(str);
            std::for_each(std::begin(_str), std::end(_str), [this](char &CHAR) mutable {
                this->_lett[static_cast<uint8_t>(CHAR)].emplace_back(&CHAR);
            });
        }

        void _clear_vector() noexcept
        {
            std::for_each(std::begin(_lett), std::end(_lett), [](std::vector<char *> &Vec) { Vec.clear(); });
        }

    public:

        text() noexcept = default;

        /**
*  @brief  Copy string Str to string stored in class or load text from file
*  @param  const std::string& Str String to stored in class or filename
*  @param  isFilename if == true, then load text from file Str
*  @return No return
*/
        explicit text(const std::string &Str, const bool IsFilename = false) noexcept
        {
            if ( !IsFilename )
                _set_text(Str);
            else
                _set_text(babel::FILE_SYS::load_txt(Str));
        }

        /**
*  @brief  Move string Str to string stored in class or load text from file
*  @param  std::string&& Str String to stored in class or filename
*  @param  isFilename if == true, then load text from file Str
*  @return No return
*/
        explicit text(std::string &&Str, const bool IsFilename = false) noexcept
        {
            if ( !IsFilename )
                _set_text(std::move(Str));
            else
                _set_text(babel::FILE_SYS::load_txt(Str));
        }

        ~text() noexcept
        {
            clear();
        }


        /**
*  @brief  Copy string Str to string stored in class
*  @param  const std::string& Str String to stored in class
*  @return No return
*/
        void set_text(const std::string &Str) noexcept
        {
            _set_text(Str);
        }


        /**
*  @brief  Move string Str to string stored in class
*  @param  std::string&& Str String to stored in class
*  @return No return
*/
        void set_text(std::string &&Str) noexcept
        {
            _set_text(std::move(Str));
        }

        /**
*  @brief Load string from file
*  @param  filename File to load
*  @return No return
*/
        void load_from_file(const std::string &filename) noexcept
        {
            _set_text(babel::FILE_SYS::load_txt(filename));
        }

        /**
*  @brief Count a specific character
         *  \Example_1 str = "test" -> count('t') -> 2
*  @param  Char character to count
*  @return Numbers of character in stored string
*/
        [[nodiscard]] size_t count(const uint8_t Char) const noexcept
        {
            return _lett[static_cast<std::size_t>(Char)].size();
        }

        /**
*  @brief Clear string and vector in class
*  @return No return
*/
        void clear() noexcept
        {
            _clear_vector();
            _str.clear();
        }

        /**
*  @brief Find string in stored string
*  @param  to_find String to find in stored string
*  @return If string will be found then return pointer to first character in string in otherwise return nullptr
*/
        [[nodiscard]] const char *find(const std::string &to_find) const noexcept
        {
            if ( to_find.empty() )
                return nullptr;
            auto& LetterVector = _lett[static_cast<std::size_t>(static_cast<uint8_t>(to_find[0]))];
            char* ReturnValue {nullptr};
            std::any_of(LetterVector.begin(), LetterVector.end(),
            [&to_find, &ReturnValue](char* CharPtr) mutable -> bool
            {
                auto found = std::equal(CharPtr, CharPtr + to_find.size(), to_find.data(), to_find.data() + to_find.size());
                if (found)
                    ReturnValue = CharPtr;
                return found;
            });
            return ReturnValue;
        }

        /**
*  @brief Get string stored in class
*  @return Return const std::string stored in class
*/
        [[nodiscard]] const std::string &get_string() const noexcept
        {
            return _str;
        }
    };
}


#endif
