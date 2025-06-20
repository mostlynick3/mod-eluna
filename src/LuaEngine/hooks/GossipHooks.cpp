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

using namespace Hooks;

#define START_HOOK(BINDINGS, EVENT, ENTRY) \
    auto key = EntryKey<GossipEvents>(EVENT, ENTRY);\
    if (!BINDINGS->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(BINDINGS, EVENT, ENTRY, RETVAL) \
    auto key = EntryKey<GossipEvents>(EVENT, ENTRY);\
    if (!BINDINGS->HasBindingsFor(key))\
        return RETVAL;

bool Eluna::OnGossipHello(Player* pPlayer, GameObject* pGameObject)
{
    START_HOOK_WITH_RETVAL(GameObjectGossipBindings, GOSSIP_EVENT_ON_HELLO, pGameObject->GetEntry(), false);
    ArgumentTracker tracker(L);
    pPlayer->PlayerTalkClass->ClearMenus();
    HookPush(pPlayer);
    HookPush(pGameObject);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(GameObjectGossipBindings, key, argument_count, true);
}

bool Eluna::OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action)
{
    START_HOOK_WITH_RETVAL(GameObjectGossipBindings, GOSSIP_EVENT_ON_SELECT, pGameObject->GetEntry(), false);
    ArgumentTracker tracker(L);
    pPlayer->PlayerTalkClass->ClearMenus();
    HookPush(pPlayer);
    HookPush(pGameObject);
    HookPush(sender);
    HookPush(action);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(GameObjectGossipBindings, key, argument_count, true);
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code)
{
    START_HOOK_WITH_RETVAL(GameObjectGossipBindings, GOSSIP_EVENT_ON_SELECT, pGameObject->GetEntry(), false);
    ArgumentTracker tracker(L);
    pPlayer->PlayerTalkClass->ClearMenus();
    HookPush(pPlayer);
    HookPush(pGameObject);
    HookPush(sender);
    HookPush(action);
    HookPush(code);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(GameObjectGossipBindings, key, argument_count, true);
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, uint32 menuId, uint32 sender, uint32 action, const std::string& code)
{
    START_HOOK(PlayerGossipBindings, GOSSIP_EVENT_ON_SELECT, menuId);
    ArgumentTracker tracker(L);
    pPlayer->PlayerTalkClass->ClearMenus();

    HookPush(pPlayer);
    HookPush(pPlayer);
    HookPush(sender);
    HookPush(action);
    if (code.empty())
        HookPush();
    else
        HookPush(code);

    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerGossipBindings, key, argument_count);
}

bool Eluna::OnItemGossip(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
{
    START_HOOK_WITH_RETVAL(ItemGossipBindings, GOSSIP_EVENT_ON_HELLO, pItem->GetEntry(), true);
    ArgumentTracker tracker(L);
    pPlayer->PlayerTalkClass->ClearMenus();
    HookPush(pPlayer);
    HookPush(pItem);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(ItemGossipBindings, key, argument_count, true);
}

void Eluna::HandleGossipSelectOption(Player* pPlayer, Item* pItem, uint32 sender, uint32 action, const std::string& code)
{
    START_HOOK(ItemGossipBindings, GOSSIP_EVENT_ON_SELECT, pItem->GetEntry());
    ArgumentTracker tracker(L);
    pPlayer->PlayerTalkClass->ClearMenus();

    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(sender);
    HookPush(action);
    if (code.empty())
        HookPush();
    else
        HookPush(code);

    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ItemGossipBindings, key, argument_count);
}

bool Eluna::OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    START_HOOK_WITH_RETVAL(CreatureGossipBindings, GOSSIP_EVENT_ON_HELLO, pCreature->GetEntry(), false);
    ArgumentTracker tracker(L);
    pPlayer->PlayerTalkClass->ClearMenus();
    HookPush(pPlayer);
    HookPush(pCreature);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureGossipBindings, key, argument_count, true);
}

bool Eluna::OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    START_HOOK_WITH_RETVAL(CreatureGossipBindings, GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry(), false);
    ArgumentTracker tracker(L);
    auto originalMenu = *pPlayer->PlayerTalkClass;
    pPlayer->PlayerTalkClass->ClearMenus();
    HookPush(pPlayer);
    HookPush(pCreature);
    HookPush(sender);
    HookPush(action);
    int argument_count = tracker.GetArgumentCount();
    auto preventDefault = CallAllFunctionsBool(CreatureGossipBindings, key, argument_count, true);
    if (!preventDefault) {
        *pPlayer->PlayerTalkClass = originalMenu;
    }
    return preventDefault;
}

bool Eluna::OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code)
{
    START_HOOK_WITH_RETVAL(CreatureGossipBindings, GOSSIP_EVENT_ON_SELECT, pCreature->GetEntry(), false);
    ArgumentTracker tracker(L);
    auto originalMenu = *pPlayer->PlayerTalkClass;
    pPlayer->PlayerTalkClass->ClearMenus();
    HookPush(pPlayer);
    HookPush(pCreature);
    HookPush(sender);
    HookPush(action);
    HookPush(code);
    int argument_count = tracker.GetArgumentCount();
    auto preventDefault = CallAllFunctionsBool(CreatureGossipBindings, key, argument_count, true);
    if (!preventDefault) {
        *pPlayer->PlayerTalkClass = originalMenu;
    }
    return preventDefault;
}
