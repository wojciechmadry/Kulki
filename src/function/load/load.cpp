#include "load.hpp"
#include "BabelLib/babel.hpp"

// load font
sf::Font load_font(const std::string &path) {
  sf::Font font;
  if (!font.loadFromFile(path))
    throw std::out_of_range("Cant load font");
  return font;
}

std::pair<uint32_t, uint32_t> load_resolution() noexcept {
  const std::string FileName = "resolution.cfg";
  auto load_default_settings = [&FileName]() -> std::pair<uint32_t, uint32_t> {
    std::pair<uint32_t, uint32_t> res =
        babel::SYSTEM::DISPLAY::get_screen_resolution();
    std::ofstream f(FileName);
    f << res.first << '\n' << res.second;
    babel::FILE_SYS::close_file(f);
    return {res.first, res.second};
  };
  namespace fs = std::filesystem;
  if (!fs::exists(FileName)) {
    return load_default_settings();
  }
  auto lines = babel::FILE_SYS::load_txt_to_vector(FileName);
  std::for_each(lines.begin(), lines.end(),
                babel::ALGO::STRING::get_only_numbers);
  if (lines.size() != 2 || lines[0].size() > 4 || lines[1].size() > 4 ||
      lines[0].size() <= 2 || lines[1].size() <= 2) {
    return load_default_settings();
  }
  return {babel::ALGO::CAST::asType<uint32_t>(lines[0]),
          babel::ALGO::CAST::asType<uint32_t>(lines[1])};
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
