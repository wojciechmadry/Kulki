//
// Created by Wojtek on 23.04.2021.
//

#ifndef KULKI_WAITER_HPP
#define KULKI_WAITER_HPP

#include <chrono>
#include <thread>
#include <atomic>
#include "../babel/babel.hpp"
#include "drawer.hpp"

template<typename ATOMIC_TYPE>
class waiter
{
    uint32_t _fps;
    ATOMIC_TYPE* _at;
    using StorageType = typename babel::CONCEPTS::type_in_atomic<ATOMIC_TYPE>::type;
public:
    waiter() = delete;
    waiter(ATOMIC_TYPE& Status, const uint32_t refresh_rate) noexcept
    : _at(&Status)
    {
        _fps = 1000 / refresh_rate;
    }

    void wait(const StorageType expectValue) noexcept
    {
        while (*_at != expectValue)
            std::this_thread::sleep_for(std::chrono::milliseconds(_fps));
    }

    void set_and_wait(const StorageType SET, const StorageType expectValue) noexcept
    {
        *_at = SET;
        wait(expectValue);
    }
};
#endif //KULKI_WAITER_HPP
