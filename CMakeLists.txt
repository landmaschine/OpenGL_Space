cmake_minimum_required(VERSION 3.28.0)
project(Space)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_definitions(-DGLFW_INCLUDE_NONE)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/src/*.cpp" "${SOURCE_DIR}/Engine/*.cpp" "${SOURCE_DIR}/lib/*.cpp" "${SOURCE_DIR}/lib/*.c")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Engine")

add_executable(Space ${SOURCE_FILES})

target_link_libraries(Space PRIVATE glfw ${OPENGL_LIBRARIES})

target_include_directories(Space PRIVATE "${OPENGL_INCLUDE_DIR}")

target_compile_options(Space PRIVATE "-Wall" "-pedantic" "-O0" "-fstrict-aliasing")
