cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME Game)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_executable(
        ${PROJECT_NAME}
        main.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            SUFFIX ".html"
            RUNTIME_OUTPUT_DIRECTORY ../build
            LINK_FLAGS " --bind -s WASM=1 -O3 -g3 -flto -s ASSERTIONS=2 -s SAFE_HEAP=1 -s STACK_OVERFLOW_CHECK=1 -s MIN_WEBGL_VERSION=1 -s ABORT_ON_WASM_EXCEPTIONS=1 -g2 -s USE_GLFW=3"
    )
endif ()

if (NOT EMSCRIPTEN)
    add_subdirectory(external/glfw)
endif()
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)