# CMAKE PROJECT

cmake_minimum_required(VERSION 4.1.2) 

set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "Cmake Generator" FORCE)
# set(CMAKE_GENERATOR "Makefiles" CACHE INTERNAL "Cmake Generator" FORCE)

project(Nonsense
	VERSION 0.1.0
	LANGUAGES C CXX
)

set(ENGINE_TARGET_NAME NonsenseEngine)
set(GAME_TARGET_NAME SpaceInvaders)
set(LOG_FILE_NAME "${GAME_TARGET_NAME}.log" CACHE STRING "Log filename")


# Create separate folders for each build config
# cmake -DCMAKE_BUILD_TYPE:STRING=<Debug/Release> -B build
# cmake --build build --target clean
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)
set(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>)

add_subdirectory(Engine)
add_subdirectory(SpaceInvaders)






	