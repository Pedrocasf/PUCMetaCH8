cmake_minimum_required(VERSION 3.13)
project(PUCMetaCH8 VERSION 0.1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 17)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.c src/Chip8.c src/Chip8.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})