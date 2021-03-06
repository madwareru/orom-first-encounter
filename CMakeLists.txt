cmake_minimum_required(VERSION 3.10)

project(orom-first-encounter VERSION 1.0)

include(LinkingHelper/link_runtime_static.cmake)
link_runtime_static()

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.rc")
file(GLOB_RECURSE THIRD_PARTY_SOURCES
    "third_party/*.cpp"
    "third_party/*.h")

set (INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_STATIC ON CACHE BOOL "" FORCE)
add_subdirectory(modules/glew-cmake)

set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(modules/glfw)
add_subdirectory(modules/kaitai_struct)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${THIRD_PARTY_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
    include
    modules/promise.hpp/headers
    modules/ecs.hpp/headers)

target_link_libraries(${PROJECT_NAME}
    glfw
    libglew_static
    kaitai_struct_cpp_stl_runtime)

set_target_properties(${PROJECT_NAME} PROPERTIES
         CXX_STANDARD 17
         CXX_STANDARD_REQUIRED YES
         CXX_EXTENSIONS NO)
