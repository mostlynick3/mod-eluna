/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "Config.h"
#include "ElunaConfig.h"

ElunaConfig::ElunaConfig()
{
}

ElunaConfig* ElunaConfig::instance()
{
    static ElunaConfig instance;
    return &instance;
}

ElunaConfig::~ElunaConfig()
{
}

void ElunaConfig::Initialize()
{
    // Load bools
    SetConfig(CONFIG_ELUNA_ENABLED, "Eluna.Enabled", false);
    SetConfig(CONFIG_ELUNA_TRACEBACK, "Eluna.TraceBack", false);
    SetConfig(CONFIG_ELUNA_PLAYER_RELOAD_ANNOUNCE, "Eluna.PlayerAnnounceReload", false);

    // Load strings
    SetConfig(CONFIG_ELUNA_SCRIPT_PATH, "Eluna.ScriptPath", "lua_scripts");
    SetConfig(CONFIG_ELUNA_REQUIRE_PATH_EXTRA, "Eluna.RequirePaths", "");
    SetConfig(CONFIG_ELUNA_REQUIRE_CPATH_EXTRA, "Eluna.RequireCPaths", "");

    // Call extra functions
    // TokenizeAllowedMaps();
}

void ElunaConfig::SetConfig(ElunaConfigBoolValues index, std::string const& fieldname, bool defvalue)
{
    SetConfig(index, sConfigMgr->GetOption<bool>(fieldname, defvalue));
}

void ElunaConfig::SetConfig(ElunaConfigStringValues index, std::string const& fieldname, std::string defvalue)
{
    SetConfig(index, sConfigMgr->GetOption<std::string>(fieldname, defvalue));
}

bool ElunaConfig::IsElunaEnabled()
{
    return GetConfig(CONFIG_ELUNA_ENABLED);
}