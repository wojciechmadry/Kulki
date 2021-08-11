set(CMAKE_CXX_STANDARD 20)

add_library(FUNCTION_RANDOM STATIC
        random.cpp)

target_compile_options(FUNCTION_RANDOM PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(FUNCTION_RANDOM PROPERTIES LINKER_LANGUAGE CXX)

set(FUNCTION ${FUNCTION} FUNCTION_RANDOM PARENT_SCOPE)