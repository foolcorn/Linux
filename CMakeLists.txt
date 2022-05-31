cmake_minimum_required(VERSION 3.16)
project(Linux C)

set(CMAKE_C_STANDARD 11)

include_directories(lib)

add_executable(Linux
        fileio/seek_io.c
        lib/error_function.c
        lib/error_function.h
        lib/get_num.c
        lib/get_num.h
        lib/tlpi_hdr.h
        proc/longjmp.c
        proc/modify_env.c
        main.c)
