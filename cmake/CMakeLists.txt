cmake_minimum_required (VERSION 3.0.2)

set(TRIANGLE_LIBRARY_TYPE "STATIC")

add_compile_options(-std=c++11)

project(triangle)

include_directories (${PROJECT_SOURCE_DIR}/../include)


file(GLOB_RECURSE TRIANGLE_INCLUDE_FILES "${PROJECT_SOURCE_DIR}/../include/*")

file(GLOB_RECURSE TRIANGLE_SRC_FILES "${PROJECT_SOURCE_DIR}/../src/*")

add_library("triangle" 
    ${TRIANGLE_LIBRARY_TYPE}
    ${TRIANGLE_INCLUDE_FILES}
    ${TRIANGLE_SRC_FILES})

add_executable("Main" WIN32 ${PROJECT_SOURCE_DIR}/../win/main.cpp)

target_link_libraries("Main" "triangle" d3d11 d3dcompiler Opengl32)
