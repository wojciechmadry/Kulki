#ifndef babel_ITERATOR_WRITE
#define babel_ITERATOR_WRITE

#include "../must_have.hpp"

namespace babel::ITERATOR{
    class writer
    {
        std::ofstream *_of {nullptr};

        class back_inserter_iterator
        {
            std::ofstream *_of {nullptr};
            bool _new_line {false};
        public:
            back_inserter_iterator() = default;

            back_inserter_iterator(std::ofstream &OfStream, bool NewLine) noexcept: _of(&OfStream), _new_line(NewLine)
            { }

            back_inserter_iterator(std::ofstream *OfStream, bool NewLine) noexcept: _of(OfStream), _new_line(NewLine)
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
                ( *_of ) << ToInsert;
                if ( _new_line )
                    ( *_of ) << '\n';
                return *this;
            }
        };

    public:

        writer() = default;

        writer(const writer &) = default;

        writer(writer &&) = default;

        explicit writer(std::ofstream &OfStream) noexcept: _of(&OfStream)
        { }

        explicit writer(std::ofstream *OfStream) noexcept: _of(OfStream)
        { }

        ~writer() = default;

        writer &operator=(const writer &) = default;

        writer &operator=(writer &&) = default;

        writer &operator=(std::ofstream &OfStream) noexcept
        {
            _of = &OfStream;
            return *this;
        }

        writer &operator=(std::ofstream *OfStream) noexcept
        {
            _of = OfStream;
            return *this;
        }

        void write(const auto &line) noexcept
        {
            ( *_of ) << line;
        }

        void writeln(const auto &line) noexcept
        {
            ( *_of ) << line << "\n";
        }

        void push_back(const auto &line) noexcept
        {
            write(line);
        }

        void close() noexcept
        {
            _of->close();
        }

        back_inserter_iterator back_inserter(const bool AutoNewLine) noexcept
        {
            return back_inserter_iterator(_of, AutoNewLine);
        }
    };
}

#endif