set(CMAKE_CXX_STANDARD 20)

add_library(FUNCTION_TESTER STATIC
        tester.cpp)

target_link_libraries(FUNCTION_TESTER PRIVATE FUNCTION_DRAWER)

target_compile_options(FUNCTION_TESTER PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(FUNCTION_TESTER PROPERTIES LINKER_LANGUAGE CXX)

set(FUNCTION ${FUNCTION} FUNCTION_TESTER PARENT_SCOPE)