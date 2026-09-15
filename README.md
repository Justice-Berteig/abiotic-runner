This is a very simple endless runner based on the sleeping minigame from Abiotic
Factor. Made with C++ and raylib.

# Controls
Space to jump

# Current Features
- Infinitely scrolling ground
- Player that can jump
- Pest enemies that can collide with the player
- Game restarts on death
- Randomly spawning decorative clouds

# Planned Features
- Tree decorations
- Mountain decorations
- Rock decorations
- Grass decoration
- Better looking sky
- Sun
- Other enemies
- Lives
- UI to display lives

# Requirements for Building:
- CMake
- raylib
### If Building for Web:
- emscripten
- python (to serve the web build)
- A version of raylib compiled for web, which you can get by:
    1. Downloading the raylib source code from one of the releases
    2. Extract the source code and `cd` into the directory
    3. Edit the `CMakeLists.txt` to include the following lines:
        ```
        if (EMSCRIPTEN)
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
            set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.
        endif ()
        ```
        You May also want to edit the line
        ```
        option(BUILD_EXAMPLES "Build the examples." ${PROJECT_IS_TOP_LEVEL})
        ```
        to instead be
        ```
        option(BUILD_EXAMPLES "Build the examples." OFF)
        ```
    4. Run `emcmake cmake -S . -B build`
    5. Run `cmake --build build`
    6. Make sure that the file `/build/raylib/libraylib.a` exits.

# Building/Running for Desktop:
In project root directory run:
- `cmake -B build` (only needs to be run once)
- `cmake --build build` (run to rebuild)
- `./build/project_name` (to run the program)

# Building/Running for Web:
Edit `CMakePresets.json` on line 7 to change `/usr/lib/emscripten/` to the path
to emscripten on your local machine.

Edit `CMakeLists.txt` on line 22 to change `~/programming/libraries/raylib-6.0/`
to the path where you put the raylib source code on your local machine.

In project root directory run:
- `emcmake cmake -B web_build --preset Web` (only needs to be run once)
- `cmake --build web_build` (run to rebuild)
- `cd web_build` and `python -m http.server 8000` (to serve the web build on port 8000)
