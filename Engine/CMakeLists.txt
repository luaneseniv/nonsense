# CMAKE ENGINE


add_library(${ENGINE_TARGET_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Core.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Logger.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Logger.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/MathUtility.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/MathUtility.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/PhysicsSystem.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/PhysicsSystem.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp
)

# Defined macros for each build config
target_compile_definitions(${ENGINE_TARGET_NAME} PUBLIC
	$<$<CONFIG:Debug>:DEVELOPMENT_BUILD>
	$<$<CONFIG:Release>:SHIPPING_BUILD>
	LOG_FILE_PATH="${CMAKE_BINARY_DIR}/${GAME_TARGET_NAME}/$<CONFIG>/${LOG_FILE_NAME}"
)


target_include_directories(${ENGINE_TARGET_NAME} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include"
)

include(FetchContent)

# add sfml lib, version 3.0.2
set(SFML_LIB_NAME SFML)
FetchContent_Declare(
	${SFML_LIB_NAME}
	GIT_REPOSITORY 	https://github.com/SFML/SFML
	GIT_TAG 		3.0.2
	GIT_SHALLOW 	FALSE
)
FetchContent_MakeAvailable(${SFML_LIB_NAME})

# add Box2D lib, version 3.1.1
set(BOX2D_LIB_NAME Box2D)
FetchContent_Declare(
	${BOX2D_LIB_NAME}
	GIT_REPOSITORY https://github.com/erincatto/box2d
	GIT_TAG v3.1.1
	GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(${BOX2D_LIB_NAME})
	
# Libraries to include
set(SFML_LIBS
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	box2d
)
	
target_link_libraries(${ENGINE_TARGET_NAME} PUBLIC ${SFML_LIBS})

function(CopyLibToTarget TARGET_NAME LIB_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
		POST_BUILD
		COMMAND
		${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:${LIB_NAME}>
		$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

# copy sfml lib files to the engine
foreach(libraryItem ${SFML_LIBS})
	CopyLibToTarget(${ENGINE_TARGET_NAME} ${libraryItem})
endforeach()