# CMakeLists.txt
cmake_minimum_required(VERSION 3.30)
project(tetris)

set(CMAKE_CXX_STANDARD 17)
#set(SDL3_DIR /Users/joonho/Library/Frameworks/SDL3.xcframework/macos-arm64_x86_64/SDL3.framework)

#find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
#find_package(libjpeg-turbo CONFIG REQUIRED)

#add_executable(tetris main.cpp)
add_executable(tetris image.cpp)

#file(
#	GLOB RESOURCES
#	*.wav
#	*.jpg
#	*.bmp
#)
#file(COPY ${RESOURCES} DESTINATION ${PROJECT_BINARY_DIR})

#configure_file(./sample.wav ${PROJECT_BINARY_DIR}/sample.wav COPYONLY)
#configure_file(./sword.wav ${PROJECT_BINARY_DIR}/sword.wav COPYONLY)
#configure_file(./gintoki.jpg ${PROJECT_BINARY_DIR}/gintoki.jpg COPYONLY)
#configure_file(./kagura.bmp ${PROJECT_BINARY_DIR}/kagura.bmp COPYONLY)
file(COPY ./assets DESTINATION ${CMAKE_BINARY_DIR})

#target_link_libraries(tetris PRIVATE SDL3::SDL3 SDL3_image::SDL3_image libjpeg-turbo::turbojpeg)
target_link_libraries(tetris PRIVATE SDL3::SDL3 $<IF:$<TARGET_EXISTS:SDL3_image::SDL3_image-shared>,SDL3_image::SDL3_image-shared,SDL3_image::SDL3_image-static>)