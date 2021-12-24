cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(Nbodies)

# add the executable
add_executable(Nbodies main.cpp)

set(SRC
    exception.hpp
    vec3.hpp
    simulation.hpp
    solver.hpp
    world.hpp
    globals.hpp

    world.cpp
    globals.cpp
)

target_sources(Nbodies PRIVATE "${SRC}")