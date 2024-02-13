cmake_minimum_required(VERSION 3.14)
project(SFMLGame)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# set(CMAKE_PREFIX_PATH C:/)
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/Server.cpp src/Server.h src/Client.cpp src/Client.h/
        src/tmx/FreeFuncs.cpp
        src/tmx/ImageLayer.cpp
        src/tmx/LayerGroup.cpp
        src/tmx/Map.cpp
        src/tmx/meson.build
        src/tmx/miniz.c
        src/tmx/miniz.h
        src/tmx/Object.cpp
        src/tmx/ObjectGroup.cpp
        src/tmx/ObjectTypes.cpp
        src/tmx/Property.cpp
        src/tmx/TileLayer.cpp
        src/tmx/Tileset.cpp
        "src/UI and Layout/Tile.cpp"
        "src/UI and Layout/Tile.h"
        src/detail/pugiconfig.hpp
        src/detail/pugixml.cpp
        src/detail/pugixml.hpp src/GameObjects/Player.cpp src/GameObjects/Player.h "src/UI and Layout/Vector.cpp" "src/UI and Layout/Vector.h" "src/UI and Layout/Layout.h" "src/UI and Layout/Layout.cpp" "src/UI and Layout/UI.cpp" "src/UI and Layout/UI.h" "src/UI and Layout/Chatbox.cpp" "src/UI and Layout/Chatbox.h" "src/UI and Layout/ChatMessages.cpp" "src/UI and Layout/ChatMessages.h" src/GameObjects/Coins.cpp src/GameObjects/Coins.h src/GameObjects/GameObject.cpp src/GameObjects/GameObject.h src/GameObjects/Key.cpp src/GameObjects/Key.h src/GameObjects/Button.cpp src/GameObjects/Button.h src/GameObjects/Gate.cpp src/GameObjects/Gate.h src/PacketHeader.h src/Gamestates/MainGame.cpp src/Gamestates/MainGame.h src/Gamestates/Gamestates.cpp src/Gamestates/Gamestates.h src/Gamestates/MainMenu.cpp src/Gamestates/MainMenu.h src/GameObjects/Well.cpp src/GameObjects/Well.h src/Gamestates/Transitions.cpp src/Gamestates/Transitions.h src/Gamestates/WinState.cpp src/Gamestates/WinState.h)
add_executable(SFMLGame ${SOURCE_FILES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (SFMLGame sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
