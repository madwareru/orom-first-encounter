cmake_minimum_required(VERSION 3.10)

project(orom-first-encounter VERSION 1.0)
include(LinkingHelper/link_runtime_static.cmake)
link_runtime_static()

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
    "src/*.rc")
file(GLOB_RECURSE THIRD_PARTY_SOURCES
    "third_party/*.cpp"
    "third_party/*.h")

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(modules/glfw)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${THIRD_PARTY_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)
set_target_properties(${PROJECT_NAME} PROPERTIES
         CXX_STANDARD 17
         CXX_STANDARD_REQUIRED YES
         CXX_EXTENSIONS NO)
