cmake_minimum_required(VERSION 3.17)
project(Kulki)
set(CMAKE_CXX_STANDARD 20)

if(UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif(UNIX)

include_directories(src)

# Set path to sfml folder
set(SFML_PATH /home/wojtek/Desktop/GIT/SFML-2.5.1/)
set(INCLUDE ${SFML_PATH}/include/)
set(LIB ${SFML_PATH}/lib/)

include_directories(${INCLUDE})
link_directories(${LIB})

add_subdirectory(src)

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    add_definitions(-D__32BITVERSION__)
else()
    add_definitions(-D__64BITVERSION__)
endif()



add_executable(Kulki
        #WIN32
        main.cpp
        )

target_compile_options(Kulki PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

if(UNIX)
    target_link_libraries(Kulki PUBLIC Threads::Threads)
endif(UNIX)

target_link_libraries(Kulki PRIVATE ${LIBRARIES})

