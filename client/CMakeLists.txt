include_directories(${CMAKE_SOURCE_DIR}/modules)
include_directories(${CMAKE_SOURCE_DIR})
# add_executable(client run_client.cc)
add_executable(run_client run_client.cc)
add_library(client client.cc)
target_link_libraries(run_client dl module1 client)
# add_executable(clientd clientd.cc)

