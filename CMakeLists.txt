cmake_minimum_required(VERSION 3.17)
project(Kulki)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)

if (CMAKE_BUILD_TYPE MATCHES Debug32 OR CMAKE_BUILD_TYPE MATCHES Release32)
    add_definitions(-D__32BITVERSION__)
    link_directories(G:/SFML/32bit/lib)
    include_directories(G:/SFML/32bit/include)
    elseif(CMAKE_BUILD_TYPE MATCHES Debug64 OR CMAKE_BUILD_TYPE MATCHES Release64)
    add_definitions(-D__64BITVERSION__)
    include_directories(G:/SFML/64bit/include)
    link_directories(G:/SFML/64bit/lib)
    else()
    link_directories(G:/SFML/32bit/lib)
    include_directories(G:/SFML/32bit/include)
    include_directories(G:/SFML/64bit/include)
    link_directories(G:/SFML/64bit/lib)
endif()
add_executable(Kulki
        #WIN32
        main.cpp
        )
target_link_libraries(Kulki PRIVATE source)
