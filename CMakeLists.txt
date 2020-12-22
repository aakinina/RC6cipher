cmake_minimum_required(VERSION 2.8)

project(ISAP)
add_executable(${PROJECT_NAME} "main.cpp" "rc6.cpp" "rc6.hpp" "wrapper.hpp")
find_package(PkgConfig REQUIRED)
pkg_check_modules(tommath REQUIRED IMPORTED_TARGET libtommath)

target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::tommath)
