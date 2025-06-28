target_include_directories(game
    PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/mod-eluna/src/LuaEngine
)

target_link_libraries(game
    PRIVATE
        lualib
)

# Add Eluna headers to game target so core files can include them for Map and WorldObject data methods
target_include_directories(game-interface
  INTERFACE
    ${MOD_ELUNA_DIR}/src/LuaEngine
)