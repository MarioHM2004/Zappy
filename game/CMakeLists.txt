cmake_minimum_required(VERSION 3.20)
project(zappy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(WIN32)
    set(OS "WINDOWS")
elseif(APPLE)
    set(OS "MACOS")
elseif(UNIX AND NOT APPLE)
    set(OS "LINUX")
endif()

set(SERVER_SRC "${CMAKE_SOURCE_DIR}/source/Server.cpp")
set(GODOT_LIB "${CMAKE_SOURCE_DIR}/library/godot-cpp")

add_executable(server ${SERVER_SRC})

file(GLOB GDEXTS_SRC "${CMAKE_SOURCE_DIR}/source/*.cpp")
list(REMOVE_ITEM GDEXTS_SRC ${SERVER_SRC})

add_library(zappy SHARED ${GDEXTS_SRC})

set_target_properties(zappy PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/zappy/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/zappy/bin"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/zappy/bin"
)

file(GLOB GODOT_CPP_LIBRARY_PATH "${GODOT_LIB}/bin/libgodot-cpp*")

if(NOT GODOT_CPP_LIBRARY_PATH)
    message(STATUS "godot-cpp library not found, building it")
    execute_process(
        COMMAND scons platform=${OS}
        WORKING_DIRECTORY "${GODOT_LIB}"
    )
    file(GLOB GODOT_CPP_LIBRARY_PATH "${GODOT_LIB}/bin/libgodot-cpp*")
endif()

if(GODOT_CPP_LIBRARY_PATH)
    message(STATUS "Found godot-cpp library: ${GODOT_CPP_LIBRARY_PATH}")
    target_link_libraries(zappy PRIVATE ${GODOT_CPP_LIBRARY_PATH})
else()
    message(FATAL_ERROR "godot-cpp library not found in ${GODOT_LIB}/bin")
endif()

target_include_directories(zappy PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(zappy PUBLIC "${GODOT_LIB}/include")
target_include_directories(zappy PUBLIC "${GODOT_LIB}/gen/include")
target_include_directories(zappy PUBLIC "${GODOT_LIB}/gdextension")
