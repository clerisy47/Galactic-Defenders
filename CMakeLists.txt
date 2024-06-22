cmake_minimum_required(VERSION 3.10)

project(Invaders)

# Set C++ standard (change as needed)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate raylib package
find_package(raylib 3.5 REQUIRED)

# Add all your source files from src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Add executable target
add_executable(Invaders ${SOURCES} ${HEADERS})

# Set include directory for headers (optional but recommended)
target_include_directories(Invaders PRIVATE src)

# Link raylib library to your project
target_link_libraries(Invaders PRIVATE raylib)