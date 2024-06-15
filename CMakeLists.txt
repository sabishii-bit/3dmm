cmake_minimum_required(VERSION 3.15)

# Set the vcpkg toolchain file before the project command
if(NOT DEFINED VCPKG_ROOT)
    message(FATAL_ERROR "VCPKG_ROOT is not set. Please set it to the vcpkg installation directory.")
endif()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(3dmm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files from src/cpp and header files from src/h
file(GLOB_RECURSE SOURCES src/cpp/*.cpp)
file(GLOB_RECURSE HEADERS src/h/*.h)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Find and link libraries using vcpkg context
find_package(glm CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Link libraries to the target
target_link_libraries(${PROJECT_NAME} PRIVATE glm GLEW::GLEW glfw imgui::imgui)

# Include directories (if needed)
target_include_directories(${PROJECT_NAME} PRIVATE src/h)
