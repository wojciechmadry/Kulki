set(CMAKE_CXX_STANDARD 20)

add_library(FUNCTION_LOAD STATIC
        load.cpp
        load_map.cpp
        load_record.cpp)

target_link_libraries(FUNCTION_LOAD PRIVATE FUNCTION_CRYPT)
target_link_libraries(FUNCTION_LOAD PRIVATE OBJECT_MAP)

target_compile_options(FUNCTION_LOAD PRIVATE -O3 -Wextra -Werror -W -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -fno-common -Wconversion -pedantic -Wall)

set_target_properties(FUNCTION_LOAD PROPERTIES LINKER_LANGUAGE CXX)

set(FUNCTION ${FUNCTION} FUNCTION_LOAD PARENT_SCOPE)