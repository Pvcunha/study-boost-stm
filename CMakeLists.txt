cmake_minimum_required( VERSION 3.8 )
project(sim_2d_sm)

set( CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system filesystem REQUIRED)

set( SOURCE_FILES src/main.cpp)

add_executable( test ${SOURCE_FILES} )