#include "load.hpp"
#include "babel.hpp"

// load font
sf::Font load_font(const std::string &path) {
  sf::Font font;
  if (!font.loadFromFile(path))
    throw std::out_of_range("Cant load font");
  return font;
}

uint32_t load_fps() noexcept {
  const std::string FileName = "fps.cfg";
  const constexpr uint32_t DefaultFPS = 30u;
  auto LoadDefault = [&FileName]() -> uint32_t {
    std::ofstream f(FileName);
    f << DefaultFPS;
    babel::FILE_SYS::close_file(f);
    return DefaultFPS;
  };
  namespace fs = std::filesystem;
  if (!fs::exists(FileName)) {
    return LoadDefault();
  }
  auto FPS = babel::FILE_SYS::load_txt(FileName);

  auto uFPS = babel::ALGO::CAST::asType<uint32_t>(
      babel::ALGO::STRING::get_only_numbers(FPS));

  uFPS = babel::ALGO::MATH::min(uFPS, 10u * DefaultFPS);
  uFPS = babel::ALGO::MATH::max(uFPS, DefaultFPS);

  return uFPS;
}
