// Copyright [2021] <Wojtek>"
#ifndef BABLIB_REQUEST_REQUEST_HPP_
#define BABLIB_REQUEST_REQUEST_HPP_

#include <functional>
#include <queue>
#include <stdexcept>

namespace babel::REQ{
    class request
    {
        void _get() noexcept
        {
            m_que.front()();
            m_que.pop();
        }

    protected:
        std::queue<std::function<void()>> m_que;
    public:
        request() = default;

        request(const request &) = delete;

        request(request &&other) noexcept: m_que(std::move(other.m_que))
        { }

        request &operator=(const request &) = delete;

        request &operator=(request &&other) noexcept
        {
            m_que = std::move(other.m_que);
            return *this;
        }

        ~request() noexcept
        {
            clear();
        }

        template< typename T = void, typename Func, typename ... Args >
        requires ( !std::same_as<T, std::nullptr_t> )
        void send_req(Func function_to_call, T *return_to = nullptr, Args &&... args) noexcept
        {
            if ( return_to == nullptr )
            { send_req(function_to_call, nullptr, std::forward<Args>(args)...); }
            else
            {
                m_que.emplace(
                        [function_to_call, return_to, &args...]() mutable -> void {
                            *return_to = ( function_to_call )(std::forward<Args>(args)...);
                        }
                );
            }
        }

        template< typename Func, typename ... Args >
        void send_req(Func
                      function_to_call,
                      std::nullptr_t, Args
                      &&... args) noexcept
        {

            m_que.emplace(
                    [function_to_call, &args...]() -> void {
                        ( function_to_call )(std::forward<Args>(args)...);
                    }
            );
        }

        void call_n(size_t n)
        {
            if ( m_que.size() < n )
                throw std::out_of_range("Size of que is less than n");
            while ( n-- > 0 )
                _get();
        }

        void call_n_if_possible(size_t n) noexcept
        {
            auto max_range = std::min(n, m_que.size());
            while ( max_range-- > 0 )
                _get();
        }

        void call_if_possible() noexcept
        {
            if ( !m_que.empty() )
                _get();
        }

        void call()
        {
            if ( m_que.empty() )
                throw std::out_of_range("Que is empty");
            _get();
        }

        void call_all() noexcept
        {
            while ( !m_que.empty() )
                _get();
        }

        void clear() noexcept
        {
            m_que = { };
        }

        [[nodiscard]] bool has_request() const noexcept
        {
            return !m_que.empty();
        }

        [[nodiscard]] bool is_empty() const noexcept
        {
            return m_que.empty();
        }

        [[nodiscard]] auto request_size() const noexcept
        {
            return m_que.size();
        }

        void pop()
        {
            if ( m_que.empty() )
                throw std::out_of_range("Que is empty");
            m_que.pop();
        }

        void pop_if_possible() noexcept
        {
            if ( !m_que.empty() )
                m_que.pop();
        }

        void pop_n(size_t n)
        {
            if ( m_que.size() < n )
                throw std::out_of_range("Size of que is less than n");
            while ( n-- > 0 )
                m_que.pop();
        }

        void pop_n_if_possible(size_t n) noexcept
        {
            auto max_range = std::min(n, m_que.size());
            while ( max_range-- > 0 )
                m_que.pop();
        }
    };
}  // namespace babel::REQ

#endif  // BABLIB_REQUEST_REQUEST_HPP_
