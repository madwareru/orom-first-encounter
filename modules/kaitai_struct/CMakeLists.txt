project (kaitai_struct_cpp_stl_runtime CXX)
cmake_minimum_required (VERSION 3.10)

set (CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(ZLIB)

set (KAITAI_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/kaitai
)

file(GLOB_RECURSE KAITAI_SOURCES kaitai/*.*)

set (SOURCES
    kaitai/kaitaistream.cpp
)

add_library(${PROJECT_NAME} STATIC ${KAITAI_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
    ${KAITAI_INCLUDE_DIRS}
)
