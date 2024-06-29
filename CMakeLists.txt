cmake_minimum_required(VERSION 3.10)

project(Fractal LANGUAGES C CXX CUDA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

include_directories(include)

file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE CUDA_SOURCES "src/*.cu")

add_library(CPP_OBJECTS OBJECT ${CPP_SOURCES})

find_package(CUDA REQUIRED)

if(CUDA_FOUND AND CUDA_VERSION VERSION_GREATER_EQUAL "12.5")
    message(STATUS "CUDA found: ${CUDA_VERSION}")

    add_definitions(-DCUDA_AVAILABLE)

    cuda_select_nvcc_arch_flags(CUDA_ARCH_FLAGS)
    list(APPEND CUDA_NVCC_FLAGS ${CUDA_ARCH_FLAGS})

    list(APPEND CUDA_NVCC_FLAGS " -dc")

    include_directories(${CUDA_INCLUDE_DIRS})

    cuda_compile(CUDA_OBJECTS ${CUDA_SOURCES} OPTIONS ${CUDA_NVCC_FLAGS})

    add_executable(fractal
        $<TARGET_OBJECTS:CPP_OBJECTS>
        ${CUDA_OBJECTS}
    )

    set_target_properties(fractal
    PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_RESOLVE_DEVICE_SYMBOLS ON
    )

    target_link_libraries(fractal PRIVATE sfml-system sfml-window sfml-graphics ${CUDA_LIBRARIES})
else()
    if(CUDA_FOUND)
        message(WARNING "CUDA version ${CUDA_VERSION} found, but version 12.5 or higher is required. Compiling without CUDA support.")
    else()
        message(STATUS "CUDA not found. Compiling without CUDA support.")
    endif()

    add_executable(fractal
        $<TARGET_OBJECTS:CPP_OBJECTS>
    )

    target_link_libraries(fractal PRIVATE sfml-system sfml-window sfml-graphics)
endif()

set_target_properties(fractal PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/../debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/../release
)
