cmake_minimum_required(VERSION 3.17)
project(ChunkList)

# link with lld if available for speed
option(ENABLE_LLD "LLD" ON)
if (ENABLE_LLD)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=lld -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LLD_VERSION)
    if(LLD_VERSION MATCHES "LLD")
        SET(LLD_AVAILABLE ON)
        MESSAGE(STATUS "lld linker available")
    endif()
endif()



# Demo executable
add_executable(ChunkList_Demo ChunkList_demo.cpp ChunkList.h)

# Test executables
add_executable(ChunkList_Test unit_tests/ChunkList_tests.cpp unit_tests/catch_main.cpp unit_tests/catch.hpp ChunkList.h)
add_executable(Constructor_Test unit_tests/constructor_tests.cpp unit_tests/catch_main.cpp unit_tests/catch.hpp ChunkList.h)
add_executable(Append_Remove_Test unit_tests/append_remove_tests.cpp unit_tests/catch_main.cpp unit_tests/catch.hpp ChunkList.h)
add_executable(Index_Test unit_tests/index_tests.cpp unit_tests/catch_main.cpp unit_tests/catch.hpp ChunkList.h)
add_executable(Iterator_Test unit_tests/iterator_tests.cpp unit_tests/catch_main.cpp unit_tests/catch.hpp ChunkList.h)
add_executable(Template_Test unit_tests/template_tests.cpp unit_tests/catch_main.cpp unit_tests/catch.hpp ChunkList.h)

# Fixes issue with catch and Apple
if (APPLE)
    set_property(TARGET ChunkList_Demo PROPERTY CXX_STANDARD 11)
    set_property(TARGET Constructor_Test PROPERTY CXX_STANDARD 11)
    set_property(TARGET Append_Remove_Test PROPERTY CXX_STANDARD 11)
    set_property(TARGET Iterator_Test PROPERTY CXX_STANDARD 11)
    set_property(TARGET Index_Test PROPERTY CXX_STANDARD 11)
    set_property(TARGET Template_Test PROPERTY CXX_STANDARD 11)
endif()
