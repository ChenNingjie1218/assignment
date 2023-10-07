include_directories(${CMAKE_SOURCE_DIR}/include)
# add_library(mypipe STATIC MyPipe.cpp)
# add_library(reader STATIC Reader.cpp)
# add_library(writer STATIC Writer.cpp)
# add_library(copy STATIC Copy.cpp)
aux_source_directory(. DIR_SRCS)
add_library(mylib ${DIR_SRCS})
add_executable(main Main.cpp)
target_link_libraries(
    main 
    mylib
)


