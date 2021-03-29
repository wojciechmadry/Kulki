#ifndef BABEL_FILE_SYSTEM
#define BABEL_FILE_SYSTEM

#include "must_have.hpp"

namespace babel::FILE_SYS {

    /**
*  @brief  Close file
*  @param  Fstream ifstream/ofstream/fstream to close
*/
    template<typename Filestream>
    requires babel::CONCEPTS::MEMBER::HAS_CLOSE<Filestream>
    void close_file(Filestream &Fstream)
    {
        if constexpr(babel::CONCEPTS::IS_POINTER<Filestream>)
            Fstream->close();
        else
            Fstream.close();
    }

    /**
   *  @brief  Close multiple file
   *  @param  Fstream ifstream/ofstream/fstream to close
   *  @param arg ifstream/ofstream/fstream to close
   */
    template<typename Filestream, typename ... Args>
    requires babel::CONCEPTS::MEMBER::HAS_CLOSE<Filestream>
    void close_file(Filestream &Fstream, Args &... arg)//NOLINT
    {
        close_file(Fstream);
        close_file(arg...);
    }

    /**
*  @brief  Scan folder and return filename
*  @param  path Folder to scan
*  @return Vector of filename with extension in folder
*/
    std::vector<std::string> scan_folder(const std::string &path)
    {
        std::vector<std::string> _res;
        for (const auto &obj : std::filesystem::directory_iterator(path))
            _res.push_back(obj.path().filename().string());
        return _res;
    }

    /**
*  @brief  If filename has extension ex.: .exe that return exe
*  if filename is ex.: folder that return "none"
*  @param  filename filename with extension or without.
*  @return File extension ex: .exe, .txt etc.
*/
    std::string file_extension(const std::string &filename)
    {
        auto _find_dot = filename.find('.');
        if (_find_dot != std::string::npos)
            return filename.substr(_find_dot + 1, filename.size());
        else
            return "none";
    }

    /**
*  @brief  Convert filename with extension to just filename
*  @param  filename filename with extension or without.
*  @return Filename without extension ex.: test.txt -> test
*/
    std::string file_without_extension(const std::string &filename)
    {
        auto _find_dot = filename.find('.');
        if (_find_dot != std::string::npos)
            return filename.substr(0, _find_dot);
        else
            return filename;
    }

    /**
*  @brief  ex.: filename = "test.txt" /
*    contain = "te" -> return 1 /
*    contain = "txt" -> return 1/
*    contain = "test.txtt" -> return 0
*  @param  filename filename with extension or without.
*  @param  contain text we want to find in filename.
*  @return If filename contains contain return 1 otherwise return 0
*/
    bool filename_contain(const std::string_view &filename, const std::string_view &contain)
    {
        return filename.find(contain) != std::string::npos;
    }
}

#endif