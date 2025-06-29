cmake_minimum_required(VERSION 3.10)

project(Engine VERSION 1.0 LANGUAGES CXX) # CXX for C++

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})

add_executable(Platformer
    Platformer.cpp
    src/Engine.cpp
    src/GameObject.cpp
)

target_include_directories(Platformer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/includes
)

target_link_libraries(Platformer ${SDL2_LIBRARIES})