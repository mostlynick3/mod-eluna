/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto key = EventKey<BGEvents>(EVENT);\
    if (!BGEventBindings->HasBindingsFor(key))\
        return;

void Eluna::OnBGStart(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_START);
    ArgumentTracker tracker(L);
    HookPush(bg);
    HookPush(bgId);
    HookPush(instanceId);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(BGEventBindings, key, argument_count);
}

void Eluna::OnBGEnd(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId, TeamId winner)
{
    START_HOOK(BG_EVENT_ON_END);
    ArgumentTracker tracker(L);
    HookPush(bg);
    HookPush(bgId);
    HookPush(instanceId);
    HookPush(winner);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(BGEventBindings, key, argument_count);
}

void Eluna::OnBGCreate(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_CREATE);
    ArgumentTracker tracker(L);
    HookPush(bg);
    HookPush(bgId);
    HookPush(instanceId);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(BGEventBindings, key, argument_count);
}

void Eluna::OnBGDestroy(BattleGround* bg, BattleGroundTypeId bgId, uint32 instanceId)
{
    START_HOOK(BG_EVENT_ON_PRE_DESTROY);
    ArgumentTracker tracker(L);
    HookPush(bg);
    HookPush(bgId);
    HookPush(instanceId);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(BGEventBindings, key, argument_count);
}
