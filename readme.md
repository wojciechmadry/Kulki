License
---
Game is on SFML licens:
https://www.sfml-dev.org/license.php

General information
---

Screen from game are in folder _Screen_.

All nedeed source files are in folder _src_.

Submodules
---

- babellib [`https://github.com/wojciechmadry/BabelLib`]

How to compile
---

First initialise submodule - `git submodule init && git submodule update`

You can build project in linux or in windows with Mingw32.

You need Cmake install too.

Project requires C++20 (gcc10 or clang10)

First you need change CMakeLists.

If you want hide console after you build this project uncomment `WIN32` - Windows only

Set path to SFML folder: (https://github.com/wojciechmadry/BabelLib.git)

`set(SFML_PATH /home/wojtek/Pulpit/GIT/SFML-2.5.1/)`

# BUILD

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


If you want to move your build project from folder remember to put folder `ball_texture` therein.



Screen from game
---
![alt text](https://github.com/wojciechmadry/Kulki/blob/master/Screen/game1.PNG)
![alt text](https://github.com/wojciechmadry/Kulki/blob/master/Screen/game2.PNG)
