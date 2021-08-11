// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ITERATORS_WRITE_HPP_
#define BABLIB_ITERATORS_WRITE_HPP_

#include <fstream>

namespace babel::ITERATOR{
    class writer
    {
        std::ofstream *m_of {nullptr};

        class back_inserter_iterator
        {
            std::ofstream *m_of {nullptr};
            bool m_new_line {false};
        public:
            back_inserter_iterator() = default;

            back_inserter_iterator(std::ofstream &OfStream, bool NewLine) noexcept: m_of(&OfStream), m_new_line(NewLine)
            { }

            back_inserter_iterator(std::ofstream *OfStream, bool NewLine) noexcept: m_of(OfStream), m_new_line(NewLine)
            { }

            ~back_inserter_iterator() = default;

            back_inserter_iterator &operator*() noexcept
            {
                return *this;
            }

            back_inserter_iterator &operator++() noexcept
            {
                return *this;
            }

            const back_inserter_iterator operator++(int) noexcept //NOLINT
            {
                return *this;
            }

            back_inserter_iterator &operator=(const auto &ToInsert) noexcept
            {
                ( *m_of ) << ToInsert;
                if ( m_new_line )
                    ( *m_of ) << '\n';
                return *this;
            }
        };

    public:
        writer() = default;

        writer(const writer &) = default;

        writer(writer &&) = default;

        explicit writer(std::ofstream &OfStream) noexcept: m_of(&OfStream)
        { }

        explicit writer(std::ofstream *OfStream) noexcept: m_of(OfStream)
        { }

        ~writer() = default;

        writer &operator=(const writer &) = default;

        writer &operator=(writer &&) = default;

        writer &operator=(std::ofstream &OfStream) noexcept
        {
            m_of = &OfStream;
            return *this;
        }

        writer &operator=(std::ofstream *OfStream) noexcept
        {
            m_of = OfStream;
            return *this;
        }

        void write(const auto &line) noexcept
        {
            ( *m_of ) << line;
        }

        void writeln(const auto &line) noexcept
        {
            ( *m_of ) << line << "\n";
        }

        void push_back(const auto &line) noexcept
        {
            write(line);
        }

        void close() noexcept
        {
            m_of->close();
        }

        back_inserter_iterator back_inserter(const bool AutoNewLine) noexcept
        {
            return back_inserter_iterator(m_of, AutoNewLine);
        }
    };
}  // namespace babel::ITERATOR

#endif  // BABLIB_ITERATORS_WRITE_HPP_
