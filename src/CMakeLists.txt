set(CMAKE_CXX_STANDARD 20)
add_library(source STATIC
        object/map.hpp
        object/ball.hpp
        babel/babel.hpp
        function/random_generator.hpp
        function/drawer.hpp
        function/load.hpp
        function/crypt.hpp
        function/search_font.hpp
        )

target_link_libraries(source PUBLIC gcc)
target_link_libraries(source PUBLIC stdc++.dll)
target_link_libraries(source PUBLIC sfml-window)
target_link_libraries(source PUBLIC sfml-graphics)
target_link_libraries(source PUBLIC sfml-system)
target_link_libraries(source PUBLIC freetype)
set_target_properties(source PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(source PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")