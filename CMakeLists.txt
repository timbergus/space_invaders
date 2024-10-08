cmake_minimum_required(VERSION 3.30.4)
project(space_invaders VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -Werror -Wpedantic)

find_package(fmt REQUIRED)
find_package(raylib REQUIRED)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/apps/*.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/include)

add_executable(space_invaders ${CMAKE_SOURCE_DIR}/src/main.cpp ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
