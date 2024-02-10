cmake_minimum_required(VERSION 3.10)
project(Groth VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for the library
include_directories(include)

# Automatically find all source files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define the library target
add_library(Groth STATIC ${SOURCES})

# Link against Windows Socket Library
if(WIN32)
    target_link_libraries(Groth PRIVATE Ws2_32)
endif()

# Specify installation rules for the library and headers
install(TARGETS Groth DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# Add an example executable
add_subdirectory(examples/SimpleServer)