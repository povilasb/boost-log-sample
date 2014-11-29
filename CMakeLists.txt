cmake_minimum_required(VERSION 2.4)

project(skeleton CXX)
set(project_exec "main")


message(STATUS "Build type: ${CMAKE_BUILD_TYPE}.")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -pedantic")


set(libs_dir "${CMAKE_CURRENT_SOURCE_DIR}/lib")


# Find Boost libs.
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(BOOST_INCLUDEDIR "${libs_dir}/boost")
set(BOOST_LIBRARYDIR "${libs_dir}/boost/libs")
find_package(Boost 1.56.0 COMPONENTS log_setup log thread date_time
	filesystem system REQUIRED)
include_directories("${Boost_INCLUDE_DIRS}")
message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost libraries: ${Boost_LIBRARIES}")


set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE src_files "${src_dir}/*.cpp")

add_executable(${project_exec} ${src_files})
target_link_libraries(${project_exec} ${Boost_LIBRARIES} pthread rt)

add_custom_target(run COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${project_exec})
