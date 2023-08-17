#ifdef _WIN32
#include "search_font.hpp"

[[nodiscard]] babel::OPT::optional<std::string> search_font() noexcept {
  auto discs = babel::SYSTEM::SYSTEM::all_discs();

  auto filter_list = [](auto &Disc, const std::string &Folder) -> void {
    std::decay_t<decltype(Disc)> new_list;
    std::for_each(std::begin(Disc), std::end(Disc),
                  [&Folder, &new_list](auto &FolderName) mutable {
                    FolderName += Folder;
                    if (babel::FILE_SYS::folder_exist(FolderName))
                      new_list.emplace_back(std::move(FolderName) + "/");
                  });
    Disc = std::move(new_list);
  };

  filter_list(discs, "Windows");
  filter_list(discs, "fonts");

  if (discs.empty())
    return {};

  std::vector<std::pair<std::string, std::vector<std::string>>> all_files;

  std::transform(
      discs.begin(), discs.end(), std::back_inserter(all_files),
      [](auto &Disc) -> std::pair<std::string, std::vector<std::string>> {
        auto files = babel::FILE_SYS::scan_folder(Disc);
        std::vector<std::string> TTF_Files;
        std::for_each(
            files.begin(), files.end(), [&TTF_Files](auto &File) mutable {
              auto extension = babel::FILE_SYS::file_extension(File);
              extension = babel::ALGO::STRING::str_to_upper(extension);
              if (extension == "TTF")
                TTF_Files.emplace_back(std::move(File));
            });
        return std::make_pair(std::move(Disc), std::move(TTF_Files));
      });

  if (all_files.empty())
    return {};

  static const constexpr std::array<const char *, 4> wanted_font = {
      "COMIC", "TIMES", "ARIAL", "CALIBRI"};

  for (const auto &WantedFont : wanted_font) {
    for (const auto &DIRECTORY : all_files) {
      auto found = std::find_if(
          DIRECTORY.second.begin(), DIRECTORY.second.end(),
          [&WantedFont](const auto &File) -> bool {
            auto file_name = babel::FILE_SYS::file_without_extension(File);
            file_name = babel::ALGO::STRING::str_to_upper(file_name);
            return file_name == WantedFont;
          });
      if (found != DIRECTORY.second.end())
        return {DIRECTORY.first + *found};
    }
  }

  return {all_files[0].first + all_files[0].second[0]};
}

#endif

