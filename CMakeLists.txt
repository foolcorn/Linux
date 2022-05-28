cmake_minimum_required(VERSION 3.19)
project(LinuxProgram C)

set(CMAKE_C_STANDARD 11)

include_directories(lib)

add_executable(LinuxProgram
        fileio/seek_io.c
        lib/error_function.c
        lib/tlpi_hdr.h)
