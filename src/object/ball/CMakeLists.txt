set(CMAKE_CXX_STANDARD 20)

add_library(OBJECT_BALL STATIC
        ball.cpp)

target_compile_options(OBJECT_BALL PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(OBJECT_BALL PROPERTIES LINKER_LANGUAGE CXX)

set(OBJECT ${OBJECT} OBJECT_BALL PARENT_SCOPE)