//
// Created by Wojtek on 26.04.2021.
//

#ifndef KULKI_THREAD_WRAPPER_HPP
#define KULKI_THREAD_WRAPPER_HPP

#include "function/drawer/drawer.hpp"

enum class OperationType
{
    EXIT = -1,
    NOTHING = 0,
    MOVE = 1,
    RESET = 2,
    UPDATE = 3
};

//Operation on map works on different thread
class Thread
{
    static void
    game_thr(map &Map, std::pair<char, char> &from, const std::pair<char, char> &to,
             int &operation, std::condition_variable &cv, std::mutex &mx);

    map *m_map;
    std::pair<char, char> *m_from;
    std::pair<char, char> *m_to;
    int m_operation;
    std::thread m_th;
    std::reference_wrapper<std::mutex> m_mx;
    std::condition_variable m_cv;

    void _run() noexcept;

public:
    Thread() = delete;

    ~Thread() = default;

    Thread(map &Map, std::pair<char, char> &From, std::pair<char, char> &To, std::mutex &Mutex) noexcept;


    void operation(OperationType Operation) noexcept;

    void close_thread() noexcept;
};

#endif //KULKI_THREAD_WRAPPER_HPP
