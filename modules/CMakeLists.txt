# 动态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/modules)
add_library(module1 SHARED module1.cc)
# add_library(module2 SHARED module2.cc)