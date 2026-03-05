
# How to build

## 1. Build the project with cmake:

``` bash
cmake -DCMAKE_BUILD_TYPE:STRING=<Debug/Release> -S . -B ./build
```
* Debug: built files are created on `./build/SpaceInvaders/Debug/`
* Release: build files are created on `./build/SpaceInvaders/Release/`

## 2. Build the game:

``` bash
cmake --build build
```

## 3. Run the game:

```bash
./build/SpaceInvaders/<Debug/Release>/SpaceInvaders.exe
```