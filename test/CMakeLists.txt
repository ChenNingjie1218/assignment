include_directories(${CMAKE_SOURCE_DIR}/include)
# add_executable(test test.cpp)
# add_executable(test2 test2.cpp)
# add_executable(test3 test3.cpp)
# add_executable(test4 test4.cpp)
find_package(OpenSSL REQUIRED)
# target_link_libraries(test OpenSSL::Crypto)
# target_link_libraries(test2 mylib OpenSSL::Crypto)
# target_link_libraries(test3 OpenSSL::Crypto)
# target_link_libraries(test4 OpenSSL::Crypto)

enable_testing()

add_executable(
  unittest
  UnitTest.cpp
)
find_package(OpenSSL REQUIRED)
target_link_libraries(
  unittest
  GTest::gtest_main
  GTest::gmock_main
  OpenSSL::Crypto
  mylib
)

include(GoogleTest)
# gtest_discover_tests(unittest)