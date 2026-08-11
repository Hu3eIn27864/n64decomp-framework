cmake_minimum_required(VERSION 3.20)

project(
    n64decomp
    VERSION 0.1.0
    DESCRIPTION "Generic Nintendo 64 / MIPS decompilation framework"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(N64DECOMP_BUILD_TESTS "Build the test suite" ON)

add_library(n64decomp_core INTERFACE)

target_include_directories(
    n64decomp_core
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    n64decomp
    src/main.cpp
)

target_link_libraries(
    n64decomp
    PRIVATE
        n64decomp_core
)

target_sources(n64decomp
    PRIVATE
        src/diagnostics.cpp
)

if(N64DECOMP_BUILD_TESTS)
    enable_testing()

    add_executable(
        n64decomp_smoke_test
        tests/smoke_test.cpp
    )

    target_link_libraries(
        n64decomp_smoke_test
        PRIVATE
            n64decomp_core
    )

    add_test(
        NAME n64decomp_smoke_test
        COMMAND n64decomp_smoke_test
    )
endif()
