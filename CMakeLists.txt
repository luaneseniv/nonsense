# CMAKE PROJECT

cmake_minimum_required(VERSION 4.1.2) 

set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)
# set(CMAKE_GENERATOR "Makefiles" CACHE INTERNAL "" FORCE)

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
	GIT_SHALLOW 	FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

set(ENGINE_TARGET_NAME NonsenseEngine)
set(GAME_TARGET_NAME SpaceInvaders)

# Create separate folders for each build config
# cmake -DCMAKE_BUILD_TYPE:STRING=<Debug/Release> -B build
# cmake --build build --target clean
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)

add_subdirectory(Engine)
add_subdirectory(SpaceInvaders)






	