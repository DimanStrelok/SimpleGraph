cmake_minimum_required(VERSION 3.9)

set(NAME SimpleGraph) #Project name

project(${NAME})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Wall -Wextra -Wshadow -march=native")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")

set(HEADER_FILES Node.h Graph.h)
set(SOURCE_FILES Node.cpp Graph.cpp main.cpp)
set(PROJECT_FILES ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${NAME} ${PROJECT_FILES})