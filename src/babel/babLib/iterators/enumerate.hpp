#ifndef babel_ITERATOR_ENUMERATE
#define babel_ITERATOR_ENUMERATE

#include "../must_have.hpp"

namespace babel::ITERATOR{

    template< typename Iter, typename Increment = std::plus<> >
    class enumerate
    {
        int64_t _index;
        Iter _iterator;
        Increment _incr { };

        class Pair
        {
            using In = std::remove_reference_t<decltype(*Iter { })>;
            int64_t _index;
            std::reference_wrapper<In> _value;
        public:
            constexpr Pair() = delete;

            constexpr Pair(const int64_t Index, In &Value) noexcept: _index(Index), _value(Value)
            { }

            constexpr Pair(Pair &&other) noexcept: _index(other._index), _value(std::move(other._value))
            { }

            constexpr Pair(const Pair &other) noexcept: _index(other._index), _value(other._value)
            { }

            constexpr ~Pair() = default;

            [[nodiscard]] constexpr int64_t get_index() const noexcept
            {
                return _index;
            }

            [[nodiscard]] constexpr auto &get_value() noexcept
            {
                return _value.get();
            }

            [[nodiscard]] constexpr const auto &get_value() const noexcept
            {
                return _value.get();
            }

            [[nodiscard]] constexpr int64_t first() const noexcept
            {
                return _index;
            }

            [[nodiscard]] constexpr auto &second() noexcept
            {
                return _value.get();
            }

            [[nodiscard]] constexpr const auto &second() const noexcept
            {
                return _value.get();
            }
        };

    public:
        using value_type = Pair;

        constexpr enumerate() = delete;

        explicit constexpr enumerate(Iter iterator, const int64_t Start = 0) noexcept: _index(Start),
                                                                                       _iterator(iterator)
        { };

        constexpr enumerate(enumerate &&Enumerate) noexcept: _index(Enumerate._index),
                                                             _iterator(std::move(Enumerate._iterator))
        { }

        constexpr enumerate(const enumerate &Enumerate) noexcept: _index(Enumerate._index),
                                                                  _iterator(Enumerate._iterator)
        { }

        constexpr ~enumerate() = default;

        [[nodiscard]] constexpr int64_t &get_index() noexcept
        {
            return _index;
        }

        [[nodiscard]] constexpr const int64_t &get_index() const noexcept
        {
            return _index;
        }

        constexpr enumerate &operator=(const enumerate &Enumerate) noexcept
        {
            _index = Enumerate._index;
            _iterator = Enumerate._iterator;
            return *this;
        }

        constexpr enumerate &operator=(enumerate &&Enumerate) noexcept
        {
            _index = Enumerate._index;
            _iterator = std::move(Enumerate._iterator);
            return *this;
        }

        [[nodiscard]] constexpr auto operator*() noexcept
        {
            return Pair {_index, *_iterator};
        }

        [[nodiscard]] constexpr auto operator*() const noexcept
        {
            return Pair {_index, *_iterator};
        }

        constexpr enumerate &operator++() noexcept
        {
            _index = _incr(_index, 1);
            ++_iterator;
            return *this;
        }

        constexpr enumerate &operator--() noexcept
        {
            _index = _incr(_index, -1);
            --_iterator;
            return *this;
        }

        constexpr const enumerate operator++(int) noexcept //NOLINT
        {
            auto old = *this;
            _index = _incr(_index, 1);
            ++_iterator;
            return old;
        }

        constexpr const enumerate operator--(int) noexcept //NOLINT
        {
            auto old = *this;
            _index = _incr(_index, -1);
            --_iterator;
            return old;
        }

        constexpr bool operator==(const enumerate &other) const noexcept
        {
            return _iterator == other._iterator;
        }

        constexpr bool operator!=(const enumerate &other) const noexcept
        {
            return _iterator != other._iterator;
        }

        constexpr bool operator==(const Iter &other) const noexcept
        {
            return _iterator == other;
        }

        constexpr bool operator!=(const Iter &other) const noexcept
        {
            return _iterator != other;
        }
    };

    template< typename Container, typename Increment = std::plus<> >
    class enumerator
    {
        std::reference_wrapper<std::remove_reference_t<Container>> _cont;
        using Iterator = decltype(std::begin(_cont.get()));
    public:
        constexpr enumerator() = default;

        constexpr explicit enumerator(Container &Cont) noexcept: _cont(Cont)
        { }

        constexpr auto begin(const int64_t Start = 0) noexcept
        {
            return enumerate<Iterator, Increment>(std::begin(_cont.get()), Start);
        }

        constexpr auto begin(const int64_t Start = 0) const noexcept //NOLINT
        {
            return enumerate<Iterator, Increment>(std::begin(_cont.get()), Start);
        }

        constexpr auto end() const noexcept //NOLINT
        {
            return enumerate<Iterator, Increment>(std::end(_cont.get()));
        }

        constexpr auto end() noexcept
        {
            return enumerate<Iterator, Increment>(std::end(_cont.get()));
        }
    };
}

#endif