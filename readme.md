License
---
Game is on SFML licens:
https://www.sfml-dev.org/license.php

Requirements
---
1. CMake
2. C++20 (GCC or Clang)
3. [MSYS2](https://www.msys2.org/) (**Windows only**)
4. `libsfml-dev`

Build from source
---

1. Init submodule
```sh
git submodule init
git submodule update
```

2. If you want hide console after you build this project uncomment `WIN32` in `CMakeList.txt` - **Windows only**

3. Change `set(SFML_PATH /home/wojtek/Desktop/GIT/SFML-2.5.1/)` in `CMakeLists.txt` to your sfml folder - **Windows only**

4. Build project with CMake (Generator can be `ninja`, `MinGW Makefiles`:
```sh
mkdir build
cd build
cmake -G<generator> ..
make -j
```

5. Copy libraries from SFML `bin` folder to build directory
   All needed library in: `sfml-graphics-2.dll`, `sfml-system-2.dll`, `sfml-window-2.dll` - **Windows only**

Screen from game
---
![alt text](https://github.com/wojciechmadry/Kulki/blob/master/Screen/game1.PNG)
![alt text](https://github.com/wojciechmadry/Kulki/blob/master/Screen/game2.PNG)
