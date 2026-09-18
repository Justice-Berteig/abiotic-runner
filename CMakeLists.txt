cmake_minimum_required(VERSION 4.0)
project(
    abiotic_runner
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define PROJECT_SOURCES as a list of all .cpp and .hpp files in the `src`
# directory.
file(
    GLOB_RECURSE
    PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_LIST_DIR}/src/*.[ch]pp"
)
# Define PROJECT_INCLUDE to be the path to the source directory of the project.
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")
# Define RAYLIB_PATH to be the path to raylib.
set(RAYLIB_PATH "~/programming/libraries/raylib-6.0/")
# Set a bunch of stuff if building for web.
if(EMSCRIPTEN)
    set(
        EMSCRIPTEN_FLAGS
        "-s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1"
    )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EMSCRIPTEN_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EMSCRIPTEN_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# Create new executable target with the project name.
add_executable(${PROJECT_NAME})

# Add the list of .cpp and .hpp files to the executable target.
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
# Include the source directory.
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
# Add raylib includes to the executable.
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        "${RAYLIB_PATH}/build/raylib/include/"
)
# Include built version of raylib for web.
if(EMSCRIPTEN)
    # Link executable with libraylib.a for web build.
    target_link_directories(
        ${PROJECT_NAME}
        PRIVATE
            "${RAYLIB_PATH}/build/raylib/"
    )
    # Add link option to embed resource files in file.js so they can be loaded
    # in the web build.
    # Path is relative to build directory making it `../resources`.
    # `@resources` maps the folder from `../resources` to just `resources` so
    # the file paths will be the same for the desktop and web builds.
    target_link_options(
        ${PROJECT_NAME}
        PRIVATE
            "--embed-file=../resources@resources"
    )
endif()
# Link raylib to the executable target.
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
