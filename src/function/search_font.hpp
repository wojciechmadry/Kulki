#ifndef KULKI_SEARCH_FONT_HPP
#define KULKI_SEARCH_FONT_HPP

#include "../babel/babel.hpp"

//Finding fonts in disc
[[nodiscard]] babel::OPT::optional<std::string> search_font() noexcept
{

    auto discs = babel::WINDOWS::SYSTEM::all_discs();

    auto filter_list = [](auto &Disc, const std::string &Folder) -> void {
        std::decay_t<decltype(Disc)> new_list;
        auto begin = Disc.begin();
        while ( begin != Disc.end() )
        {
            *begin = *begin + Folder + "/";
            if ( babel::FILE_SYS::folder_exist(*begin) )
                new_list.emplace_back(std::move(*begin));
            ++begin;
        }
        Disc = std::move(new_list);
    };

    filter_list(discs, "windows");
    filter_list(discs, "fonts");

    if ( discs.empty() )
        return { };

    std::vector<std::pair<std::string, std::vector<std::string>>> all_files;

    for ( auto &Disc : discs )
    {
        auto files = babel::FILE_SYS::scan_folder(Disc);
        std::vector<std::string> TTF_Files;
        for(auto& File : files)
        {
            auto extension = babel::FILE_SYS::file_extension(File);
            extension = babel::ALGO::STRING::str_to_upper(extension);
            if (extension == "TTF")
                TTF_Files.emplace_back(std::move(File));
        }
        all_files.emplace_back(std::make_pair(std::move(Disc), std::move(TTF_Files)));
    }

    if ( all_files.empty() )
        return { };

    static const constexpr std::array<const char*,4> wanted_font = {
            "COMIC",
            "TIMES",
            "ARIAL",
            "CALIBRI"
    };

    for(const auto& WantedFont : wanted_font)
    {
        for(const auto& DIRECTORY : all_files)
        {
            for(const auto& File : DIRECTORY.second)
            {
                auto file_name =babel::FILE_SYS::file_without_extension(File);
                file_name = babel::ALGO::STRING::str_to_upper(file_name);
                if (file_name == WantedFont)
                    return {DIRECTORY.first + File};
            }
        }
    }


    return {all_files[0].first + all_files[0].second[0]};
}

#endif