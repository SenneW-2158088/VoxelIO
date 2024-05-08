cmake_minimum_required(VERSION 3.24)
project(VoxelIO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(OpenGL REQUIRED)

# find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

find_package(ALSA REQUIRED)
if (ALSA_FOUND)
    include_directories(${ALSA_INCLUDE_DIRS})
endif()

if(APPLE)
  set(LIBS glfw3 "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
else()
  set(LIBS ${LIBS} glfw)
endif()

find_package(assimp REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIRS}")

add_library(GLAD "glad.c" include/KHR/khrplatform.h)
set(LIBS ${LIBS} GLAD)

set(IRRKLANG_LIBRARY ikpMP3.so)
set(IRRKLANG_LIBRARY libIrrKlang.so)

add_library(irrKlang STATIC IMPORTED)
set_property(TARGET irrKlang PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/irrKlang/libIrrKlang.so)



include_directories(${CMAKE_SOURCE_DIR}/include/irrKlang)
include_directories(${PROJECT_SOURCE_DIR}/core)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${ASSIMP_INCLUDE_DIRS})

link_directories(${CMAKE_SOURCE_DIR}/lib/irrKlang)
link_directories(/usr/lib /usr/local/lib)

message(STATUS "Included all libraries")

add_definitions(-D_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

add_subdirectory(app)
add_subdirectory(core)

