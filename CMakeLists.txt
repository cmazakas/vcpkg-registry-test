cmake_minimum_required(VERSION 3.8...3.20)

project(vcpkg_registry_test LANGUAGES CXX)

find_package(
  Boost
  REQUIRED

  COMPONENTS
    unordered
    hash2
    bloom
    open_method
)

add_executable("registry-test" src/main.cpp)
target_link_libraries("registry-test" PRIVATE Boost::unordered Boost::hash2)

add_executable("bloom-demo" src/bloom_demo.cpp)
target_link_libraries("bloom-demo" PRIVATE Boost::bloom)

add_executable("open-method-demo" src/open_method_demo.cpp)
target_link_libraries("open-method-demo" PRIVATE Boost::open_method)
