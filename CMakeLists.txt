project(final)

cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -pthread")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

if (CONSOLE)
  add_definitions(-DCONSOLE)
endif ()

find_package(Boost REQUIRED system)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
