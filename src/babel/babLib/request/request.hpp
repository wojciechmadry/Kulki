#ifndef babel_REQUEST
#define babel_REQUEST

#include "../must_have.hpp"

namespace babel::REQ{
    class request
    {
        void _get() noexcept
        {
            _que.front()();
            _que.pop();
        }

    protected:
        std::queue<std::function<void()>> _que;
    public:
        request() = default;

        request(const request &) = delete;

        request(request &&other) noexcept: _que(std::move(other._que))
        { }

        request &operator=(const request &) = delete;

        request &operator=(request &&other) noexcept
        {
            _que = std::move(other._que);
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
                send_req(function_to_call, nullptr, std::forward<Args>(args)...);
            else
                _que.emplace(
                        [function_to_call, return_to, &args...]() mutable -> void {
                            *return_to = ( function_to_call )(std::forward<Args>(args)...);
                        }
                );
        }

        template< typename Func, typename ... Args >
        void send_req(Func
                      function_to_call,
                      std::nullptr_t NULLPTR, Args
                      &&... args) noexcept
        {

            _que.emplace(
                    [function_to_call, &args...]() -> void {
                        ( function_to_call )(std::forward<Args>(args)...);
                    }
            );
        }

        void call_n(size_t n)
        {
            if ( _que.size() < n )
                throw std::out_of_range("Size of que is less than n");
            while ( n-- > 0 )
                _get();
        }

        void call_n_if_possible(size_t n) noexcept
        {
            auto max_range = std::min(n, _que.size());
            while ( max_range-- > 0 )
                _get();
        }

        void call_if_possible() noexcept
        {
            if ( !_que.empty() )
                _get();
        }

        void call()
        {
            if ( _que.empty() )
                throw std::out_of_range("Que is empty");
            _get();
        }

        void call_all() noexcept
        {
            while ( !_que.empty() )
                _get();
        }

        void clear() noexcept
        {
            std::queue<std::function<void()>> empty;
            _que = std::move(empty);
        }

        [[nodiscard]] bool has_request() const noexcept
        {
            return !_que.empty();
        }

        [[nodiscard]] bool is_empty() const noexcept
        {
            return _que.empty();
        }

        [[nodiscard]] auto request_size() const noexcept
        {
            return _que.size();
        }

        void pop()
        {
            if ( _que.empty() )
                throw std::out_of_range("Que is empty");
            _que.pop();
        }

        void pop_if_possible() noexcept
        {
            if ( !_que.empty() )
                _que.pop();
        }

        void pop_n(size_t n)
        {
            if ( _que.size() < n )
                throw std::out_of_range("Size of que is less than n");
            while ( n-- > 0 )
                _que.pop();
        }

        void pop_n_if_possible(size_t n) noexcept
        {
            auto max_range = std::min(n, _que.size());
            while ( max_range-- > 0 )
                _que.pop();
        }
    };
}

#endif