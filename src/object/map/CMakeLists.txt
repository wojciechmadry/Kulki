set(CMAKE_CXX_STANDARD 20)

add_library(OBJECT_MAP STATIC
        map.cpp
        map_move.cpp
        map_score_there.cpp
        map_position_check.cpp
        map_check_score.cpp
        map_next_three.cpp)


target_link_libraries(OBJECT_MAP PRIVATE OBJECT_BALL)

target_compile_options(OBJECT_MAP PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(OBJECT_MAP PROPERTIES LINKER_LANGUAGE CXX)

set(OBJECT ${OBJECT} OBJECT_MAP PARENT_SCOPE)