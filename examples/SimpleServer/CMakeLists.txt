cmake_minimum_required(VERSION 3.10)
project(SimpleServer)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(SimpleServer main.cpp MyController.cpp)
target_link_libraries(SimpleServer PRIVATE Groth)