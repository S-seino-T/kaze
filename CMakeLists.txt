cmake_minimum_required(VERSION 3.20)

project(kz VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Build type: Debug → debug.cpp を使用")
    add_executable(kz debug.cpp ${SOURCES})
    target_include_directories(kz PRIVATE ${CMAKE_SOURCE_DIR}/src)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Build type: Release → main.cpp を使用")
    add_executable(kz main.cpp ${SOURCES})
    target_include_directories(kz PRIVATE ${CMAKE_SOURCE_DIR}/src)
else()
    message(STATUS "Build type: ${CMAKE_BUILD_TYPE} → デフォルト(main.cpp)を使用")
    add_executable(kz main.cpp ${SOURCES})
    target_include_directories(kz PRIVATE ${CMAKE_SOURCE_DIR}/src)
endif()