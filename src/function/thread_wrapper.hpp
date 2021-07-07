//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_THREAD_WRAPPER_HPP
#define KULKI_THREAD_WRAPPER_HPP

#include "drawer.hpp"

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
    game_thr(map &Map, std::pair<char, char> &from, const std::pair<char, char> &to,
             int &operation, std::condition_variable &cv, std::mutex &mx)
    {
        std::unique_lock<std::mutex> uLock(mx, std::defer_lock);
        while ( operation != -1 )
        {
            cv.wait(uLock, [&]() {
                        return operation != 0;
                    }
            );
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

            operation = babel::ALGO::MATH::min(operation, 0);
            cv.notify_one();
        }
    }

    map *m_map;
    std::pair<char, char> *m_from;
    std::pair<char, char> *m_to;
    int m_operation;
    std::thread m_th;
    std::reference_wrapper<std::mutex> m_mx;
    std::condition_variable m_cv;

    void _run() noexcept
    {
        m_th = std::thread(Thread::game_thr, std::ref(*m_map), std::ref(*m_from), std::ref(*m_to),
                           std::ref(m_operation), std::ref(m_cv), std::ref(m_mx));
    }

public:
    Thread() = delete;

    ~Thread() = default;

    Thread(map &Map, std::pair<char, char> &From, std::pair<char, char> &To, std::mutex &Mutex) noexcept
            : m_map(&Map), m_from(&From), m_to(&To), m_operation(0), m_mx(Mutex)
    {
        _run();
    }


    void operation(const OperationType Operation) noexcept
    {
        std::unique_lock<std::mutex> uLock(m_mx.get(), std::defer_lock);
        uLock.lock();
        m_operation = static_cast<int>(Operation);
        m_cv.notify_one();
        m_cv.wait(uLock, [&]() {
                      return m_operation <= 0;
                  }
        );

    }

    void close_thread() noexcept
    {
        operation(OperationType::EXIT);
        if ( m_th.joinable() )
            m_th.join();
    }
};

#endif //KULKI_THREAD_WRAPPER_HPP
