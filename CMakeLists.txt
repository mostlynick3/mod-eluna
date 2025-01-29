set(LUA_VERSION "lua52" CACHE STRING "Lua version to use")
set_property(CACHE LUA_VERSION PROPERTY STRINGS luajit lua51 lua52 lua53 lua54)
MESSAGE(STATUS "Lua version: ${LUA_VERSION}")

# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP in CMake 3.24:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

option(LUA_STATIC "link lua statically" ON)
if (LUA_STATIC)
  MESSAGE(STATUS "Lua linking: static")
else()
  MESSAGE(STATUS "Lua linking: dynamic")
endif()

if (LUA_VERSION MATCHES "luajit")
  add_subdirectory(src/lualib/luajit)
  set(LUAJIT_VERSION true)
else()
  add_subdirectory(src/lualib/lua)
  set(LUAJIT_VERSION false)
endif()

set_target_properties(lualib PROPERTIES INTERFACE_COMPILE_DEFINITIONS LUAJIT_VERSION)

# Ajout de la partie Eluna
CU_SET_PATH("MOD_ELUNA_DIR" "${CMAKE_CURRENT_LIST_DIR}")

# Inclure les fichiers sources de LuaEngine
file(GLOB_RECURSE ELUNA_SOURCES 
    "${MOD_ELUNA_DIR}/src/LuaEngine/*.cpp"
    "${MOD_ELUNA_DIR}/src/LuaEngine/*.h"
)

# Ajouter la bibliothèque Eluna
add_library(mod-eluna STATIC ${ELUNA_SOURCES})

target_include_directories(mod-eluna
    PUBLIC
        ${CMAKE_SOURCE_DIR}
        ${MOD_ELUNA_DIR}/src
)

target_link_libraries(mod-eluna
    PRIVATE
        lualib
)

# Hook pour modifier game après sa création
CU_ADD_HOOK(AFTER_GAME_LIBRARY "${MOD_ELUNA_DIR}/cmake/after_game.cmake")