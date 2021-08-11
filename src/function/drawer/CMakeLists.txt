set(CMAKE_CXX_STANDARD 20)

add_library(FUNCTION_DRAWER STATIC
        drawer_utils.cpp
        drawer_global_class.cpp
        drawer_window.cpp)

target_link_libraries(FUNCTION_DRAWER PRIVATE OBJECT_MAP)
target_link_libraries(FUNCTION_DRAWER PRIVATE FUNCTION_LOAD)

target_compile_options(FUNCTION_DRAWER PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(FUNCTION_DRAWER PROPERTIES LINKER_LANGUAGE CXX)

set(FUNCTION ${FUNCTION} FUNCTION_DRAWER PARENT_SCOPE)