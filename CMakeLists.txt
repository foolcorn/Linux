cmake_minimum_required(VERSION 3.19)
project(LinuxProgram C)

set(CMAKE_C_STANDARD 11)

include_directories(lib)

add_executable(LinuxProgram
        fileio/seek_io.c
        lib/error_function.c
        lib/error_function.h
        lib/get_num.c
        lib/get_num.h
        lib/tlpi_hdr.h
        proc/modify_env.c main.c proc/longjmp.c)
