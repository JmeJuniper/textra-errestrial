cmake_minimum_required(VERSION 3.25)
project(TextraErrestrial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

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
	code/scenes/console.cpp
	code/scenes/comms.cpp
	code/scenes/congrats.cpp
	code/scenes/pause.cpp

	# Tilemap & Object handling
	code/game/Map.cpp
	code/game/objects/Object.cpp
	code/game/objects/Player.cpp
	code/game/objects/Box.cpp
	code/game/objects/Console.cpp
	code/game/objects/Comms.cpp
	
	# Helper classes & functions
	code/menu/MenuItem.cpp
	code/game/tilemapUtils.cpp
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