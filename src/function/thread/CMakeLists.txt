set(CMAKE_CXX_STANDARD 20)

add_library(FUNCTION_THREAD STATIC
        thread_wrapper.cpp)

target_link_libraries(FUNCTION_THREAD PRIVATE FUNCTION_DRAWER)
target_link_libraries(FUNCTION_THREAD PRIVATE OBJECT_MAP)

target_compile_options(FUNCTION_THREAD PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(FUNCTION_THREAD PROPERTIES LINKER_LANGUAGE CXX)

set(FUNCTION ${FUNCTION} FUNCTION_THREAD PARENT_SCOPE)