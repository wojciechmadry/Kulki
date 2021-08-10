#include "tester.hpp"

#include "babel/babel.hpp"
#include <chrono>
#include <thread>
#include <atomic>
#include "function/drawer/drawer.hpp"
#include <iostream>

void Play_Test_Games(int64_t test, int32_t threads)
{
    babel::ALGO::MATH::random_generator rg;
    int32_t record = -1;
    auto game = [=,&record]() mutable{
        bool is_inf = test==-1;
        int64_t counter = 0;
        map Game;
        while(is_inf || counter < test)
        {
            std::pair<uint8_t, uint8_t> from, to;
            if(Game.game_over())
            {
                auto th_id = std::this_thread::get_id();
                auto score = Game.get_score();
                Game.reset();
                if(score > record)
                {
                    record = score;
                    std::cout <<"Thread ID : " << th_id << " | Score : " << score << '\n';
                }
            }
            do
            {
                from.first = rg.generate<uint8_t>(0, 8);
                from.second = rg.generate<uint8_t>(0, 8);
                to.first = rg.generate<uint8_t>(0, 8);
                to.second = rg.generate<uint8_t>(0, 8);
            }while(!Game.can_move(from, to));
            Game.move(from, to);
            ++counter;
        }
    };
    if (threads <= 0)
        threads = static_cast<decltype(threads)>(std::thread::hardware_concurrency());
    std::vector<std::thread> ths(static_cast<std::size_t>(threads));

    for(std::size_t i = 0 ; i < static_cast<std::size_t>(threads) ; ++i)
        ths[i] = std::thread(game);

    for(auto& th : ths)
        if(th.joinable())
            th.join();
}