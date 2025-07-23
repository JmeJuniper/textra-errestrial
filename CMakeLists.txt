cmake_minimum_required(VERSION 3.25)
project(TextraErrestrial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
    # Main file
    main.cpp
    
    # Scenes
    code/scenes/menu.cpp
    code/scenes/credits.cpp
    code/scenes/game.cpp
    code/scenes/congrats.cpp

    # Tilemap & Object handling
    code/game/Map.cpp
    code/game/objects/Object.cpp
    
    # Helper classes & functions
    code/menu/MenuItem.cpp
    code/game/tilemapFuncs.cpp
)
file(COPY
    assets
    data
    DESTINATION
    ${CMAKE_CURRENT_BINARY_DIR}/bin
)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/code/include)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Window)