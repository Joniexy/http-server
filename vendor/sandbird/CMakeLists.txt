cmake_minimum_required(VERSION 3.22)

function(add_headers VAR)
    set(headers ${${VAR}})
    foreach (header ${ARGN})
        set(headers ${headers} ${header})
    endforeach()
    set(${VAR} ${headers} PARENT_SCOPE)
endfunction()
add_headers(SANDBIRD_HEADER sandbird.h)

set(SANDBIRD_SOURCE sandbird.c)

add_library(sandbird ${SANDBIRD_SOURCE} ${SANDBIRD_HEADER})