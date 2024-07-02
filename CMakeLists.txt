cmake_minimum_required(VERSION 3.24)

project(Fractal)
set(EXECUTABLE "fractal")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

include_directories(include)

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE CUDA_SOURCES "src/*.cu")

include(CheckLanguage)
check_language(CUDA)

# set(CMAKE_CUDA_COMPILER OFF)

# Check if CUDA is available on the current platform
if(CMAKE_CUDA_COMPILER AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    enable_language(CUDA)

    if(NOT DEFINED CMAKE_CUDA_STANDARD)
        set(CMAKE_CUDA_STANDARD 11)
        set(CMAKE_CUDA_STANDARD_REQUIRED True)
    endif()

    add_executable(${EXECUTABLE} ${CPP_SOURCES} ${CUDA_SOURCES})

    set_target_properties(${EXECUTABLE}
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_ARCHITECTURES native
    )

    add_definitions(-DCUDA_AVAILABLE)
else()
    if (CMAKE_CUDA_COMPILER)
        message(STATUS "Cmake minimum version required for CUDA support is 3.24.")
        message(STATUS "CMake version: ${CMAKE_VERSION}")
        message(STATUS "Compiling without CUDA support.")
    else()
        message(STATUS "CUDA not found. Compiling without CUDA support.")
    endif()

    add_executable(${EXECUTABLE} ${CPP_SOURCES})
endif()

target_link_libraries(${EXECUTABLE} PRIVATE sfml-system sfml-window sfml-graphics)

target_compile_options(${EXECUTABLE} PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-g3>
)

set_target_properties(${EXECUTABLE}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../release
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../debug
)
