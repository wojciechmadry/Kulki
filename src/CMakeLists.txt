set(CMAKE_CXX_STANDARD 20)

# --- no diffrence ---
add_subdirectory(function/crypt)
add_subdirectory(function/font)
add_subdirectory(object/ball)
# ---------------------


add_subdirectory(object/map)
add_subdirectory(object/red_box)

add_subdirectory(function/load)
add_subdirectory(function/drawer)

add_subdirectory(function/thread)
add_subdirectory(function/mouse)
add_subdirectory(function/tester)

set(LIBRARIES
        ${OBJECT}
        ${FUNCTION}
        stdc++
        sfml-window
        sfml-graphics
        sfml-system
        freetype
        PARENT_SCOPE)
