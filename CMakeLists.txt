# CMakeLists.txt
cmake_minimum_required(VERSION 3.30)
project(tetris)

set(CMAKE_CXX_STANDARD 17)
#set(SDL3_DIR /Users/joonho/Library/Frameworks/SDL3.xcframework/macos-arm64_x86_64/SDL3.framework)

#find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3 CONFIG REQUIRED)

add_executable(tetris main.cpp)

configure_file(./sample.bmp ${PROJECT_BINARY_DIR}/sample.bmp COPYONLY)
configure_file(./sample.wav ${PROJECT_BINARY_DIR}/sample.wav COPYONLY)
configure_file(./sword.wav ${PROJECT_BINARY_DIR}/sword.wav COPYONLY)

target_link_libraries(tetris PRIVATE SDL3::SDL3)