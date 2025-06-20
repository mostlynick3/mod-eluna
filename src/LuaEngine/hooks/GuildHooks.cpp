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
    auto key = EventKey<GuildEvents>(EVENT);\
    if (!GuildEventBindings->HasBindingsFor(key))\
        return;

void Eluna::OnAddMember(Guild * guild, Player * player, uint32 plRank)
{
    START_HOOK(GUILD_EVENT_ON_ADD_MEMBER);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(player);
    HookPush(plRank);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}

void Eluna::OnRemoveMember(Guild* guild, Player* player, bool isDisbanding)
{
    START_HOOK(GUILD_EVENT_ON_REMOVE_MEMBER);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(player);
    HookPush(isDisbanding);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}

void Eluna::OnMOTDChanged(Guild* guild, const std::string& newMotd)
{
    START_HOOK(GUILD_EVENT_ON_MOTD_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(newMotd);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}

void Eluna::OnInfoChanged(Guild* guild, const std::string& newInfo)
{
    START_HOOK(GUILD_EVENT_ON_INFO_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(newInfo);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}

void Eluna::OnCreate(Guild* guild, Player* leader, const std::string& name)
{
    START_HOOK(GUILD_EVENT_ON_CREATE);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(leader);
    HookPush(name);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}

void Eluna::OnDisband(Guild* guild)
{
    START_HOOK(GUILD_EVENT_ON_DISBAND);
    ArgumentTracker tracker(L);
    HookPush(guild);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}

void Eluna::OnMemberWitdrawMoney(Guild* guild, Player* player, uint32& amount, bool isRepair)
{
    START_HOOK(GUILD_EVENT_ON_MONEY_WITHDRAW);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(player);
    HookPush(amount);
    HookPush(isRepair); // isRepair not a part of Mangos, implement?
    int argument_count = tracker.GetArgumentCount();
    int amountIndex = 2;
    int n = SetupStack(GuildEventBindings, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex, argument_count);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(argument_count);
}

void Eluna::OnMemberDepositMoney(Guild* guild, Player* player, uint32& amount)
{
    START_HOOK(GUILD_EVENT_ON_MONEY_DEPOSIT);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(player);
    HookPush(amount);
    int argument_count = tracker.GetArgumentCount();
    int amountIndex = 2;
    int n = SetupStack(GuildEventBindings, key, 3);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 1);
        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex, argument_count);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(argument_count);
}

void Eluna::OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
    bool isDestBank, uint8 destContainer, uint8 destSlotId)
{
    START_HOOK(GUILD_EVENT_ON_ITEM_MOVE);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(player);
    HookPush(pItem);
    HookPush(isSrcBank);
    HookPush(srcContainer);
    HookPush(srcSlotId);
    HookPush(isDestBank);
    HookPush(destContainer);
    HookPush(destSlotId);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}

void Eluna::OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank)
{
    START_HOOK(GUILD_EVENT_ON_EVENT);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(eventType);
    HookPush(playerGuid1);
    HookPush(playerGuid2);
    HookPush(newRank);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}

void Eluna::OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId)
{
    START_HOOK(GUILD_EVENT_ON_BANK_EVENT);
    ArgumentTracker tracker(L);
    HookPush(guild);
    HookPush(eventType);
    HookPush(tabId);
    HookPush(playerGuid);
    HookPush(itemOrMoney);
    HookPush(itemStackCount);
    HookPush(destTabId);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(GuildEventBindings, key, argument_count);
}
