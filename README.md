# Raylib+ANGLE CMake Starter for C/C++

This is a starter project for using [Raylib](https://www.raylib.com/) and [ANGLE](https://chromium.googlesource.com/angle/angle) with C/C++ and CMake.
**WARNING: Only tested on MacOS**


## Getting Started

1. Clone this repository
2. Run `./bootstrap`
3. Build `./b`
4. Run `./r`

## Building with Google ANGLE (10x more draw calls on Apple Silicon) (Only tested on MacOS)
### Option 1 - Grab ANGLE dylibs from a Google Chrome installation
1. Grab ANGLE dylibs from Your Google Chrome installation

```
cd /Applications/Google\ Chrome.app
find ./ -name libGLESv2.dylib
find ./ -name libEGL.dylib
```

2. Copy the dylibs to `libs/`

3. Build with ANGLE `./b angle`

4. run with ANGLE `./r angle`

### Option 2 - Build ANGLE locally
***DEPENDENCIES***

* Apple Developer Command Line Tools (xcode) - On MacOS
* Ninja
* CMake
* Python 3
* Git
* depot_tools (gclient)
  
1. Bootstrap ANGLE
   Run `./bootstrap-angle`
   
3. Build with `./build-angle [Number of cores to build with]`
   
5. Copy ANGLE dylibs to libs/ - Run `./cp-angle-dylibs`
