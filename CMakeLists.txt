CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
add_compile_options(-Wall -std=c++11 -g)
PROJECT(hw6)
add_executable(hw6_filemerge src/homework6_files.cpp)
add_executable(hw6_search src/homework6_search.cpp)
target_include_directories(hw6_filemerge PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(hw6_search PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

