cmake_minimum_required(VERSION 4.0)
project(
    abiotic_runner
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/sources/*.c") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") # Define PROJECT_INCLUDE to be the path to the include directory of the project

# Declaring our executable
add_executable(
    ${PROJECT_NAME}
    src/animation.cpp
    src/animation.hpp
    src/asset_manager.cpp
    src/asset_manager.hpp
    src/assets.hpp
    src/background.cpp
    src/background.hpp
    src/cloud.cpp
    src/cloud.hpp
    src/enemy.cpp
    src/enemy.hpp
    src/enemy_manager.cpp
    src/enemy_manager.hpp
    src/game.cpp
    src/game.hpp
    src/main.cpp
    src/player.cpp
    src/player.hpp
    src/type_aliases.hpp
)
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
