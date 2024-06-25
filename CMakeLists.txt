cmake_minimum_required(VERSION 3.2)

project(Fractal)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_NAME fractal)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(${EXECUTABLE_NAME} ${SOURCES})

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

target_link_libraries(${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics)

string(APPEND CMAKE_CXX_FLAGS_RELEASE " -Wall -Wextra -Werror -O3")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -Wall -Wextra -Werror -g3")

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../release
)
