cmake_minimum_required(VERSION 3.10)

project(SearchTreeProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(SearchTreeProject 
    src/main.cpp 
    src/Node.cpp 
    src/SearchAlgorithms.cpp 
    src/Visualizer.cpp
)
