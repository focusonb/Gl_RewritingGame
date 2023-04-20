cmake_minimum_required(VERSION 3.14.0)

project(GLRewritingGame)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)

add_definitions(-DPLATFORM_WINDOWS=1)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/Glad/include/glad)

include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/glfw-3.3.4/include/GLFW)
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/glm)
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/Glad/include)

file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "src/*.c")


link_directories(${CMAKE_SOURCE_DIR}/ThirdParty/lib/libglfw)
add_executable(GLRewritingGame ${SRC_DIR_LIST})




