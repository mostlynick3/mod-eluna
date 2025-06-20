/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */
#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaInstanceAI.h"

using namespace Hooks;

#define START_HOOK(EVENT, AI) \
    auto mapKey = EntryKey<InstanceEvents>(EVENT, AI->instance->GetId());\
    auto instanceKey = EntryKey<InstanceEvents>(EVENT, AI->instance->GetInstanceId());\
    if (!MapEventBindings->HasBindingsFor(mapKey) && !InstanceEventBindings->HasBindingsFor(instanceKey))\
        return;\
    ArgumentTracker tracker(L);\
    PushInstanceData(AI);\
    HookPush<Map>(AI->instance)
#define START_HOOK_WITH_RETVAL(EVENT, AI, RETVAL) \
    auto mapKey = EntryKey<InstanceEvents>(EVENT, AI->instance->GetId());\
    auto instanceKey = EntryKey<InstanceEvents>(EVENT, AI->instance->GetInstanceId());\
    if (!MapEventBindings->HasBindingsFor(mapKey) && !InstanceEventBindings->HasBindingsFor(instanceKey))\
        return RETVAL;\
    ArgumentTracker tracker(L);\
    PushInstanceData(AI);\
    HookPush<Map>(AI->instance)

void Eluna::OnInitialize(ElunaInstanceAI* ai)
{
    START_HOOK(INSTANCE_EVENT_ON_INITIALIZE, ai);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey, argument_count);
}

void Eluna::OnLoad(ElunaInstanceAI* ai)
{
    START_HOOK(INSTANCE_EVENT_ON_LOAD, ai);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey, argument_count);
}

void Eluna::OnUpdateInstance(ElunaInstanceAI* ai, uint32 diff)
{
    START_HOOK(INSTANCE_EVENT_ON_UPDATE, ai);
    HookPush(diff);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey, argument_count);
}

void Eluna::OnPlayerEnterInstance(ElunaInstanceAI* ai, Player* player)
{
    START_HOOK(INSTANCE_EVENT_ON_PLAYER_ENTER, ai);
    HookPush(player);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey, argument_count);
}

void Eluna::OnCreatureCreate(ElunaInstanceAI* ai, Creature* creature)
{
    START_HOOK(INSTANCE_EVENT_ON_CREATURE_CREATE, ai);
    HookPush(creature);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey, argument_count);
}

void Eluna::OnGameObjectCreate(ElunaInstanceAI* ai, GameObject* gameobject)
{
    START_HOOK(INSTANCE_EVENT_ON_GAMEOBJECT_CREATE, ai);
    HookPush(gameobject);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(MapEventBindings, InstanceEventBindings, mapKey, instanceKey, argument_count);
}

bool Eluna::OnCheckEncounterInProgress(ElunaInstanceAI* ai)
{
    START_HOOK_WITH_RETVAL(INSTANCE_EVENT_ON_CHECK_ENCOUNTER_IN_PROGRESS, ai, false);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(MapEventBindings, InstanceEventBindings, mapKey, instanceKey, argument_count);
}
