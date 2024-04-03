cmake_minimum_required(VERSION 3.24)
project(VoxelIO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(OpenGL REQUIRED)

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

if(APPLE)
  set(LIBS glfw3 "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
  set(LIBS ${LIBS} glfw3)
endif()

find_package(assimp REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIRS}")

add_library(GLAD "glad.c" include/KHR/khrplatform.h)
set(LIBS ${LIBS} GLAD)


include_directories(${PROJECT_SOURCE_DIR}/core)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${ASSIMP_INCLUDE_DIRS})



message(STATUS "Included all libraries")

add_definitions(-D_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

add_subdirectory(app)
add_subdirectory(core)

