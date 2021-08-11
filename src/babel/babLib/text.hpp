// Copyright [2021] <Wojtek>"
#ifndef BABLIB_TEXT_HPP_
#define BABLIB_TEXT_HPP_

#include "file_system.hpp"

namespace babel::TEXT{
    class text
    {
        std::string m_str;
        std::array<std::vector<char *>, 256> m_lett;

        template< typename T >
        void _set_text(T &&str) noexcept
        {
            _clear_vector();
            m_str = std::forward<T>(str);
            std::for_each(std::begin(m_str), std::end(m_str), [this](char &_char) mutable {
                this->m_lett[static_cast<uint8_t>(_char)].emplace_back(&_char);
            });
        }

        void _clear_vector() noexcept
        {
            std::for_each(std::begin(m_lett), std::end(m_lett), [](std::vector<char *> &Vec) { Vec.clear(); });
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
            return m_lett[static_cast<std::size_t>(Char)].size();
        }

        /**
*  @brief Clear string and vector in class
*  @return No return
*/
        void clear() noexcept
        {
            _clear_vector();
            m_str.clear();
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
            auto& LetterVector = m_lett[static_cast<std::size_t>(static_cast<uint8_t>(to_find[0]))];
            char* ReturnValue {nullptr};
            auto isFound = std::any_of(LetterVector.begin(), LetterVector.end(),
            [&to_find, &ReturnValue](char* CharPtr) mutable -> bool
            {
                auto found = std::equal(CharPtr, CharPtr + to_find.size(), to_find.data(), to_find.data() + to_find.size());
                if (found)
                    ReturnValue = CharPtr;
                return found;
            });
            return isFound ? ReturnValue : nullptr;
        }

        /**
*  @brief Get string stored in class
*  @return Return const std::string stored in class
*/
        [[nodiscard]] const std::string &getm_string() const noexcept
        {
            return m_str;
        }
    };
}  // namespace babel::TEXT


#endif  // BABLIB_TEXT_HPP_
