
# Set required version and policy version
cmake_minimum_required( VERSION 3.9.2 FATAL_ERROR )
cmake_policy( VERSION 3.9.2...3.13 )

# Prohibit screwing up the source tree
set( CMAKE_DISABLE_IN_SOURCE_BUILD ON )
set( CMAKE_DISABLE_SOURCE_CHANGES ON )

# Use C++17 everywhere
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

# Compile commands for vim YCM
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Name the project and set a prefix for naming internal targets and variables
project( discord-btw VERSION 0.0.1 LANGUAGES CXX )
set( TARGET_PREFIX ${PROJECT_NAME}-lib )

set( LIB_NAME ${TARGET_PREFIX} )

# Use target folders to organize target list
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

# Download and extract discord game sdk
set( DISCORD_GAME_SDK ${CMAKE_BINARY_DIR}/discord_game_sdk )
set( DISCORD_GAME_SDK_ZIP ${CMAKE_BINARY_DIR}/discord_game_sdk.zip )
if(NOT EXISTS ${CMAKE_BINARY_DIR}/discord_game_sdk.zip)
    message("Downloading discord_game_sdk...")
    file(DOWNLOAD https://dl-game-sdk.discordapp.net/2.5.6/discord_game_sdk.zip ${DISCORD_GAME_SDK_ZIP}
            TIMEOUT 60  # seconds
            TLS_VERIFY ON)
    message("Done.")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E rm -rf ${DISCORD_GAME_SDK})
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${DISCORD_GAME_SDK})
file(ARCHIVE_EXTRACT INPUT ${DISCORD_GAME_SDK_ZIP}
        DESTINATION ${DISCORD_GAME_SDK}
        VERBOSE)

# Copy binary to source directory
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DISCORD_GAME_SDK}/lib/x86_64/discord_game_sdk.so ${PROJECT_SOURCE_DIR}/source)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${DISCORD_GAME_SDK}/lib/x86_64/discord_game_sdk.so ${CMAKE_BINARY_DIR}/source/discord_game_sdk.so)

# Build shared libs
add_subdirectory( source )

set( TARGET_NAME ${PROJECT_NAME} )

add_executable( ${TARGET_NAME} main.cpp)
target_link_libraries( ${TARGET_NAME} ${LIB_NAME} )
target_include_directories( ${TARGET_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} )

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION bin)
install (PROGRAMS ${DISCORD_GAME_SDK}/lib/x86_64/discord_game_sdk.so DESTINATION lib)

