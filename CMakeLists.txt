cmake_minimum_required(VERSION 4.1.2) 

project(Nonsense
	VERSION 0.1.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 		14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS 	OFF)

set(${AWESOME_GAMES_TARGET_NAME} AwesomeGames)

add_subdirectory(AwesomeGames)
