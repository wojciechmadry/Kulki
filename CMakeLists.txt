cmake_minimum_required(VERSION 3.17)
project(Kulki)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)

#add_definitions(-D__32BITVERSION__)
add_definitions(-D__64BITVERSION__)


include_directories(F:/SFML/64bit/include)
link_directories(F:/SFML/64bit/lib)

add_executable(Kulki
        #WIN32
        main.cpp
        )
target_compile_options(Kulki PRIVATE -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)
target_link_libraries(Kulki PRIVATE source)
