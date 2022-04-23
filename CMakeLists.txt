cmake_minimum_required(VERSION 3.22)
project(http_server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

add_definitions(-D__CMAKE_ROOT_DIRECTORY__="${CMAKE_CURRENT_SOURCE_DIR}/.")
add_subdirectory(vendor)

add_executable(${PROJECT_NAME}
        main.cpp
        http_service/http.h
        utils/clock.h
        utils/clock.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC fmt sandbird winmm ws2_32)
target_link_directories(${PROJECT_NAME} PUBLIC vendor ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC vendor . ${PROJECT_SOURCE_DIR})