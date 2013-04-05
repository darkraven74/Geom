project(Proj)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
set(CMAKE_BUILD_TYPE "Debug")

add_definitions(-std=c++11 -Wall)
find_package(Boost COMPONENTS chrono system REQUIRED)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} gmp)

