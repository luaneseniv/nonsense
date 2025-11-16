# CAMKE GAME

add_executable(${GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp
)

target_include_directories(${GAME_TARGET_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${GAME_TARGET_NAME} PUBLIC ${ENGINE_TARGET_NAME})

# Copy the built engine lib to the game dir
function(CopyLibDirToTarget TARGET_NAME LIB_NAME)
    add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND
        ${CMAKE_COMMAND} -E copy_directory
        $<TARGET_FILE_DIR:${LIB_NAME}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>
    )
endfunction()
CopyLibDirToTarget(${GAME_TARGET_NAME} ${ENGINE_TARGET_NAME})

