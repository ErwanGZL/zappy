cmake_minimum_required(VERSION 3.0)  # Minimum required version of CMake

project(zappy_gui)  # Name of your project

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O3 -g3")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add source files to your project
set(
SOURCES
    main.cpp
    Gui/Gui.cpp
    Gui/Perlin.cpp
    Gui/TileGui.cpp
    Gui/PlayerGui.cpp
    Net/Network.cpp
    Net/Commands.cpp
    Data/Data.cpp
    Data/Player.cpp
    Data/Team.cpp
    Data/Tile.cpp
    Logger/Logger.cpp
    Data/Egg.cpp
)

set(
INCLUDES_DIR
    Net/
    Gui/
    Data/
    Logger/
    Egg/
)


# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES_DIR})
