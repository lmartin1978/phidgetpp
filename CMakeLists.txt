cmake_minimum_required(VERSION 3.5)

# set the project name and version
project(phidgetpp VERSION 0.2)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC
    "src/*.cc"
)

add_library(phidgetpp ${SRC})
target_include_directories(phidgetpp PUBLIC include)
target_link_libraries(phidgetpp PUBLIC phidget22)
