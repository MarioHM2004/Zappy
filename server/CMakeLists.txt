cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(ZappyServer VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the include directory for header files
include_directories(include)

# Add the source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Add the executable target
add_executable(zappy_server ${SOURCES})

# Set the output directory for binaries
set_target_properties(zappy_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# If there are specific libraries your project depends on, link them here
# target_link_libraries(zappy_server <library_name>)
