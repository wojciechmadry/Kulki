#include "load.hpp"
#include <filesystem>
#include <fstream>

uint32_t load_fps() noexcept {
  const std::string FileName = "fps.cfg";
  const constexpr uint32_t DefaultFPS = 30u;
  auto LoadDefault = [&FileName]() -> uint32_t {
    std::ofstream f(FileName);
    f << DefaultFPS;
    return DefaultFPS;
  };
  namespace fs = std::filesystem;
  if (!fs::exists(FileName)) {
    return LoadDefault();
  }
  std::string FPS = std::to_string(DefaultFPS);
  std::ifstream f(FileName);
  if (f.is_open()) {
    std::getline(f, FPS);
  }
  auto uFPS = static_cast<std::uint32_t>(std::stoul(FPS));

  uFPS = std::min(uFPS, 10u * DefaultFPS);
  uFPS = std::max(uFPS, DefaultFPS);

  return uFPS;
}
