License
---
Game is on SFML licens:
https://www.sfml-dev.org/license.php

General information
---

Screen from game are in folder _Screen_.

All nedeed source files are in folder _src_.

Working version
--- 

In this moment only working builded version
is 64 bit, if you want 32 bit you need compile project with cmake by your own.

How to compile
---

I build project with Mingw32.
You need Cmake install too.

Project requires C++20 (I use Clang 11.0)

First you need change CMakeLists.


If you want hide console after you build this project uncomment `WIN32`

If you compile on 32 bit system you add this definition:

`add_definitions(-D__32BITVERSION__)`

If you compile on 64 bit system you add this definition:

`add_definitions(-D__64BITVERSION__)`


Now you set path to header files SFML:  

`include_directories(F:/SFML/64bit/include)`

Now set path to all static SFML library:

`link_directories(F:/SFML/64bit/lib)`

Every file you need to build project:

`folder - ball_texture`
`folder - src`
`folder - Build`(in this folder you build your project)

`file - CMakeLists.txt`
`file - main.cpp`
`font - arial.ttf`

Now open console in folder Build and type:
`cmake -g`

Now you see available generator, I pick: `MinGW Makefiles`

Now type `cmake -G 'MinGW Makefiles' ../` to generate project.

To build your project type `cmake --build .`

When your build you project copy font `arial.ttf` to your build project.

Now only to you need to do: copy libraries from SFML folder`../bin`

All needed library: `sfml-graphics-2.dll`, `sfml-system-2.dll`, `sfml-window-2.dll`

If you want to move your build project from folder remember to put folder `ball_texture` therein.



Screen from game
---
![alt text](https://gitlab.com/woitys1999/kulki/-/raw/master/Screen/game1.PNG)
![alt text](https://gitlab.com/woitys1999/kulki/-/raw/master/Screen/game2.PNG)
