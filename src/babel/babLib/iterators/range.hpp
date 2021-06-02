#ifndef babel_ITERATOR_RANGE
#define babel_ITERATOR_RANGE

#include "../must_have.hpp"

namespace babel::ITERATOR{
    class range
    {
        int64_t _start, _stop, _step;
    public:

        class Iterator
        {
            int64_t _val, _step;
        public:
            constexpr Iterator(const int64_t Val, const int64_t Step) noexcept: _val(Val), _step(Step)
            { }
            constexpr ~Iterator() = default;

            [[nodiscard]] constexpr int64_t operator*() const noexcept
            {
                return _val;
            }

            [[nodiscard]] constexpr int64_t &operator*() noexcept
            {
                return _val;
            }

            constexpr Iterator &operator++() noexcept
            {
                _val += _step;
                return *this;
            }

            constexpr const Iterator operator++(int) noexcept //NOLINT
            {
                auto _ret = *this;
                _val += _step;
                return _ret;
            }

            constexpr bool operator==(const Iterator &Other) const noexcept
            {
                if ( _step > 0 )
                    return Other._val <= _val;
                return Other._val >= _val;
            }

            constexpr bool operator!=(const Iterator &Other) const noexcept
            {
                if ( _step < 0 )
                    return _val > Other._val;
                return _val < Other._val;
            }

        };

        constexpr range() noexcept: _start(0), _stop(0), _step(0)
        { }
        constexpr range(int64_t Start, int64_t Stop, int64_t Step = 1)
        {
            if ( Start > Stop && Step == 1 )
                Step = -1;
            if ( Start != Stop && Step == 0 )
                throw std::out_of_range("When Start != Stop then Step can't be 0.");
            if ( Start > Stop && Step > 0 )
                throw std::out_of_range("When Start > Stop then Step can't be >0.");
            else if ( Start < Stop && Step < 0 )
                throw std::out_of_range("When Start < Stop then Step can't be <0.");
            _start = Start;
            _stop = Stop;
            _step = Step;
        }

        constexpr ~range() = default;

        [[nodiscard]]constexpr int64_t Start() const noexcept
        {
            return _start;
        }

        [[nodiscard]]constexpr int64_t Stop() const noexcept
        {
            return _start;
        }

        [[nodiscard]]constexpr int64_t Step() const noexcept
        {
            return _start;
        }

        [[nodiscard]]constexpr int64_t &Start() noexcept
        {
            return _start;
        }

        [[nodiscard]]constexpr int64_t &Stop() noexcept
        {
            return _start;
        }

        [[nodiscard]]constexpr int64_t &Step() noexcept
        {
            return _start;
        }

        [[nodiscard]]constexpr Iterator begin() const noexcept
        {
            return Iterator(_start, _step);
        }

        [[nodiscard]]constexpr Iterator end() const noexcept
        {
            return Iterator(_stop, _step);
        }
    };
}

#endif