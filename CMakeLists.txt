# CMakeLists.txt
cmake_minimum_required(VERSION 3.30)
project(sdl3-example)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
    set(CMAKE_C_FLAGS "-fexec-charset=CP949")
    set(CMAKE_CXX_FLAGS "-fexec-charset=CP949")
endif ()

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_mixer CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

#add_executable(${PROJECT_NAME} src/main.cpp)
#add_executable(${PROJECT_NAME} src/image.cpp)
#add_executable(${PROJECT_NAME} src/load_wave.cpp)
#add_executable(${PROJECT_NAME} src/load_mp3.cpp)
#add_executable(${PROJECT_NAME} src/particle.cpp)
add_executable(${PROJECT_NAME} src/font.cpp)

#file(COPY ./assets DESTINATION ${CMAKE_BINARY_DIR})

if (WIN32)
    file(COPY ./assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)

else ()
    file(COPY ./assets DESTINATION ${CMAKE_BINARY_DIR})
endif ()

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        SDL3::SDL3
        PRIVATE
        SDL3_image::SDL3_image
        PRIVATE
        SDL3_mixer::SDL3_mixer
        PRIVATE
        SDL3_ttf::SDL3_ttf
)