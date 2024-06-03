cmake_minimum_required(VERSION 3.20)
project(zappy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(SOURCES "source/main.cpp")
set(SERVER_SRC "source/Server.cpp")

add_executable(zappy ${SOURCES})
add_executable(server ${SERVER_SRC})

target_include_directories(zappy PUBLIC "include")
target_include_directories(zappy PUBLIC "library/godot-cpp/include")
target_include_directories(zappy PUBLIC "library/godot-cpp/gen/include")
target_include_directories(zappy PUBLIC "library/godot-cpp/gdextension")

if (WIN32)
    set(ARCH_TARGET "windows")
elseif (APPLE)
    set(ARCH_TARGET "macos")
elseif (UNIX)
    set(ARCH_TARGET "linux")
endif()

add_custom_target(generate_bindings
    COMMAND scons platform=${ARCH_TARGET}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating bindings"
)
