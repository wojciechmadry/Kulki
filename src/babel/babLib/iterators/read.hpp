// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ITERATORS_READ_HPP_
#define BABLIB_ITERATORS_READ_HPP_

#include <fstream>

namespace babel::ITERATOR{

    class reader
    {
        bool m_end_line {true}; // it false when no lines in file left
        std::ifstream *m_if {nullptr};
        std::string m_line; // line read

        class Iterator
        {
            bool m_end_line {true};
            std::ifstream *m_if {nullptr};
            std::string m_line;
        public:
            Iterator() = default;

            Iterator(std::ifstream *If, const bool _end) : m_end_line(_end), m_if(If)
            { }

            ~Iterator() = default;

            [[nodiscard]] const std::string &operator*() const noexcept
            {
                return m_line;
            }

            [[nodiscard]] std::string &operator*() noexcept
            {
                return m_line;
            }

            Iterator &operator++() noexcept
            {
                m_end_line = static_cast<bool>(std::getline(*m_if, m_line));
                return *this;
            }

            bool operator==(const Iterator &other) const noexcept
            {
                return m_end_line == other.m_end_line;
            }

            bool operator!=(const Iterator &other) const noexcept
            {
                return m_end_line != other.m_end_line;
            }
        };

    public:
        reader() = default;

        reader(const reader &) = default;

        reader(reader &&Reader) noexcept : m_end_line(Reader.m_end_line),  m_if(Reader.m_if), m_line( std::move(Reader.m_line))
        {
        }

        explicit reader(std::ifstream &&) = delete;

        explicit reader(std::ifstream &IfStream) noexcept: m_if(&IfStream)
        { }

        explicit reader(std::ifstream *IfStream) noexcept: m_if(IfStream)
        { }

        ~reader() = default;

        reader &operator=(std::ifstream &IfStream) noexcept
        {
            m_line.clear();
            m_end_line = true;
            m_if = &IfStream;
            return *this;
        }

        reader &operator=(std::ifstream *IfStream) noexcept
        {
            m_line.clear();
            m_end_line = true;
            m_if = IfStream;
            return *this;
        }

        reader &operator=(reader &&Reader) noexcept
        {
            m_end_line = Reader.m_end_line;
            m_if = Reader.m_if;
            m_line = std::move(Reader.m_line);
            return *this;
        }

        reader &operator=(const reader &) = default;

        [[nodiscard]] std::ifstream &get() noexcept
        {
            return *m_if;
        }

        [[nodiscard]] const std::ifstream &get() const noexcept
        {
            return *m_if;
        }

        std::string &read() noexcept
        {
            m_end_line = static_cast<bool>(std::getline(*m_if, m_line));
            return m_line;
        }

        explicit operator bool() noexcept
        {
            m_end_line = static_cast<bool>(std::getline(*m_if, m_line));
            return m_end_line;
        }

        [[nodiscard]] const std::string &line() const noexcept
        {
            return m_line;
        }

        [[nodiscard]] std::string &line() noexcept
        {
            return m_line;
        }

        auto begin() noexcept
        {
            return ++Iterator(m_if, m_end_line);
        }

        auto end() noexcept
        {
            return Iterator(m_if, false);
        }

        void close() noexcept
        {
            m_if->close();
        }
    };
}  // namespace babel::ITERATOR

inline std::ostream &operator<<(std::ostream &Of, const babel::ITERATOR::reader &Reader) noexcept
{
    Of << Reader.line();
    return Of;
}

#endif  // BABLIB_ITERATORS_READ_HPP_
