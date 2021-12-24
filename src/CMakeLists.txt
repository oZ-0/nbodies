cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 0.1)

SET(CUSTOM_COMPILE_FLAGS "-O3 -march=native -flto -Wl,-O1 -Wno-comment")

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

    simulation.cpp
    world.cpp
)

target_sources(Nbodies PRIVATE "${SRC}")