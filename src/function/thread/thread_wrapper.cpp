#include "thread_wrapper.hpp"

void Thread::game_thr(map &Map, std::pair<char, char> &from, const std::pair<char, char> &to,
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

void Thread::_run() noexcept
{
    m_th = std::thread(Thread::game_thr, std::ref(*m_map), std::ref(*m_from), std::ref(*m_to),
                       std::ref(m_operation), std::ref(m_cv), std::ref(m_mx));
}

Thread::Thread(map &Map, std::pair<char, char> &From, std::pair<char, char> &To, std::mutex &Mutex) noexcept
        : m_map(&Map), m_from(&From), m_to(&To), m_operation(0), m_mx(Mutex)
{
    _run();
}

void Thread::operation(const OperationType Operation) noexcept
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

void Thread::close_thread() noexcept
{
    operation(OperationType::EXIT);
    if ( m_th.joinable() )
        m_th.join();
}