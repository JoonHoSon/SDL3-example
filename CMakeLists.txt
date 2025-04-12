# CMakeLists.txt
cmake_minimum_required(VERSION 3.30)
project(sdl3-example)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
endif ()

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_mixer CONFIG REQUIRED)

#add_executable(${PROJECT_NAME} src/main.cpp)
#add_executable(${PROJECT_NAME} src/image.cpp)
#add_executable(${PROJECT_NAME} src/load_wave.cpp)
add_executable(${PROJECT_NAME} src/load_mp3.cpp)

file(COPY ./assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        SDL3::SDL3
        PRIVATE
        SDL3_image::SDL3_image
        PRIVATE
        SDL3_mixer::SDL3_mixer
)