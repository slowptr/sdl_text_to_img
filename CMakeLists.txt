cmake_minimum_required(VERSION 3.20)
project(sdl_text_to_img)

set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/x86)

add_executable(sdl_text_to_img src/main.cpp src/c_sdlhelper.h)
target_link_libraries(sdl_text_to_img PRIVATE SDL2 SDL2main SDL2_ttf)