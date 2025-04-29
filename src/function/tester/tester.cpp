#include "tester.hpp"

#include "drawer.hpp"
#include <atomic>
#include <iostream>
#include <random>
#include <thread>

void Play_Test_Games(int64_t test, int32_t threads) {
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<std::uint8_t> uniform_dist(0, 8);
  std::atomic<int32_t> record = -1;
  auto game = [&]() {
    bool is_inf = test == -1;
    int64_t counter = 0;
    map Game;
    while (is_inf || counter < test) {
      std::pair<uint8_t, uint8_t> from, to;
      if (Game.game_over()) {
        auto th_id = std::this_thread::get_id();
        auto score = Game.get_score();
        Game.reset();
        if (score > record) {
          record = score;
          std::cout << "Thread ID : " << th_id << " | Score : " << score
                    << '\n';
        }
      }
      do {
        from.first = uniform_dist(e1);
        from.second = uniform_dist(e1);
        to.first = uniform_dist(e1);
        to.second = uniform_dist(e1);
      } while (!Game.can_move(from, to));
      Game.move(from, to);
      ++counter;
    }
  };
  if (threads <= 0)
    threads =
        static_cast<decltype(threads)>(std::thread::hardware_concurrency());
  std::vector<std::thread> ths(static_cast<std::size_t>(threads));

  for (std::size_t i = 0; i < static_cast<std::size_t>(threads); ++i)
    ths[i] = std::thread(game);

  for (auto &th : ths)
    if (th.joinable())
      th.join();
}
