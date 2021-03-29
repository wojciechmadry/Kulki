#ifndef BABEL_CHAR
#define BABEL_CHAR

#include "must_have.hpp"

namespace babel::CHAR {
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
            {}

            [[nodiscard]]const char *what() const noexcept override
            {
                return "CHAR IS NOT ALPHABETICAL !";
            }
        };

        class IS_NOT_NUMBER : public std::exception
        {
        public:
            IS_NOT_NUMBER() : std::exception()
            {}

            [[nodiscard]]const char *what() const noexcept override
            {
                return "CHAR IS NOT A NUMBER !";
            }
        };

    public:
        constexpr explicit ASCII_CHAR() noexcept: _member(0)
        {}

        constexpr explicit ASCII_CHAR(char _char) noexcept: _member(_char)
        {}

        constexpr ASCII_CHAR(const ASCII_CHAR &other) noexcept: _member(other._member) //NOLINT
        {}

        constexpr ASCII_CHAR &operator=(const ASCII_CHAR &other) //NOLINT
        {
            _member = other._member;
            return *this;
        }

        constexpr ASCII_CHAR &operator=(char _char)
        {
            _member = _char;
            return *this;
        }

        constexpr explicit operator bool() const
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
        constexpr char &get_by_ref() noexcept
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
        constexpr void set(char to_set) noexcept
        {
            _member = to_set;
        }

        /**
         * @brief Check if char storage number 0-9
         * */
        [[nodiscard]]constexpr bool is_number() const noexcept
        {
            return _member > 47 && _member < 58;
        }

        /**
         * @brief Check if char storage a-z or A-Z
         * */
        [[nodiscard]]constexpr bool is_alphabetical() const noexcept
        {
            return (_member > 64 && _member < 91) || (_member > 96 && _member < 123);
        }

        /**
        * @brief Check if char storage a-z
        * */
        [[nodiscard]]constexpr bool is_lower() const noexcept
        {
            return _member > 96 && _member < 123;
        }

        /**
        * @brief Check if char storage A-Z
        * */
        [[nodiscard]]constexpr bool is_upper() const noexcept
        {
            return _member > 64 && _member < 91;
        }

        /**
        * @brief Check if char is equal to ' '
        * */
        [[nodiscard]]constexpr bool is_space() const noexcept
        {
            return _member == 32;
        }

        /**
        * @brief If char is not alphabetical function throw in otherwise return upper letter
        * */
        [[nodiscard]]constexpr char to_upper() const
        {
            if (is_upper())
                return _member;
            if (is_lower())
                return static_cast<char>(_member - 32);
            throw IS_NOT_ALPHABETICAL();
        }

        /**
         * @brief If char is not alphabetical function throw in otherwise return lower letter
         * */
        [[nodiscard]] constexpr char to_lower() const
        {
            if (is_lower())
                return _member;
            if (is_upper())
                return static_cast<char>(_member + 32);
            throw IS_NOT_ALPHABETICAL();
        }

        /**
         * @brief If char is not a number(0-9) function throw in otherwise return number convert to int
         * @return Number 0-9
         * */
        [[nodiscard]]constexpr int to_int_number() const
        {
            if (is_number())
                return static_cast<int>(_member - '0');
            throw IS_NOT_NUMBER();
        }

        /**
         * @brief Set char to number 0-9
         * @param number Number 0-9
         * */
        constexpr void set_number(int number) noexcept
        {
            _member = static_cast<char>(number + 48);
        }

        constexpr ASCII_CHAR &operator--()
        {
            --_member;
            return *this;
        }

        constexpr ASCII_CHAR &operator++()
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