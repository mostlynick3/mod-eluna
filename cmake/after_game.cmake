target_include_directories(game
    PRIVATE
        ${CMAKE_SOURCE_DIR}/modules/mod-eluna/src/LuaEngine
)
target_link_libraries(game
    PRIVATE
        lualib
)

set(ELUNA_SELECTIVE_DIR ${CMAKE_BINARY_DIR}/eluna_selective)
file(MAKE_DIRECTORY ${ELUNA_SELECTIVE_DIR})
configure_file(
    ${MOD_ELUNA_DIR}/src/LuaEngine/LuaValue.h
    ${ELUNA_SELECTIVE_DIR}/LuaValue.h
    COPYONLY
)

target_include_directories(game-interface
    INTERFACE
        ${ELUNA_SELECTIVE_DIR}
)