cmake_minimum_required(VERSION 3.0)
project(zappy_server C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g3")

add_subdirectory(libs)

# Add your source files
set(
SOURCES
    src/main.c
)

set(
INCLUDES
    inc/
)

# Create an executable target
add_executable(zappy_server ${SOURCES})
target_include_directories(zappy_server PRIVATE ${INCLUDES})
target_link_libraries(zappy_server PRIVATE list)
