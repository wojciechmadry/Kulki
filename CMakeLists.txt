cmake_minimum_required(VERSION 3.17)
project(Kulki)
set(CMAKE_CXX_STANDARD 20)

if(UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif(UNIX)

find_package(SFML COMPONENTS graphics window system REQUIRED)
find_package(Freetype REQUIRED)

include_directories(
    src/BabelLib
    include
)

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    add_definitions(-D__32BITVERSION__)
else()
    add_definitions(-D__64BITVERSION__)
endif()

add_executable(Kulki
        #WIN32
        main.cpp
        src/function/crypt/crypt.cpp
        src/function/drawer/drawer_utils.cpp
        src/function/drawer/drawer_global_class.cpp
        src/function/drawer/drawer_window.cpp
        src/function/font/search_font_linux.cpp
        src/function/font/search_font_windows.cpp
        src/function/load/load.cpp
        src/function/load/load_map.cpp
        src/function/load/load_record.cpp
        src/function/mouse/mouse_click_event.cpp
        src/function/random/random.cpp
        src/function/tester/tester.cpp
        src/function/thread/thread_wrapper.cpp
        src/object/ball/ball.cpp
        src/object/map/map_check_score.cpp
        src/object/map/map.cpp
        src/object/map/map_move.cpp
        src/object/map/map_next_three.cpp
        src/object/map/map_position_check.cpp
        src/object/map/map_score_there.cpp
        src/object/red_box/red_box.cpp
)

target_compile_options(Kulki PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

if(UNIX)
    target_link_libraries(Kulki PUBLIC Threads::Threads)
endif(UNIX)

target_link_libraries(Kulki PRIVATE
    sfml-window
    sfml-graphics
    sfml-system
    freetype
)

