// Copyright [2021] <Wojtek>"
#ifndef BABLIBm_iteratorS_ENUMERATE_HPP_
#define BABLIBm_iteratorS_ENUMERATE_HPP_

#include <functional>

namespace babel::ITERATOR{

    template< typename Iter, typename Increment = std::plus<> >
    class enumerate
    {
        int64_t m_index;
        Iter m_iterator;
        Increment m_incr { };

        class Pair
        {
            using In = std::remove_reference_t<decltype(*Iter { })>;
            int64_t m_index;
            std::reference_wrapper<In> m_value;
        public:
            constexpr Pair() = delete;

            constexpr Pair(const int64_t Index, In &Value) noexcept: m_index(Index), m_value(Value)
            { }

            constexpr Pair(Pair &&other) noexcept: m_index(other.m_index), m_value(std::move(other.m_value))
            { }

            constexpr Pair(const Pair &other) noexcept: m_index(other.m_index), m_value(other.m_value)
            { }

            constexpr ~Pair() = default;

            [[nodiscard]] constexpr int64_t get_index() const noexcept
            {
                return m_index;
            }

            [[nodiscard]] constexpr auto &get_value() noexcept
            {
                return m_value.get();
            }

            [[nodiscard]] constexpr const auto &get_value() const noexcept
            {
                return m_value.get();
            }

            [[nodiscard]] constexpr int64_t first() const noexcept
            {
                return m_index;
            }

            [[nodiscard]] constexpr auto &second() noexcept
            {
                return m_value.get();
            }

            [[nodiscard]] constexpr const auto &second() const noexcept
            {
                return m_value.get();
            }
        };

    public:
        using value_type = Pair;

        constexpr enumerate() = delete;

        explicit constexpr enumerate(Iter iterator, const int64_t Start = 0) noexcept: m_index(Start),
                                                                                       m_iterator(iterator)
        { };

        constexpr enumerate(enumerate &&Enumerate) noexcept: m_index(Enumerate.m_index),
                                                             m_iterator(std::move(Enumerate.m_iterator))
        { }

        constexpr enumerate(const enumerate &Enumerate) noexcept: m_index(Enumerate.m_index),
                                                                  m_iterator(Enumerate.m_iterator)
        { }

        constexpr ~enumerate() = default;

        [[nodiscard]] constexpr int64_t &get_index() noexcept
        {
            return m_index;
        }

        [[nodiscard]] constexpr const int64_t &get_index() const noexcept
        {
            return m_index;
        }

        constexpr enumerate &operator=(const enumerate &Enumerate) noexcept
        {
            m_index = Enumerate.m_index;
            m_iterator = Enumerate.m_iterator;
            return *this;
        }

        constexpr enumerate &operator=(enumerate &&Enumerate) noexcept
        {
            m_index = Enumerate.m_index;
            m_iterator = std::move(Enumerate.m_iterator);
            return *this;
        }

        [[nodiscard]] constexpr auto operator*() noexcept
        {
            return Pair {m_index, *m_iterator};
        }

        [[nodiscard]] constexpr auto operator*() const noexcept
        {
            return Pair {m_index, *m_iterator};
        }

        constexpr enumerate &operator++() noexcept
        {
            m_index = m_incr(m_index, 1);
            ++m_iterator;
            return *this;
        }

        constexpr enumerate &operator--() noexcept
        {
            m_index = m_incr(m_index, -1);
            --m_iterator;
            return *this;
        }

        constexpr const enumerate operator++(int) noexcept //NOLINT
        {
            auto old = *this;
            m_index = m_incr(m_index, 1);
            ++m_iterator;
            return old;
        }

        constexpr const enumerate operator--(int) noexcept //NOLINT
        {
            auto old = *this;
            m_index = m_incr(m_index, -1);
            --m_iterator;
            return old;
        }

        constexpr bool operator==(const enumerate &other) const noexcept
        {
            return m_iterator == other.m_iterator;
        }

        constexpr bool operator!=(const enumerate &other) const noexcept
        {
            return m_iterator != other.m_iterator;
        }

        constexpr bool operator==(const Iter &other) const noexcept
        {
            return m_iterator == other;
        }

        constexpr bool operator!=(const Iter &other) const noexcept
        {
            return m_iterator != other;
        }
    };

    template< typename Container, typename Increment = std::plus<> >
    class enumerator
    {
        std::reference_wrapper<std::remove_reference_t<Container>> m_cont;
        using Iterator = decltype(std::begin(m_cont.get()));
    public:
        constexpr enumerator() = default;

        constexpr explicit enumerator(Container &Cont) noexcept: m_cont(Cont)
        { }

        constexpr auto begin(const int64_t Start = 0) noexcept
        {
            return enumerate<Iterator, Increment>(std::begin(m_cont.get()), Start);
        }

        constexpr auto begin(const int64_t Start = 0) const noexcept //NOLINT
        {
            return enumerate<Iterator, Increment>(std::begin(m_cont.get()), Start);
        }

        constexpr auto end() const noexcept //NOLINT
        {
            return enumerate<Iterator, Increment>(std::end(m_cont.get()));
        }

        constexpr auto end() noexcept
        {
            return enumerate<Iterator, Increment>(std::end(m_cont.get()));
        }
    };
}  // namespace babel::ITERATOR"

#endif  // BABLIBm_iteratorS_ENUMERATE_HPP_
