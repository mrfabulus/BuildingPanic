cmake_minimum_required(VERSION 3.0)

project(BuildingPanic)

# Directories
aux_source_directory(./src/ MAIN_SRC)
aux_source_directory(./src/Entity ENTITY_SRC)
aux_source_directory(./src/Input INPUT_SRC)
aux_source_directory(./src/Manager MANAGER_SRC)
aux_source_directory(./src/Resource RESOURCE_SRC)
aux_source_directory(./src/Scene SCENE_SRC)


LIST (APPEND SRC_LIST
    ${MAIN_SRC}
    ${ENTITY_SRC}
    ${INPUT_SRC}
    ${MANAGER_SRC}
    ${RESOURCE_SRC}
    ${SCENE_SRC}
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

# C++14
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# SDL2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
