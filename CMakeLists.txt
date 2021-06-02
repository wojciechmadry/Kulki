cmake_minimum_required(VERSION 3.17)
project(Kulki)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    add_definitions(-D__32BITVERSION__)
    include_directories(F:/SFML/32bit/include) # Link to 32 bit sfml
    link_directories(F:/SFML/32bit/lib)
else()
    add_definitions(-D__64BITVERSION__)
    include_directories(F:/SFML/64bit/include) # Link to 64 bit sfml
    link_directories(F:/SFML/64bit/lib)
endif()




add_executable(Kulki
        #WIN32
        main.cpp
        )

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    target_compile_options(Kulki PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)
endif()

target_link_libraries(Kulki PRIVATE source)
