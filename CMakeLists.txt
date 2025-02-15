cmake_minimum_required(VERSION 3.10)

project(new_chad_neural LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

# if(MSVC)
#     add_compile_options(/W3 /WX)
# else()
#     add_compile_options(-Wall -Wextra -Wpedantic -O3)
# endif()

add_executable(ice-fishing src/main.c)
target_link_libraries(ice-fishing PRIVATE SDL3::SDL3)
