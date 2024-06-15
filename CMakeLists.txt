cmake_minimum_required(VERSION 3.15)

# Set the vcpkg toolchain file before the project command
if(DEFINED ENV{VCPKG_ROOT})
    set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
else()
    message(FATAL_ERROR "VCPKG_ROOT is not set. Please set it to the vcpkg installation directory.")
endif()

# Ensure VCPKG_DEFAULT_TRIPLET is set
if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
    set(VCPKG_TARGET_TRIPLET $ENV{VCPKG_DEFAULT_TRIPLET})
else()
    message(FATAL_ERROR "VCPKG_DEFAULT_TRIPLET is not set. Please set it to the appropriate triplet (e.g., x64-windows, x64-linux, x64-osx).")
endif()

project(3dmm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files from src/cpp and header files from src/h
file(GLOB_RECURSE SOURCES src/cpp/*.cpp src/imgui_backends/*.cpp)
file(GLOB_RECURSE HEADERS src/h/*.h src/imgui_backends/*.h)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Find and link libraries using vcpkg context
find_package(glm CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src/h)
target_include_directories(${PROJECT_NAME} PRIVATE src/imgui_backends)
target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}/include)

# Link libraries to the target
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm-header-only GLEW::GLEW glfw imgui::imgui)
