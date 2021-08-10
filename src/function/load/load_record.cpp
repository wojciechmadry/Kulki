#include "load.hpp"
#include <filesystem>
#include "babel/babel.hpp"
#include "function/crypt/crypt.hpp"

void save_record(uint16_t new_record)
{
    std::ofstream f("kulki.bin");
    if ( !( f.is_open() && f.good() ) )
        throw std::out_of_range("Cant open kulki.bin");
    f << crypt(new_record);
    babel::FILE_SYS::close_file(f);
}

uint16_t check_for_record()
{
    namespace fs = std::filesystem;
    const std::string FileName = "kulki.bin";

    if ( !fs::exists(FileName) )
    {
        std::ofstream f(FileName);
        f << crypt(0);
        babel::FILE_SYS::close_file(f);
    }
    std::ifstream file(FileName);
    if ( !file.is_open() )
        throw std::out_of_range("Cant open " + FileName);
    uint16_t decoded;
    try
    {
        std::string line;
        std::getline(file, line);
        decoded = decrypt(line);
        babel::FILE_SYS::close_file(file);
    }
    catch ( ... )
    {
        babel::FILE_SYS::close_file(file);
        std::ofstream f(FileName);
        f << crypt(0);
        decoded = 0;
        babel::FILE_SYS::close_file(f);
    }

    return decoded;
}