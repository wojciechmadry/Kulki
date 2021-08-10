set(CMAKE_CXX_STANDARD 20)

add_library(FUNCTION_MOUSE STATIC
        mouse_click_event.cpp)

target_link_libraries(FUNCTION_LOAD PRIVATE FUNCTION_MOUSE)

target_link_libraries(FUNCTION_LOAD PRIVATE FUNCTION_THREAD)

target_compile_options(FUNCTION_THREAD PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(FUNCTION_THREAD PROPERTIES LINKER_LANGUAGE CXX)

set(FUNCTION ${FUNCTION} FUNCTION_MOUSE PARENT_SCOPE)