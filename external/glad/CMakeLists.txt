cmake_minimum_required(VERSION 3.26)

project(Glad)

add_library(glad STATIC
        include/glad/gles2.h
        include/glad/egl.h

        src/gles2.c
        src/egl.c
)
target_include_directories(glad PUBLIC include/)