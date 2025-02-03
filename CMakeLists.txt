cmake_minimum_required(VERSION 3.15)
project(PhysicsSimulator)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics system window) 

set(CMAKE_CXX_STANDARD 14)  # Use C++14 or higher

add_executable(PhysicsSimulator main.cpp shapes/Point.cpp shapes/Line.cpp)

target_link_libraries(PhysicsSimulator sfml-graphics sfml-system sfml-window) # Order matters for some systems
