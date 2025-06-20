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
#include "ElunaLoader.h"
#include <algorithm> // std::transform
#include <cstdlib> // strtol

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto key = EventKey<PlayerEvents>(EVENT);\
    if (!PlayerEventBindings->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, RETVAL) \
    auto key = EventKey<PlayerEvents>(EVENT);\
    if (!PlayerEventBindings->HasBindingsFor(key))\
        return RETVAL;

void Eluna::OnLearnTalents(Player* pPlayer, uint32 talentId, uint32 talentRank, uint32 spellid)
{
    START_HOOK(PLAYER_EVENT_ON_LEARN_TALENTS);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(talentId);
    HookPush(talentRank);
    HookPush(spellid);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

bool Eluna::OnCommand(ChatHandler& handler, const char* text)
{
    Player* player = handler.IsConsole() ? nullptr : handler.GetSession()->GetPlayer();
    // If from console, player is NULL
    if (!player || player->GetSession()->GetSecurity() >= SEC_ADMINISTRATOR)
    {
        std::string reload = text;
        std::transform(reload.begin(), reload.end(), reload.begin(), ::tolower);
        const std::string reload_command = "reload eluna";
        if (reload.find(reload_command) == 0)
        {
            int mapId = RELOAD_ALL_STATES;
            std::string args = reload.substr(reload_command.length());
            if (!args.empty())
                mapId = strtol(args.c_str(), nullptr, 10);

            sElunaLoader->ReloadElunaForMap(mapId);

            return false;
        }
    }

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_COMMAND, true);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(text);
    HookPush(&handler);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(PlayerEventBindings, key, argument_count, true);
}

void Eluna::OnLootItem(Player* pPlayer, Item* pItem, uint32 count, ObjectGuid guid)
{
    START_HOOK(PLAYER_EVENT_ON_LOOT_ITEM);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(count);
    HookPush(guid);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnLootMoney(Player* pPlayer, uint32 amount)
{
    START_HOOK(PLAYER_EVENT_ON_LOOT_MONEY);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(amount);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnFirstLogin(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_FIRST_LOGIN);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnRepop(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_REPOP);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnResurrect(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_RESURRECT);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnQuestAbandon(Player* pPlayer, uint32 questId)
{
    START_HOOK(PLAYER_EVENT_ON_QUEST_ABANDON);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(questId);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot)
{
    START_HOOK(PLAYER_EVENT_ON_EQUIP);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(bag);
    HookPush(slot);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

InventoryResult Eluna::OnCanUseItem(const Player* pPlayer, uint32 itemEntry)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_USE_ITEM, EQUIP_ERR_OK);
    InventoryResult result = EQUIP_ERR_OK;
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(itemEntry);
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 1);

        if (lua_isnumber(L, r))
            result = (InventoryResult)CHECKVAL<uint32>(r);

        lua_pop(L, 1);
    }

    CleanUpStack(argument_count);
    return result;
}
void Eluna::OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy)
{
    START_HOOK(PLAYER_EVENT_ON_ENTER_COMBAT);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pEnemy);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnPlayerLeaveCombat(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_LEAVE_COMBAT);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnPVPKill(Player* pKiller, Player* pKilled)
{
    START_HOOK(PLAYER_EVENT_ON_KILL_PLAYER);
    ArgumentTracker tracker(L);
    HookPush(pKiller);
    HookPush(pKilled);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnCreatureKill(Player* pKiller, Creature* pKilled)
{
    START_HOOK(PLAYER_EVENT_ON_KILL_CREATURE);
    ArgumentTracker tracker(L);
    HookPush(pKiller);
    HookPush(pKilled);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled)
{
    START_HOOK(PLAYER_EVENT_ON_KILLED_BY_CREATURE);
    ArgumentTracker tracker(L);
    HookPush(pKiller);
    HookPush(pKilled);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnLevelChanged(Player* pPlayer, uint8 oldLevel)
{
    START_HOOK(PLAYER_EVENT_ON_LEVEL_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(oldLevel);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints)
{
    START_HOOK(PLAYER_EVENT_ON_TALENTS_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(newPoints);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnTalentsReset(Player* pPlayer, bool noCost)
{
    START_HOOK(PLAYER_EVENT_ON_TALENTS_RESET);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(noCost);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnMoneyChanged(Player* pPlayer, int32& amount)
{
    START_HOOK(PLAYER_EVENT_ON_MONEY_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(amount);
    int amountIndex = 1;
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<int32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex, argument_count);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(argument_count);
}

void Eluna::OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim, uint8 xpSource)
{
    START_HOOK(PLAYER_EVENT_ON_GIVE_XP);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(amount);
    HookPush(pVictim);
    HookPush(xpSource);
    int amountIndex = 1;
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 4);
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

bool Eluna::OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_REPUTATION_CHANGE, true);
    bool result = true;
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(factionID);
    HookPush(standing);
    HookPush(incremental);
    int standingIndex = 2;
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 4);
    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 1);

        if (lua_isnumber(L, r))
        {
            standing = CHECKVAL<int32>(r);
            if (standing == -1)
                result = false;
            // Update the stack for subsequent calls.
            ReplaceArgument(standing, standingIndex, argument_count);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(argument_count);
    return result;
}

void Eluna::OnDuelRequest(Player* pTarget, Player* pChallenger)
{
    START_HOOK(PLAYER_EVENT_ON_DUEL_REQUEST);
    ArgumentTracker tracker(L);
    HookPush(pTarget);
    HookPush(pChallenger);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnDuelStart(Player* pStarter, Player* pChallenger)
{
    START_HOOK(PLAYER_EVENT_ON_DUEL_START);
    ArgumentTracker tracker(L);
    HookPush(pStarter);
    HookPush(pChallenger);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
{
    START_HOOK(PLAYER_EVENT_ON_DUEL_END);
    ArgumentTracker tracker(L);
    HookPush(pWinner);
    HookPush(pLoser);
    HookPush(type);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnEmote(Player* pPlayer, uint32 emote)
{
    START_HOOK(PLAYER_EVENT_ON_EMOTE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(emote);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, ObjectGuid guid)
{
    START_HOOK(PLAYER_EVENT_ON_TEXT_EMOTE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(textEmote);
    HookPush(emoteNum);
    HookPush(guid);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnPlayerSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck)
{
    START_HOOK(PLAYER_EVENT_ON_SPELL_CAST);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pSpell);
    HookPush(skipCheck);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnLogin(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_LOGIN);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnLogout(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_LOGOUT);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnCreate(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_CHARACTER_CREATE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnDelete(uint32 guidlow)
{
    START_HOOK(PLAYER_EVENT_ON_CHARACTER_DELETE);
    ArgumentTracker tracker(L);
    HookPush(guidlow);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnSave(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_SAVE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent)
{
    START_HOOK(PLAYER_EVENT_ON_BIND_TO_INSTANCE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(difficulty);
    HookPush(mapid);
    HookPush(permanent);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnUpdateArea(Player* pPlayer, uint32 oldArea, uint32 newArea)
{
    START_HOOK(PLAYER_EVENT_ON_UPDATE_AREA);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(oldArea);
    HookPush(newArea);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
{
    START_HOOK(PLAYER_EVENT_ON_UPDATE_ZONE);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(newZone);
    HookPush(newArea);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnMapChanged(Player* player)
{
    START_HOOK(PLAYER_EVENT_ON_MAP_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(player);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, NULL);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CHAT, true);
    bool result = true;
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(argument_count);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, pGroup, NULL);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_GROUP_CHAT, true);
    bool result = true;
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    HookPush(pGroup);
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(argument_count);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, pGuild, NULL, NULL);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_GUILD_CHAT, true);
    bool result = true;
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    HookPush(pGuild);
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(argument_count);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, pChannel);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CHANNEL_CHAT, true);
    bool result = true;
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    HookPush(pChannel->IsConstant() ? static_cast<int32>(pChannel->GetChannelId()) : -static_cast<int32>(pChannel->GetChannelDBId()));
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(argument_count);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, pReceiver, NULL, NULL, NULL);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_WHISPER, true);
    bool result = true;
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    HookPush(pReceiver);
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(PlayerEventBindings, key, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(argument_count);
    return result;
}

void Eluna::OnPetAddedToWorld(Player* player, Creature* pet)
{
    START_HOOK(PLAYER_EVENT_ON_PET_ADDED_TO_WORLD);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(pet);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnLearnSpell(Player* player, uint32 spellId)
{
    START_HOOK(PLAYER_EVENT_ON_LEARN_SPELL);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(spellId);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnAchiComplete(Player* player, AchievementEntry const* achievement)
{
    START_HOOK(PLAYER_EVENT_ON_ACHIEVEMENT_COMPLETE);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(achievement);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnFfaPvpStateUpdate(Player* player, bool hasFfaPvp)
{
    START_HOOK(PLAYER_EVENT_ON_FFAPVP_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(hasFfaPvp);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

bool Eluna::OnCanInitTrade(Player* player, Player* target)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_INIT_TRADE, true);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(target);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(PlayerEventBindings, key, argument_count);
}

bool Eluna::OnCanSendMail(Player* player, ObjectGuid receiverGuid, ObjectGuid mailbox, std::string& subject, std::string& body, uint32 money, uint32 cod, Item* item)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_SEND_MAIL, true);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(receiverGuid);
    HookPush(mailbox);
    HookPush(subject);
    HookPush(body);
    HookPush(money);
    HookPush(cod);
    HookPush(item);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(PlayerEventBindings, key, argument_count);
}

bool Eluna::OnCanJoinLfg(Player* player, uint8 roles, lfg::LfgDungeonSet& dungeons, const std::string& comment)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_JOIN_LFG, true);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(roles);

    lua_newtable(L);
    int table = lua_gettop(L);
    uint32 counter = 1;
    for (uint32 dungeon : dungeons)
    {
        HookPush(dungeon);
        lua_rawseti(L, table, counter);
        ++counter;
    }
    lua_settop(L, table);
    ++push_counter; // Increment push_counter for manual table creation

    HookPush(comment);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(PlayerEventBindings, key, argument_count);
}

void Eluna::OnQuestRewardItem(Player* player, Item* item, uint32 count)
{
    START_HOOK(PLAYER_EVENT_ON_QUEST_REWARD_ITEM);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(item);
    HookPush(count);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnCreateItem(Player* player, Item* item, uint32 count)
{
    START_HOOK(PLAYER_EVENT_ON_CREATE_ITEM);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(item);
    HookPush(count);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnStoreNewItem(Player* player, Item* item, uint32 count)
{
    START_HOOK(PLAYER_EVENT_ON_STORE_NEW_ITEM);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(item);
    HookPush(count);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnPlayerCompleteQuest(Player* player, Quest const* quest)
{
    START_HOOK(PLAYER_EVENT_ON_COMPLETE_QUEST);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(quest);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

bool Eluna::OnCanGroupInvite(Player* player, std::string& memberName)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_GROUP_INVITE, true);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(memberName);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(PlayerEventBindings, key, argument_count);
}

void Eluna::OnGroupRollRewardItem(Player* player, Item* item, uint32 count, RollVote voteType, Roll* roll)
{
    START_HOOK(PLAYER_EVENT_ON_GROUP_ROLL_REWARD_ITEM);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(item);
    HookPush(count);
    HookPush(voteType);
    HookPush(roll);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnBattlegroundDesertion(Player* player, const BattlegroundDesertionType type)
{
    START_HOOK(PLAYER_EVENT_ON_BG_DESERTION);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(type);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

void Eluna::OnCreatureKilledByPet(Player* player, Creature* killed)
{
    START_HOOK(PLAYER_EVENT_ON_PET_KILL);
    ArgumentTracker tracker(L);
    HookPush(player);
    HookPush(killed);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(PlayerEventBindings, key, argument_count);
}

bool Eluna::OnPlayerCanUpdateSkill(Player* player, uint32 skill_id)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_UPDATE_SKILL, true);
    Push(player);
    Push(skill_id);
    return CallAllFunctionsBool(PlayerEventBindings, key);
}

void Eluna::OnPlayerBeforeUpdateSkill(Player* player, uint32 skill_id, uint32& value, uint32 max, uint32 step)
{
    START_HOOK(PLAYER_EVENT_ON_BEFORE_UPDATE_SKILL);
    Push(player);
    Push(skill_id);
    Push(value);
    Push(max);
    Push(step);

    int valueIndex = lua_gettop(L) -2;
    int n = SetupStack(PlayerEventBindings, key, 5);
    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 1);
        if (lua_isnumber(L, r))
        {
            value = CHECKVAL<uint32>(L, r);
            // Update the stack for subsequent calls.
            ReplaceArgument(value, valueIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(5);
}

void Eluna::OnPlayerUpdateSkill(Player* player, uint32 skill_id, uint32 value, uint32 max, uint32 step, uint32 new_value)
{
    START_HOOK(PLAYER_EVENT_ON_UPDATE_SKILL);
    Push(player);
    Push(skill_id);
    Push(value);
    Push(max);
    Push(step);
    Push(new_value);
    CallAllFunctions(PlayerEventBindings, key);
}


bool Eluna::CanPlayerResurrect(Player* player)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_RESURRECT, true);
    Push(player);
    return CallAllFunctionsBool(PlayerEventBindings, key);
}
