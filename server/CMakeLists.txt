cmake_minimum_required(VERSION 3.10)
project(zappy_server)

# Specify the C standard
set(CMAKE_C_STANDARD 11)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the directory containing liblog.so to the linker search path
link_directories(${PROJECT_SOURCE_DIR}/libs)

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Add the executable
add_executable(zappy_server ${SOURCES})

# Link the liblog shared library
target_link_libraries(zappy_server ${PROJECT_SOURCE_DIR}/libs/liblog.so)
