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
    SetConfig(CONFIG_ELUNA_ENABLED, "Eluna.Enabled", true);
    SetConfig(CONFIG_ELUNA_COMPATIBILITY_MODE, "Eluna.CompatibilityMode", false);
    SetConfig(CONFIG_ELUNA_TRACEBACK, "Eluna.TraceBack", false);
    SetConfig(CONFIG_ELUNA_PLAYER_RELOAD_ANNOUNCE, "Eluna.PlayerAnnounceReload", false);

    // Load strings
    SetConfig(CONFIG_ELUNA_SCRIPT_PATH, "Eluna.ScriptPath", "lua_scripts");
    SetConfig(CONFIG_ELUNA_ONLY_ON_MAPS, "Eluna.OnlyOnMaps", "");
    SetConfig(CONFIG_ELUNA_REQUIRE_PATH_EXTRA, "Eluna.RequirePaths", "");
    SetConfig(CONFIG_ELUNA_REQUIRE_CPATH_EXTRA, "Eluna.RequireCPaths", "");

    // Call extra functions
    TokenizeAllowedMaps();
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

bool ElunaConfig::IsElunaCompatibilityMode()
{
    return GetConfig(CONFIG_ELUNA_COMPATIBILITY_MODE);
}

bool ElunaConfig::ShouldMapLoadEluna(uint32 id)
{
    // if the set is empty (all maps), return true
    if (m_allowedMaps.empty())
        return true;

    // Check if the map ID is in the set
    return (m_allowedMaps.find(id) != m_allowedMaps.end());
}

void ElunaConfig::TokenizeAllowedMaps()
{
    // clear allowed maps
    m_allowedMaps.clear();
    std::string mapString = GetConfig(CONFIG_ELUNA_ONLY_ON_MAPS);
    size_t pos = 0;
    std::string token;

    while ((pos = mapString.find(',')) != std::string::npos) {
        token = mapString.substr(0, pos);
        token.erase(std::remove_if(token.begin(), token.end(), [](char c) {
            return std::isspace(static_cast<unsigned char>(c));
        }), token.end());

        if (!token.empty()) {
            try {
                m_allowedMaps.emplace(std::stoul(token));
            }
            catch (std::exception&) {
                ELUNA_LOG_ERROR("[Eluna]: Error tokenizing Eluna.OnlyOnMaps, invalid config value '{}'", token.c_str());
            }
        }
        mapString.erase(0, pos + 1);
    }

    if (!mapString.empty()) {
        mapString.erase(std::remove_if(mapString.begin(), mapString.end(), [](char c) {
            return std::isspace(static_cast<unsigned char>(c));
        }), mapString.end());

        try {
            m_allowedMaps.emplace(std::stoul(mapString));
        }
        catch (std::exception&) {
            ELUNA_LOG_ERROR("[Eluna]: Error tokenizing Eluna.OnlyOnMaps, invalid config value '{}'", mapString.c_str());
        }
    }
}

