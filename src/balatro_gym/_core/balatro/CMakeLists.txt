cmake_minimum_required(VERSION 3.10)
project(balatro CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(BALATRO_SOURCES 
    "src/main.cpp"
    "src/hand.cpp"
    "src/gamestate.cpp"
    "src/score.cpp"
)

# Header files
set(BALATRO_HEADERS
    "src/types.hpp"
    "src/io.hpp"
    "src/hand.hpp"
    "src/gamestate.hpp"
    "src/score.hpp"
)

# Compiler flags
if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
endif()

# Add library
add_library(balatro STATIC ${BALATRO_SOURCES})

# Include directories
target_include_directories(balatro PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set public headers
set_target_properties(balatro PROPERTIES PUBLIC_HEADER "${BALATRO_HEADERS}")

# Link libraries
target_link_libraries(balatro)
