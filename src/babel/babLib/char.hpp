#ifndef BABEL_CHAR
#define BABEL_CHAR

#include "must_have.hpp"

namespace babel::CHAR{
    class ASCII_CHAR
    {
        char _member;

        //FRIENDS
        friend constexpr bool operator==(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator==(const char &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator==(const ASCII_CHAR &lhs, const char &rhs);

        friend constexpr bool operator>(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator>(const char &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator>(const ASCII_CHAR &lhs, const char &rhs);

        friend constexpr bool operator>=(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator>=(const char &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator>=(const ASCII_CHAR &lhs, const char &rhs);

        friend constexpr bool operator<(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator<(const char &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator<(const ASCII_CHAR &lhs, const char &rhs);

        friend constexpr bool operator<=(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator<=(const char &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator<=(const ASCII_CHAR &lhs, const char &rhs);

        friend constexpr bool operator!=(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator!=(const char &lhs, const ASCII_CHAR &rhs);

        friend constexpr bool operator!=(const ASCII_CHAR &lhs, const char &rhs);

        friend std::istream &operator>>(std::istream &is, ASCII_CHAR &_asci);

        friend std::ostream &operator<<(std::ostream &os, const ASCII_CHAR &_asci);

        //END OF FRIEND
        class IS_NOT_ALPHABETICAL : public std::exception
        {
        public:
            IS_NOT_ALPHABETICAL() : std::exception()
            { }

            [[nodiscard]]const char *what() const noexcept override
            {
                return "CHAR IS NOT ALPHABETICAL !";
            }
        };

        class IS_NOT_NUMBER : public std::exception
        {
        public:
            IS_NOT_NUMBER() : std::exception()
            { }

            [[nodiscard]]const char *what() const noexcept override
            {
                return "CHAR IS NOT A NUMBER !";
            }
        };

    public:
        constexpr explicit ASCII_CHAR() noexcept: _member(0)
        { }

        constexpr explicit ASCII_CHAR(char _char) noexcept: _member(_char)
        { }

        constexpr ASCII_CHAR(const ASCII_CHAR &other) noexcept: _member(other._member) //NOLINT
        { }

        constexpr ASCII_CHAR &operator=(const ASCII_CHAR &other) noexcept //NOLINT
        {
            _member = other._member;
            return *this;
        }

        constexpr ASCII_CHAR &operator=(char _char) noexcept
        {
            _member = _char;
            return *this;
        }

        constexpr explicit operator bool() const noexcept
        {
            return static_cast<bool>(_member);
        }

        /**
         *  @return Return copy of stored char
         */
        [[nodiscard]]constexpr char get() const noexcept
        {
            return _member;
        }

        /**
         *  @return Return by reference stored char
         */
        [[nodiscard]] constexpr char &get_by_ref() noexcept
        {
            return _member;
        }

        /**
         *  @return Return by const reference stored char
         */
        [[nodiscard]]constexpr const char &get_by_ref() const noexcept
        {
            return _member;
        }

        /**
         * @brief Set stored char to param
         * @param to_set New char
         * */
        constexpr void set(const char to_set) noexcept
        {
            _member = to_set;
        }

        /**
         * @brief Check if char storage number 0-9
         * \Example_1 '9' -> ture
         * \Example_2 '3' -> ture
         * \Example_3 'c' -> false
         * \Example_4  9 -> false
         * */
        [[nodiscard]] constexpr bool is_number() const noexcept
        {
            return _member > 47 && _member < 58;
        }

        /**
         * @brief Check if char storage a-z or A-Z
         * \Example_1 'A' -> ture
         * \Example_2 'B' -> ture
         * \Example_3 'c' -> true
         * \Example_4 '5' -> false
         * */
        [[nodiscard]] constexpr bool is_alphabetical() const noexcept
        {
            return ( _member > 64 && _member < 91 ) || ( _member > 96 && _member < 123 );
        }

        /**
        * @brief Check if char storage a-z
         * \Example_1 'A' -> false
         * \Example_2 'B' -> false
         * \Example_3 'c' -> true
         * \Example_4 '5' -> false
        * */
        [[nodiscard]] constexpr bool is_lower() const noexcept
        {
            return _member > 96 && _member < 123;
        }

        /**
        * @brief Check if char storage A-Z
         * \Example_1 'A' -> ture
         * \Example_2 'B' -> ture
         * \Example_3 'c' -> false
         * \Example_4 '5' -> false
        * */
        [[nodiscard]] constexpr bool is_upper() const noexcept
        {
            return _member > 64 && _member < 91;
        }

        /**
        * @brief Check if char is equal to ' '
         * \Example_1 ' ' -> true
         * \Example_2 'c' -> false
         * @return If _member == ' ' return true
        * */
        [[nodiscard]]constexpr bool is_space() const noexcept
        {
            return _member == 32;
        }

        /**
        * @brief If char is not alphabetical function throw in otherwise return upper letter
         * \Example_1 'a' -> 'A'
         * \Example_2 'b' -> 'B'
         * \Example_2 '5' -> throw IS_NOT_ALPHABETICAL
          @return upper letter
        * */
        [[nodiscard]]constexpr char to_upper() const
        {
            if ( is_upper() )
                return _member;
            if ( is_lower() )
                return static_cast<char>(_member - 32);
            throw IS_NOT_ALPHABETICAL();
        }

        /**
         * @brief If char is not alphabetical function throw in otherwise return lower letter
         * \Example_1 'A' -> 'a'
         * \Example_2 'B' -> 'b'
         * \Example_2 '5' -> throw IS_NOT_ALPHABETICAL
         * @return lower letter
         * */
        [[nodiscard]] constexpr char to_lower() const
        {
            if ( is_lower() )
                return _member;
            if ( is_upper() )
                return static_cast<char>(_member + 32);
            throw IS_NOT_ALPHABETICAL();
        }

        /**
         * @brief If char is not a number(0-9) function throw in otherwise return number convert to int
         * \Example_1 stored element is '5' -> return 5
         * \Example_2 stored element is '3' -> return 3
         * \Example_3 stored element is 'a' -> throw IS_NOT_NUMBER
         * @return Number 0-9
         * */
        [[nodiscard]]constexpr int to_int_number() const
        {
            if ( is_number() )
                return static_cast<int>(_member - '0');
            throw IS_NOT_NUMBER();
        }

        /**
         * @brief Set char to number 0-9
         * \Example_1 set_number(0) -> stored number is '0'
         * \Example_2 set_number(5) -> stored number is '5'
         * @param number Number 0-9
         * */
        constexpr void set_number(const int number) noexcept
        {
            _member = static_cast<char>(number + 48);
        }

        constexpr ASCII_CHAR &operator--() noexcept
        {
            --_member;
            return *this;
        }

        constexpr ASCII_CHAR &operator++() noexcept
        {
            ++_member;
            return *this;
        }
    };


//OPERATORS
    std::ostream &operator<<(std::ostream &os, const ASCII_CHAR &_asci)
    {
        return os << _asci._member;
    }

    std::istream &operator>>(std::istream &is, ASCII_CHAR &_asci)
    {
        is >> _asci._member;
        return is;
    }

    constexpr bool operator==(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs)
    {
        return lhs._member == rhs._member;
    }

    constexpr bool operator==(const ASCII_CHAR &lhs, const char &rhs)
    {
        return lhs._member == rhs;
    }

    constexpr bool operator==(const char &lhs, const ASCII_CHAR &rhs)
    {
        return lhs == rhs._member;
    }

    constexpr bool operator>(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs)
    {
        return lhs._member > rhs._member;
    }

    constexpr bool operator>(const char &lhs, const ASCII_CHAR &rhs)
    {
        return lhs > rhs._member;
    }

    constexpr bool operator>(const ASCII_CHAR &lhs, const char &rhs)
    {
        return lhs._member > rhs;
    }

    constexpr bool operator>=(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs)
    {
        return lhs._member >= rhs._member;
    }

    constexpr bool operator>=(const char &lhs, const ASCII_CHAR &rhs)
    {
        return lhs >= rhs._member;
    }

    constexpr bool operator>=(const ASCII_CHAR &lhs, const char &rhs)
    {
        return lhs._member >= rhs;
    }

    constexpr bool operator<(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs)
    {
        return lhs._member < rhs._member;
    }

    constexpr bool operator<(const char &lhs, const ASCII_CHAR &rhs)
    {
        return lhs < rhs._member;
    }

    constexpr bool operator<(const ASCII_CHAR &lhs, const char &rhs)
    {
        return lhs._member < rhs;
    }

    constexpr bool operator<=(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs)
    {
        return lhs._member <= rhs._member;
    }

    constexpr bool operator<=(const char &lhs, const ASCII_CHAR &rhs)
    {
        return lhs <= rhs._member;
    }

    constexpr bool operator<=(const ASCII_CHAR &lhs, const char &rhs)
    {
        return lhs._member <= rhs;
    }

    constexpr bool operator!=(const ASCII_CHAR &lhs, const ASCII_CHAR &rhs)
    {
        return lhs._member != rhs._member;
    }

    constexpr bool operator!=(const char &lhs, const ASCII_CHAR &rhs)
    {
        return lhs != rhs._member;
    }

    constexpr bool operator!=(const ASCII_CHAR &lhs, const char &rhs)
    {
        return lhs._member != rhs;
    }


}


#endif