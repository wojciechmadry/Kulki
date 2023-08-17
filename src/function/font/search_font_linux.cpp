#ifdef linux
#include "search_font.hpp"

[[nodiscard]] babel::OPT::optional<std::string> search_font() noexcept {
  constexpr const char *command =
      R"(find /usr/share/fonts -name "*.ttf" | head -n 1 > babel_temporary_font)";
  auto sys_res = system(command);
  std::fstream file_babel("babel_temporary_font", std::ios::in | std::ios::out);
  if (sys_res == 0 && file_babel.good() && file_babel.is_open()) {
    std::string path;
    std::getline(file_babel, path);
    auto found_ttf = path.find_last_of(".ttf");

    file_babel.close();
    sys_res = system("rm babel_temporary_font");
    if (sys_res == 0 && found_ttf != std::string::npos) {
      return path;
    }
  }

  return {};
}
#endif

