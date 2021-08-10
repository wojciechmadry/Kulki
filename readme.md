License
---
Game is on SFML licens:
https://www.sfml-dev.org/license.php

General information
---

Screen from game are in folder _Screen_.

All nedeed source files are in folder _src_.

How to compile
---

You can build project in linux or in windows with Mingw32.

You need Cmake install too.

Project requires C++20 (gcc10 or clang10)

First you need change CMakeLists.


(Only in WINDOWS)
If you want hide console after you build this project uncomment `WIN32`

Set path to header files SFML:

`set(INCLUDE /home/wojtek/SFML-2.5.1/include/)` to sfml headers.

Now set path to all static SFML library:

`set(LIB /home/wojtek/SFML-2.5.1/lib/)` to sfml lib.
#BUILD

Open console in folder `Build` and

### WINDOWS BUILD
 type:
`cmake -g`

Now you see available generator, I pick: `MinGW Makefiles`

Now type `cmake -G 'MinGW Makefiles' ../` to generate project.
### LINUX BUILD
type: `cmake ../`

### LINUX & WINDOWS

To build your project type `cmake --build .`

Now only to you need to do: copy libraries from SFML folder`../bin`

All needed library in `WINDOWS`: `sfml-graphics-2.dll`, `sfml-system-2.dll`, `sfml-window-2.dll`

All needed library in `LINUX`: `TODO`


If you want to move your build project from folder remember to put folder `ball_texture` therein.



Screen from game
---
![alt text](https://gitlab.com/woitys1999/kulki/-/raw/master/Screen/game1.PNG)
![alt text](https://gitlab.com/woitys1999/kulki/-/raw/master/Screen/game2.PNG)
