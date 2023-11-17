include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(client Client.cpp)
add_executable(server Server.cpp)
find_package(OpenSSL REQUIRED)
aux_source_directory(. DIR_SRCS)
add_library(mylib ${DIR_SRCS})


target_link_libraries(client OpenSSL::Crypto)

target_link_libraries(client mylib)
target_link_libraries(server mylib)

