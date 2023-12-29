include_directories(${CMAKE_SOURCE_DIR})
add_executable(run_server run_server.cc)

add_library(server server.cc)

target_link_libraries(run_server server)