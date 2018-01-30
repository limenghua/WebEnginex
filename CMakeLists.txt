cmake_minimum_required(VERSION 3.5)

project(WebEnginx)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(src DIR_WEBENGINX_SRCS)

set(Boost_USE_STATIC_LIBS  ON)

find_package(Boost REQUIRED)

include_directories(./include)
include_directories(${Boost_INCLUDE_DIR})

link_directories(./lib/win32)

add_subdirectory(src)
add_subdirectory(tests)


