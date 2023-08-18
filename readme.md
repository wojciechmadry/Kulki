License
---
Game is on SFML licens:
https://www.sfml-dev.org/license.php

General information
---

Screen from game are in folder _Screen_.

All nedeed source files are in folder _src_.

Requirements
---
1. CMake
2. C++20
3. Mingw32 (When building on Windows)

Build from source
---

1. Init submodule
```sh
git submodule init
git submodule update
```

2. If you want hide console after you build this project uncomment `WIN32` in `CMakeList.txt` - **Windows only**

3. Build project with CMake (Generator can be `ninja`, `MinGW Makefiles`:
```sh
mkdir build
cd build
cmake -G<generator> ..
make -j
```

4. Copy libraries from SFML `bin` folder to build directory
   All needed library in **WINDOWS**: `sfml-graphics-2.dll`, `sfml-system-2.dll`, `sfml-window-2.dll`

Screen from game
---
![alt text](https://github.com/wojciechmadry/Kulki/blob/master/Screen/game1.PNG)
![alt text](https://github.com/wojciechmadry/Kulki/blob/master/Screen/game2.PNG)
