# CMAKE PROJECT

cmake_minimum_required(VERSION 4.1.2) 

project(Nonsense
	VERSION 0.1.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 			14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS	 	OFF)

# add sfml lib, using version 3.0.2
include(FetchContent)
set(SFML_LIB_NAME SFML)
FetchContent_Declare(
	${SFML_LIB_NAME}
	GIT_REPOSITORY 	https://github.com/SFML/SFML
	GIT_TAG 		3.0.2
	GIT_SHALLOW 	FALE
)
FetchContent_MakeAvailable(${SFML_LIB_NAME})


set(ENGINE_TARGET_NAME NonsenseEngine)
set(GAME_TARGET_NAME SpaceInvaders)

add_subdirectory(Engine)
add_subdirectory(SpaceInvaders)


