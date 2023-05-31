cmake_minimum_required(VERSION 3.0)
project(zappy_gui)

if (APPLE)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O3 -g3")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)
    include_directories(/opt/homebrew/Cellar/sfml/2.5.1_2)

    # Set the directory containing the libconfig library file
    link_directories(/opt/homebrew/Cellar/sfml/2.5.1_2/lib)

    # Find the libconfig library file
    set(CMAKE_PREFIX_PATH /opt/homebrew/Cellar/sfml/2.5.1_2)

    find_library(LIBCONFIGPP libconfig++.dylib PATHS /opt/homebrew/Cellar/sfml/2.5.1_2/lib)
else()
    find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
endif()

# Add source files to your project
set(
    SOURCES
    main.cpp
    Gui/Gui.cpp
    Gui/Perlin.cpp
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

# Select the appropriate SFML libraries based on the system architecture
if(APPLE)
    if(CMAKE_OSX_ARCHITECTURES STREQUAL "arm64")
        set(SFML_LIBRARIES
            /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-graphics.2.5.1.dylib
            /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-window.2.5.1.dylib
            /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-system.2.5.1.dylib
            /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-audio.2.5.1.dylib
            /opt/homebrew/Cellar/sfml/2.5.1_2/lib/libsfml-network.2.5.1.dylib
        )
    endif()
endif()

# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES_DIR})
