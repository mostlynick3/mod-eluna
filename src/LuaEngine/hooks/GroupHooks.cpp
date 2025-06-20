/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto key = EventKey(EVENT);\
    if (!GroupEventBindings->HasBindingsFor(key))\
        return;

void Eluna::OnAddMember(Group* group, ObjectGuid guid)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_ADD);
    ArgumentTracker tracker(L);
    HookPush(group);
    HookPush(guid);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GroupEventBindings, key, argument_count);
}

void Eluna::OnInviteMember(Group* group, ObjectGuid guid)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_INVITE);
    ArgumentTracker tracker(L);
    HookPush(group);
    HookPush(guid);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GroupEventBindings, key, argument_count);
}

void Eluna::OnRemoveMember(Group* group, ObjectGuid guid, uint8 method)
{
    START_HOOK(GROUP_EVENT_ON_MEMBER_REMOVE);
    ArgumentTracker tracker(L);
    HookPush(group);
    HookPush(guid);
    HookPush(method);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GroupEventBindings, key, argument_count);
}

void Eluna::OnChangeLeader(Group* group, ObjectGuid newLeaderGuid, ObjectGuid oldLeaderGuid)
{
    START_HOOK(GROUP_EVENT_ON_LEADER_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(group);
    HookPush(newLeaderGuid);
    HookPush(oldLeaderGuid);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GroupEventBindings, key, argument_count);
}

void Eluna::OnDisband(Group* group)
{
    START_HOOK(GROUP_EVENT_ON_DISBAND);
    ArgumentTracker tracker(L);
    HookPush(group);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GroupEventBindings, key, argument_count);
}

void Eluna::OnCreate(Group* group, ObjectGuid leaderGuid, GroupType groupType)
{
    START_HOOK(GROUP_EVENT_ON_CREATE);
    ArgumentTracker tracker(L);
    HookPush(group);
    HookPush(leaderGuid);
    HookPush(groupType);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GroupEventBindings, key, argument_count);
}
