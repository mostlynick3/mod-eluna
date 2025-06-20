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
#include "ElunaEventMgr.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT, ENTRY) \
    auto key = EntryKey<GameObjectEvents>(EVENT, ENTRY);\
    if (!GameObjectEventBindings->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, ENTRY, RETVAL) \
    auto key = EntryKey<GameObjectEvents>(EVENT, ENTRY);\
    if (!GameObjectEventBindings->HasBindingsFor(key))\
        return RETVAL;

void Eluna::OnDummyEffect(WorldObject* pCaster, uint32 spellId, SpellEffIndex effIndex, GameObject* pTarget)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_DUMMY_EFFECT, pTarget->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pCaster);
    HookPush(spellId);
    HookPush(effIndex);
    HookPush(pTarget);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

void Eluna::UpdateAI(GameObject* pGameObject, uint32 diff)
{
    pGameObject->elunaEvents->Update(diff);
    START_HOOK(GAMEOBJECT_EVENT_ON_AIUPDATE, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    HookPush(diff);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

bool Eluna::OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    START_HOOK_WITH_RETVAL(GAMEOBJECT_EVENT_ON_QUEST_ACCEPT, pGameObject->GetEntry(), false);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pGameObject);
    HookPush(pQuest);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(GameObjectEventBindings, key, argument_count);
}

bool Eluna::OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest, uint32 opt)
{
    START_HOOK_WITH_RETVAL(GAMEOBJECT_EVENT_ON_QUEST_REWARD, pGameObject->GetEntry(), false);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pGameObject);
    HookPush(pQuest);
    HookPush(opt);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(GameObjectEventBindings, key, argument_count);
}

void Eluna::GetDialogStatus(const Player* pPlayer, const GameObject* pGameObject)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_DIALOG_STATUS, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pGameObject);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

void Eluna::OnDestroyed(GameObject* pGameObject, WorldObject* attacker)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_DESTROYED, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    HookPush(attacker);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

void Eluna::OnDamaged(GameObject* pGameObject, WorldObject* attacker)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_DAMAGED, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    HookPush(attacker);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

void Eluna::OnLootStateChanged(GameObject* pGameObject, uint32 state)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    HookPush(state);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

void Eluna::OnGameObjectStateChanged(GameObject* pGameObject, uint32 state)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    HookPush(state);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

void Eluna::OnSpawn(GameObject* pGameObject)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_SPAWN, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

void Eluna::OnAddToWorld(GameObject* pGameObject)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_ADD, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

void Eluna::OnRemoveFromWorld(GameObject* pGameObject)
{
    START_HOOK(GAMEOBJECT_EVENT_ON_REMOVE, pGameObject->GetEntry());
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GameObjectEventBindings, key, argument_count);
}

bool Eluna::OnGameObjectUse(Player* pPlayer, GameObject* pGameObject)
{
    START_HOOK_WITH_RETVAL(GAMEOBJECT_EVENT_ON_USE, pGameObject->GetEntry(), false);
    ArgumentTracker tracker(L);
    HookPush(pGameObject);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(GameObjectEventBindings, key, argument_count);
}
