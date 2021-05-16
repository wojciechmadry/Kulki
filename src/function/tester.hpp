#include <chrono>
#include <thread>
#include <atomic>
#include "../babel/babel.hpp"
#include "drawer.hpp"
#include <iostream>

void Play_Test_Games(int64_t test = -1, int32_t threads = -1)
{
    int32_t record = -1;
    auto game = [=,&record]() mutable{
        bool is_inf = test==-1;
        int64_t counter = 0;
        map Game;
        while(is_inf || counter < test)
        {
            std::pair<byte, byte> from, to;
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
                from.first = random_generator::generate<byte>(0, 8);
                from.second = random_generator::generate<byte>(0, 8);
                to.first = random_generator::generate<byte>(0, 8);
                to.second = random_generator::generate<byte>(0, 8);
            }while(!Game.can_move(from, to));
            Game.move(from, to);
            ++counter;
        }
    };
    if (threads <= 0)
        threads = static_cast<decltype(threads)>(std::thread::hardware_concurrency());
    std::vector<std::thread> ths(static_cast<uint64_t>(threads));

    for(uint64_t i = 0 ; i < static_cast<uint64_t>(threads) ; ++i)
        ths[i] = std::thread(game);

    for(auto& th : ths)
        if(th.joinable())
            th.join();
}