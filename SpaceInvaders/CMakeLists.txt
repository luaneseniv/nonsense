# CAMKE GAME

add_executable(${GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/spaceship/Spaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/spaceship/Spaceship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerSpaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerSpaceship.cpp
)

# Defined macros for each build config
target_compile_definitions(${GAME_TARGET_NAME} PUBLIC
	$<$<CONFIG:Debug>:DEVELOPMENT_BUILD>
	$<$<CONFIG:Release>:SHIPPING_BUILD>
)

target_include_directories(${GAME_TARGET_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${GAME_TARGET_NAME} PUBLIC ${ENGINE_TARGET_NAME})

# Copy the built engine lib to the built game dir
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

set(CONTENT_FOLDER_NAME content)
set(CONTENT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CONTENT_FOLDER_NAME})

# Copy content to the built game dir
add_custom_command(TARGET ${GAME_TARGET_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy_directory
    ${CONTENT_SRC_DIR}
    $<TARGET_FILE_DIR:${GAME_TARGET_NAME}>/${CONTENT_FOLDER_NAME}
)

# Config file
Configure_file(
    "config.h.cfg"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
)