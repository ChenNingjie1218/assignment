cmake_minimum_required(VERSION 3.16.3)
project(DistributedTestSystem)

# debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(modules)

# add_executable(main main.cc)
# target_link_libraries(main dl)
