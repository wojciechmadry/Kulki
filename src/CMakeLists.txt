if (CMAKE_BUILD_TYPE MATCHES Debug32 OR CMAKE_BUILD_TYPE MATCHES Release32)
 link_directories(G:/SFML/32bit/lib)
 include_directories(G:/SFML/32bit/include)
elseif(CMAKE_BUILD_TYPE MATCHES Debug64 OR CMAKE_BUILD_TYPE MATCHES Release64)
 include_directories(G:/SFML/64bit/include)
 link_directories(G:/SFML/64bit/lib)
else()
 link_directories(G:/SFML/32bit/lib)
 include_directories(G:/SFML/32bit/include)
 include_directories(G:/SFML/64bit/include)
 link_directories(G:/SFML/64bit/lib)
endif()
set(CMAKE_CXX_STANDARD 20)
add_library(source STATIC
        object/map.hpp
        object/ball.hpp
        babel/babel.hpp
        function/random_generator.hpp
        function/drawer.hpp
        function/load.hpp
        function/crypt.hpp)
target_link_libraries(source PUBLIC gcc)
target_link_libraries(source PUBLIC stdc++.dll)
target_link_libraries(source PUBLIC sfml-window)
target_link_libraries(source PUBLIC sfml-graphics)
target_link_libraries(source PUBLIC sfml-system)
target_link_libraries(source PUBLIC freetype)
set_target_properties(source PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(source PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")