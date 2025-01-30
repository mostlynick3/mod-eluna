/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

// Eluna
#include "LuaEngine.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaUtility.h"

// Method includes
#include "AchievementMethods.h"
#include "AuraMethods.h"
#include "BattleGroundMethods.h"
#include "ChatHandlerMethods.h"
#include "CorpseMethods.h"
#include "CreatureMethods.h"
#include "GlobalMethods.h"

// Custom methods
// #include "CustomMethods.h"

void RegisterMethods(Eluna* E)
{
    ElunaTemplate<>::SetMethods(E, LuaGlobalFunctions::GlobalMethods);

    ElunaTemplate<AchievementEntry>::Register(E, "AchievementEntry");
    ElunaTemplate<AchievementEntry>::SetMethods(E, LuaAchievement::AchievementMethods);

    ElunaTemplate<Aura>::Register(E, "Aura");
    ElunaTemplate<Aura>::SetMethods(E, LuaAura::AuraMethods);

    ElunaTemplate<BattleGround>::Register(E, "BattleGround");
    ElunaTemplate<BattleGround>::SetMethods(E, LuaBattleGround::BattleGroundMethods);

    ElunaTemplate<ChatHandler>::Register(E, "ChatHandler");
    ElunaTemplate<ChatHandler>::SetMethods(E, LuaChatHandler::ChatHandlerMethods);

    ElunaTemplate<Corpse>::Register(E, "Corpse");
    // ElunaTemplate<Corpse>::SetMethods(E, LuaObject::ObjectMethods);
    // ElunaTemplate<Corpse>::SetMethods(E, LuaWorldObject::WorldObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, LuaCorpse::CorpseMethods);

    ElunaTemplate<Creature>::Register(E, "Creature");
    // ElunaTemplate<Creature>::SetMethods(E, LuaObject::ObjectMethods);
    // ElunaTemplate<Creature>::SetMethods(E, LuaWorldObject::WorldObjectMethods);
    // ElunaTemplate<Creature>::SetMethods(E, LuaUnit::UnitMethods);
    ElunaTemplate<Creature>::SetMethods(E, LuaCreature::CreatureMethods);

    ElunaTemplate<long long>::Register(E, "long long");

    ElunaTemplate<unsigned long long>::Register(E, "unsigned long long");

    ElunaTemplate<ObjectGuid>::Register(E, "ObjectGuid");
}

