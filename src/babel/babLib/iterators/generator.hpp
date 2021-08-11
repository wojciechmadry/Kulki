// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ITERATORS_GENERATOR_HPP_
#define BABLIB_ITERATORS_GENERATOR_HPP_

#include <cstdint>
#include <utility>

namespace babel::ITERATOR{

    template< typename Type >
    class generator
    {
        Type m_gen;

        class iterator
        {
            Type *m_gen {nullptr};
            int64_t _times {0};

        public:
            constexpr iterator(const Type &Sequence, const int64_t Times) noexcept: m_gen(&Sequence), _times(Times)
            { }

            constexpr iterator(Type *Sequence, const int64_t Times) noexcept: m_gen(Sequence), _times(Times)
            { }

            [[nodiscard]] constexpr int64_t &times() noexcept
            {
                return _times;
            }

            [[nodiscard]] constexpr int64_t times() const noexcept
            {
                return _times;
            }

            constexpr const Type &operator*() const noexcept
            {
                return *m_gen;
            }


            constexpr iterator &operator++()
            {
                --_times;
                return *this;
            }

            constexpr const iterator operator++(int) //NOLINT
            {
                iterator other(m_gen, _times);
                --_times;
                return other;
            }

            constexpr iterator &operator--()
            {
                ++_times;
                return *this;
            }

            constexpr const iterator operator--(int) //NOLINT
            {
                iterator other(m_gen, _times);
                ++_times;
                return other;
            }

            constexpr bool operator==(const iterator &other) const noexcept
            {
                return _times == other._times;
            }

            constexpr bool operator!=(const iterator &other) const noexcept
            {
                return _times != other._times;
            }
        };

    public:
        constexpr generator() = delete;

        constexpr explicit generator(const Type &Sequence) noexcept: m_gen(Sequence)
        { }

        constexpr generator(const generator &Other) noexcept: m_gen(Other.m_gen)
        { }

        constexpr generator(generator &&Other) noexcept: m_gen(std::move(Other.m_gen))
        { }

        [[nodiscard]] Type& stored() noexcept
        {
            return m_gen;
        }

        [[nodiscard]] const Type& stored() const noexcept
        {
            return m_gen;
        }

        [[nodiscard]] constexpr auto begin(const int64_t Times) noexcept
        {
            return iterator(&m_gen, Times);
        }

        [[nodiscard]] constexpr auto end() noexcept
        {
            return iterator(&m_gen, 0);
        }
    };

}  // namespace babel::ITERATOR


#endif  // BABLIB_ITERATORS_GENERATOR_HPP_
