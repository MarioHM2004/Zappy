cmake_minimum_required(VERSION 3.10)
project(zappy_server)

# Specify the C standard
set(CMAKE_C_STANDARD 11)

# Add subdirectory for the library
add_subdirectory(libs)

# Add the include directory for header files
include_directories(include)

# Add the directory containing liblog.so to the linker search path
link_directories(${PROJECT_SOURCE_DIR}/libs)

# Find all source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Add the executable
add_executable(zappy_server ${SOURCES})

# Set the output directory for binaries
set_target_properties(zappy_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# If there are specific libraries your project depends on, link them here
target_link_libraries(zappy_server ${PROJECT_SOURCE_DIR}/libs/liblog.so)
target_link_libraries(zappy_server my)
