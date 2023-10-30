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
)

include(GoogleTest)
# gtest_discover_tests(unittest)

include_directories(${CMAKE_SOURCE_DIR}/include)