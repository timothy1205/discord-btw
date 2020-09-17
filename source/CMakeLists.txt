set( CMAKE_FOLDER source )
set( TARGET_NAME ${TARGET_PREFIX} )

# Set DISTRIBUTABLE_INSTALL_DIR in some parent scope
set( DISCORD_INSTALL_DIR ${DISTRIBUTABLE_INSTALL_DIR} )

message("Next: ${CMAKE_CURRENT_SOURCE_DIR}")
#configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/discord_game_sdk.so ${CMAKE_CURRENT_BINARY_DIR} COPYONLY )
add_library( dsdk_lib_import SHARED IMPORTED )
set_target_properties( dsdk_lib_import PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/discord_game_sdk.so )
#install( FILES ${CMAKE_CURRENT_BINARY_DIR}/discord_game_sdk.so DESTINATION ./${DISCORD_INSTALL_DIR} COMPONENT DIST )

add_library( ${LIB_NAME} SHARED
  achievement_manager.cpp achievement_manager.h
  activity_manager.cpp activity_manager.h
  application_manager.cpp application_manager.h
  core.cpp core.h
  discord.h
  event.h
  ffi.h
  image_manager.cpp image_manager.h
  lobby_manager.cpp lobby_manager.h
  network_manager.cpp network_manager.h
  overlay_manager.cpp overlay_manager.h
  relationship_manager.cpp relationship_manager.h
  storage_manager.cpp storage_manager.h
  store_manager.cpp store_manager.h
  types.cpp types.h
  user_manager.cpp user_manager.h
  voice_manager.cpp voice_manager.h
  )
target_include_directories( ${LIB_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )
target_link_libraries( ${LIB_NAME} PRIVATE
    dsdk_lib_import
)

install(TARGETS ${TARGET_NAME} RUNTIME DESTINATION lib)
