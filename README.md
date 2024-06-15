# Simple 3D Model Maker

Made as a fun little assignment for myself. Might continue support, might not, who knows.

### Requirements

vcpkg, CMake, C++17 compiler

### Installing Dependencies and Building

Ensure vcpkg is added to your system's PATH variables, then run the install command in the root of the project where the manifest file (vcpkg.json) is located:

```
vcpkg install
```

Ensure VCPKG_ROOT enviornment variable is set:

```
# Windows
set VCPKG_ROOT=C:\path\to\vcpkg

# Linux/MacOS
export VCPKG_ROOT=/path/to/vcpkg
```

Generate build directory and build files using CMake and building:
```
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

### Usage

Hold left-mouse click and navigate the screen with WASD.
'T' toggles wireframe mode.
Click on objects you create to transform their matrices in the toolbar.