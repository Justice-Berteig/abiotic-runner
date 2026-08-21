# Requirements:
- emscripten
- CMake
- A version of raylib compiled for web.
    - This can be done by:
        1. Cloning raylib from github `git clone https://github.com/raysan5/raylib.git raylib`
        2. Change directory `cd raylib`
        3. Edit the `CMakeLists.txt` to include the following lines:
            ```
            if (EMSCRIPTEN)
                set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
                set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
            endif ()
            ```
        4. Run `emcmake cmake -S . -B build`
        5. Run `cmake --build build`
        6. Make sure that the file `/build/raylib/libraylib.a` exits.
        7. Edit the `CMakeLists.txt` for YOUR project to include the following lines:
            ```
            if (EMSCRIPTEN)
                include_directories(PATH_TO_RAYLIB/build/raylib/include/)
                link_directories(PATH_TO_RAYLIB/build/raylib/)

                set(EMSCRIPTEN_FLAGS "-s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
                set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EMSCRIPTEN_FLAGS}")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EMSCRIPTEN_FLAGS}")
                set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_FLAGS}")
                set(CMAKE_EXECUTABLE_SUFFIX ".html")
            endif ()
            ```

# How to build normally:
cmake -S . -B build
cmake --build build

# How to build for web:
`emcmake cmake -S . -B web_build -DCMAKE_TOOLCHAIN_FILE={PATH_TO_EMSCRIPTEN}/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM=Web`
`emcmake cmake -S . -B web_build -DCMAKE_TOOLCHAIN_FILE=/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake -DPLATFORM=Web`

`cmake --build web_build`

`cd web_build`
`python -m http.server 8000`
