#ifndef KULKI_SEARCH_FONT_HPP
#define KULKI_SEARCH_FONT_HPP

#include "../babel/babel.hpp"

//Finding fonts in disc
[[nodiscard]] babel::OPT::optional<std::string> search_font() noexcept
{
    std::list<std::string> discs;
    for(char alph = 'A'; alph <= 'Z' ; ++alph)
    {
        std::string disc;
        disc = alph;
        disc += ":/";
        if(babel::FILE_SYS::folder_exist(disc))
            discs.emplace_back(std::move(disc));
    }

    auto filter_list = [](std::list<std::string>& List, const std::string& Folder) ->void {
        auto begin= List.begin();
        for(;begin != List.end() ; ++begin)
        {
            *begin = *begin + Folder +"/";
            if (!babel::FILE_SYS::folder_exist(*begin))
                List.erase(begin);
        }
    };

    filter_list(discs, "windows");
    filter_list(discs, "fonts");

    if (discs.empty())
        return {};

    std::vector<std::pair<std::string, std::vector<std::string>>> all_files;

    for(auto& Disc : discs)
        all_files.emplace_back(std::make_pair(std::move(Disc),babel::FILE_SYS::scan_folder(Disc)));

    if (all_files.empty())
        return {};

    for(auto& Folder : all_files)
    {
        for(auto& File : Folder.second)
        {
            auto file_extension = babel::FILE_SYS::file_extension(File);
            for (auto & c: file_extension) c = static_cast<char>(toupper(c));
            if ( file_extension == "TTF")
            {
                return {Folder.first + File};
            }
        }
    }

    return {};
}

#endif