cmake_minimum_required(VERSION 3.17)
project(Kulki)
set(CMAKE_CXX_STANDARD 20)

if(UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif(UNIX)

add_subdirectory(SFML)

include_directories(
    src/BabelLib
    include
)

file(GLOB_RECURSE SRC_FILES src/function/*.cpp src/object/*.cpp)
file(GLOB_RECURSE HEADERS_FILES include/*.hpp include/*.h)

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    add_definitions(-D__32BITVERSION__)
else()
    add_definitions(-D__64BITVERSION__)
endif()

add_executable(Kulki
        main.cpp
        ${SRC_FILES}
)

target_compile_options(Kulki PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

if(UNIX)
    target_link_libraries(Kulki PUBLIC Threads::Threads)
endif(UNIX)

target_link_libraries(Kulki PRIVATE
    sfml-window
    sfml-graphics
    sfml-system
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/ball_texture
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/font
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

 add_custom_target(
    clangformat
    COMMAND /usr/bin/clang-format
    -i
    ${SRC_FILES}
    ${HEADERS_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

