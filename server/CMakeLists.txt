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

add_compile_options(-g3 -DLOG_USE_COLOR)

# Add the executable
add_executable(zappy_server ${SOURCES})

# Set the output directory for binaries
set_target_properties(zappy_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Link the libraries
file(GLOB LOG_SOURCES "${CMAKE_SOURCE_DIR}/libs/log/src/*.c")

# Create a shared library for log
add_library(log SHARED ${LOG_SOURCES})

# Add the include directory for log
target_include_directories(log PRIVATE libs/log/include)

# Link the log library
target_link_libraries(zappy_server log my)

# if its a mac, link the argp library
if(APPLE)
    target_link_libraries(zappy_server argp)
endif()
