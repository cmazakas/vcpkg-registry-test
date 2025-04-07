cmake_minimum_required(VERSION 3.8...3.20)

project(vcpkg_registry_test LANGUAGES CXX)

find_package(
  Boost
  REQUIRED

  COMPONENTS
    unordered
    hash2
)

add_executable("registry-test" main.cpp)
target_link_libraries("registry-test" PRIVATE Boost::unordered Boost::hash2)
