# CMAKE PROJECT

cmake_minimum_required(VERSION 4.1.2) 

set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "Cmake Generator" FORCE)
# set(CMAKE_GENERATOR "Makefiles" CACHE INTERNAL "Cmake Generator" FORCE)

project(Nonsense
	VERSION 0.1.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 			17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS	 	OFF)

set(ENGINE_TARGET_NAME NonsenseEngine)
set(GAME_TARGET_NAME SpaceInvaders)
set(LOG_FILE_NAME "${GAME_TARGET_NAME}.log" CACHE STRING "Log filename")


# Create separate folders for each build config
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)

add_subdirectory(Engine)
add_subdirectory(SpaceInvaders)






	