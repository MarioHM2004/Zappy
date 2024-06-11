file(GLOB_RECURSE SOURCES "src/*.c")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Library configuration
add_library(my STATIC ${SOURCES})
