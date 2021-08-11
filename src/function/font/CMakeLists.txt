set(CMAKE_CXX_STANDARD 20)

if(UNIX)
    set(SRC_FONT search_font_linux.cpp)
endif(UNIX)

if(WIN32)
    set(SRC_FONT search_font_windows.cpp)
endif(WIN32)

add_library(FUNCTION_FONT STATIC
        ${SRC_FONT}
        )
target_compile_options(FUNCTION_FONT PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(FUNCTION_FONT PROPERTIES LINKER_LANGUAGE CXX)

set(FUNCTION ${FUNCTION} FUNCTION_FONT PARENT_SCOPE)