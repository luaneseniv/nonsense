# CMAKE ENGINE

add_library(${ENGINE_TARGET_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/EntryPoint.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/EntryPoint.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

)

target_include_directories(${ENGINE_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

# SFML Libraries to include
set(SFML_LIBS
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
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
