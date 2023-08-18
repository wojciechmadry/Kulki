License
---
Game is on SFML licens:
https://www.sfml-dev.org/license.php

Requirements
---
1. CMake
2. C++20 (GCC or Clang)
3. `libsfml-dev`

Build from source
---

1. Init submodule
```sh
git submodule init
git submodule update
```

3. Build project with CMake:
```sh
mkdir build
cd build
cmake ..
make -j
```

Build Dockerimage
---
```sh
docker build -t kulki .
```

Screen from game
---
![alt text](https://github.com/wojciechmadry/Kulki/blob/master/Screen/game1.PNG)
![alt text](https://github.com/wojciechmadry/Kulki/blob/master/Screen/game2.PNG)
