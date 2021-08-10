set(CMAKE_CXX_STANDARD 20)


add_library(OBJECT_REDBOX STATIC
        red_box.cpp)

target_compile_options(OBJECT_REDBOX PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(OBJECT_REDBOX PROPERTIES LINKER_LANGUAGE CXX)

set(OBJECT ${OBJECT} OBJECT_REDBOX PARENT_SCOPE)