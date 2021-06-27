#ifndef babel_ITERATOR_GENERATOR
#define babel_ITERATOR_GENERATOR

#include "../must_have.hpp"

namespace babel::ITERATOR{

    template< typename Type >
    class generator
    {
        Type _gen;

        class iterator
        {
            Type *_gen {nullptr};
            int64_t _times {0};

        public:
            constexpr iterator(const Type &Sequence, const int64_t Times) noexcept: _gen(&Sequence), _times(Times)
            { }

            constexpr iterator(Type *Sequence, const int64_t Times) noexcept: _gen(Sequence), _times(Times)
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
                return *_gen;
            }


            constexpr iterator &operator++()
            {
                --_times;
                return *this;
            }

            constexpr const iterator operator++(int) //NOLINT
            {
                iterator other(_gen, _times);
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
                iterator other(_gen, _times);
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

        constexpr explicit generator(const Type &Sequence) noexcept: _gen(Sequence)
        { }

        constexpr generator(const generator &Other) noexcept: _gen(Other._gen)
        { }

        constexpr generator(generator &&Other) noexcept: _gen(std::move(Other._gen))
        { }

        [[nodiscard]] Type& stored() noexcept
        {
            return _gen;
        }

        [[nodiscard]] const Type& stored() const noexcept
        {
            return _gen;
        }

        [[nodiscard]] constexpr auto begin(const int64_t Times) noexcept
        {
            return iterator(&_gen, Times);
        }

        [[nodiscard]] constexpr auto end() noexcept
        {
            return iterator(&_gen, 0);
        }
    };

}


#endif