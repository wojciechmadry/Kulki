// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ITERATORS_RANGE_HPP_
#define BABLIB_ITERATORS_RANGE_HPP_

#include <cstdint>
#include <stdexcept>

namespace babel::ITERATOR{
    template< typename Type = int64_t, typename StepType = int64_t >
    class range
    {
        Type m_start, m_stop;
        StepType m_step;
    public:
        class Iterator
        {
            Type m_val;
            StepType m_step;
        public:
            constexpr Iterator(const Type Val, const StepType Step) noexcept: m_val(Val), m_step(Step)
            { }

            constexpr ~Iterator() = default;

            [[nodiscard]] constexpr Type operator*() const noexcept
            {
                return m_val;
            }

            [[nodiscard]] constexpr Type &operator*() noexcept
            {
                return m_val;
            }

            constexpr Iterator &operator++() noexcept
            {
                m_val = static_cast<Type>(m_val + m_step);
                return *this;
            }

            constexpr const Iterator operator++(int) noexcept //NOLINT
            {
                auto _ret = *this;
                m_val = static_cast<Type>(m_val + m_step);
                return _ret;
            }

            constexpr bool operator==(const Iterator &Other) const noexcept
            {
                if ( m_step > 0 )
                    return Other.m_val <= m_val;
                return Other.m_val >= m_val;
            }

            constexpr bool operator!=(const Iterator &Other) const noexcept
            {
                if ( m_step < 0 )
                    return m_val > Other.m_val;
                return m_val < Other.m_val;
            }
        };

        constexpr range() noexcept: m_start(0), m_stop(0), m_step(0)
        { }

        constexpr range(Type Start, Type Stop, StepType Step = 1)
        {
            if ( Start > Stop && Step == 1 )
                Step = static_cast<StepType>(-1);
            if ( Start != Stop && Step == 0 )
                throw std::out_of_range("When Start != Stop then Step can't be 0.");
            if ( Start > Stop && Step > 0 )
                throw std::out_of_range("When Start > Stop then Step can't be >0.");
            else if ( Start < Stop && Step < 0 )
                throw std::out_of_range("When Start < Stop then Step can't be <0.");
            m_start = Start;
            m_stop = Stop;
            m_step = Step;
        }

        constexpr ~range() = default;

        [[nodiscard]]constexpr Type Start() const noexcept
        {
            return m_start;
        }

        [[nodiscard]]constexpr Type Stop() const noexcept
        {
            return m_stop;
        }

        [[nodiscard]]constexpr StepType Step() const noexcept
        {
            return m_step;
        }

        [[nodiscard]]constexpr Type &Start() noexcept
        {
            return m_start;
        }

        [[nodiscard]]constexpr Type &Stop() noexcept
        {
            return m_stop;
        }

        [[nodiscard]]constexpr StepType &Step() noexcept
        {
            return m_step;
        }

        [[nodiscard]]constexpr Iterator begin() const noexcept
        {
            return Iterator(m_start, m_step);
        }

        [[nodiscard]]constexpr Iterator end() const noexcept
        {
            return Iterator(m_stop, m_step);
        }
    };
}  // namespace babel::ITERATOR

#endif  // BABLIB_ITERATORS_RANGE_HPP_
