include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(main Main.cpp)
add_library(filesystem STATIC Filesystem.cpp)
target_link_libraries(main filesystem)