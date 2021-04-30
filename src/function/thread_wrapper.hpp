//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_THREAD_WRAPPER_HPP
#define KULKI_THREAD_WRAPPER_HPP

#include "function/waiter.hpp"

enum class OperationType
{
    EXIT = -1,
    NOTHING = 0,
    MOVE = 1,
    RESET = 2,
    UPDATE = 3
};

//Operation on map works on diffrent thread
class Thread
{
    static void
    game_thr(map &Map, const uint32_t fps, std::pair<char, char> &from, const std::pair<char, char> &to,
             std::atomic<int> &operation)
    {
        uint32_t _fps = babel::MATH::min(fps, 244u);
        _fps = 1000 / _fps;
        while ( operation != -1 )
        {
            if ( operation > 0 )
            {
                if ( operation == 3 )
                {
                    Map.set_update(true);
                } else if ( operation == 1 )
                {
                    if ( Map.move(from, to) )
                    {
                        from = {-1, -1};
                    }
                } else if ( operation == 2 )
                {
                    Map.reset();
                }
                operation = 0;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(_fps));
        }
        operation = 0;
    }

    map *_map;//NOLINT
    uint32_t _fps;
    std::pair<char, char> *_from;
    std::pair<char, char> *_to;
    std::atomic<int> _operation;
    waiter<decltype(_operation)> _waiter;
    std::thread _th;

    void _run() noexcept
    {
        _th = std::thread(Thread::game_thr, std::ref(*_map), _fps, std::ref(*_from), std::ref(*_to),
                          std::ref(_operation));
    }
public:
    Thread() = delete;

    ~Thread() = default;

    Thread(map &Map, uint32_t FPS, std::pair<char, char> &From, std::pair<char, char> &To) noexcept
            : _map(&Map), _fps(FPS), _from(&From), _to(&To), _operation(0), _waiter(_operation, FPS)
    {
        _run();
    }



    void operation(const OperationType Operation) noexcept
    {
        _waiter.set_and_wait(static_cast<int>(Operation), static_cast<int>(OperationType::NOTHING));
    }

    void close_thread() noexcept
    {
        operation(OperationType::EXIT);
        _th.join();
    }
};

#endif //KULKI_THREAD_WRAPPER_HPP
