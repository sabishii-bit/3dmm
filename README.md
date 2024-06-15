# Simple 3D Model Maker

Made as a fun little assignment for myself. Might continue support, might not, who knows.

### Requirements

- vcpkg
- CMake
- C++17 compiler

### Installing Dependencies and Building

Ensure vcpkg is added to your system's PATH variables, then run the install command in the root of the project where the manifest file (vcpkg.json) is located:

```
vcpkg install
```

Ensure VCPKG_ROOT and VCPKG_DEFAULT_TRIPLET environment variables are set:

```
# Windows
set VCPKG_ROOT=C:\path\to\vcpkg
set VCPKG_DEFAULT_TRIPLET=x64-windows

# Linux
export VCPKG_ROOT=/path/to/vcpkg
export VCPKG_DEFAULT_TRIPLET=x64-linux

# macOS
export VCPKG_ROOT=/path/to/vcpkg
export VCPKG_DEFAULT_TRIPLET=x64-osx
```

Generate build directory and build files using CMake, and then build the project:
```
mkdir build
cd build
cmake ..
cmake --build .
```

### Usage

Hold left-mouse click and navigate the screen with WASD.
'T' toggles wireframe mode.
Click on objects you create to transform their matrices in the toolbar.