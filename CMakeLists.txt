# CMakeLists.txt
cmake_minimum_required(VERSION 3.30)
project(tetris)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
	include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
endif ()

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)

#add_executable(tetris main.cpp)
add_executable(tetris image.cpp)

file(COPY ./assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(tetris
	PRIVATE
	SDL3::SDL3
	PRIVATE
	SDL3_image::SDL3_image
)