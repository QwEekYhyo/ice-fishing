cmake_minimum_required(VERSION 3.10)

project(ice_fishing LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(SDL3_ttf REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

# if(MSVC)
#     add_compile_options(/W3 /WX)
# else()
#     add_compile_options(-Wall -Wextra -Wpedantic -O3)
# endif()

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(ice-fishing ${SOURCES})
target_include_directories(ice-fishing PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(ice-fishing PRIVATE
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
    SDL3::SDL3
)
