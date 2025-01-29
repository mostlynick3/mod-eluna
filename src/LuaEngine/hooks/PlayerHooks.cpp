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
    HookPush(pPlayer);
    HookPush(talentId);
    HookPush(talentRank);
    HookPush(spellid);
    CallAllFunctions(PlayerEventBindings, key);
}

bool Eluna::OnCommand(ChatHandler& handler, const char* text)
{
    Player* player = handler.IsConsole() ? nullptr : handler.GetSession()->GetPlayer();
    // If from console, player is NULL
    if (!player || player->GetSession()->GetSecurity() >= SEC_ADMINISTRATOR)
    {
        std::string reload = text;
        std::transform(reload.begin(), reload.end(), reload.begin(), ::tolower);
        if (reload.find("reload eluna") == 0)
        {
            int mapId = -2;

            sElunaLoader->ReloadElunaForMap(mapId);

            return false;
        }
    }

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_COMMAND, true);
    HookPush(player);
    HookPush(text);
    HookPush(&handler);
    return CallAllFunctionsBool(PlayerEventBindings, key, true);
}

void Eluna::OnLootItem(Player* pPlayer, Item* pItem, uint32 count, ObjectGuid guid)
{
    START_HOOK(PLAYER_EVENT_ON_LOOT_ITEM);
    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(count);
    HookPush(guid);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnLootMoney(Player* pPlayer, uint32 amount)
{
    START_HOOK(PLAYER_EVENT_ON_LOOT_MONEY);
    HookPush(pPlayer);
    HookPush(amount);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnFirstLogin(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_FIRST_LOGIN);
    HookPush(pPlayer);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnRepop(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_REPOP);
    HookPush(pPlayer);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnResurrect(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_RESURRECT);
    HookPush(pPlayer);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnQuestAbandon(Player* pPlayer, uint32 questId)
{
    START_HOOK(PLAYER_EVENT_ON_QUEST_ABANDON);
    HookPush(pPlayer);
    HookPush(questId);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot)
{
    START_HOOK(PLAYER_EVENT_ON_EQUIP);
    HookPush(pPlayer);
    HookPush(pItem);
    HookPush(bag);
    HookPush(slot);
    CallAllFunctions(PlayerEventBindings, key);
}

InventoryResult Eluna::OnCanUseItem(const Player* pPlayer, uint32 itemEntry)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_USE_ITEM, EQUIP_ERR_OK);
    InventoryResult result = EQUIP_ERR_OK;
    HookPush(pPlayer);
    HookPush(itemEntry);
    int n = SetupStack(PlayerEventBindings, key, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 1);

        if (lua_isnumber(L, r))
            result = (InventoryResult)CHECKVAL<uint32>(r);

        lua_pop(L, 1);
    }

    CleanUpStack(2);
    return result;
}
void Eluna::OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy)
{
    START_HOOK(PLAYER_EVENT_ON_ENTER_COMBAT);
    HookPush(pPlayer);
    HookPush(pEnemy);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnPlayerLeaveCombat(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_LEAVE_COMBAT);
    HookPush(pPlayer);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnPVPKill(Player* pKiller, Player* pKilled)
{
    START_HOOK(PLAYER_EVENT_ON_KILL_PLAYER);
    HookPush(pKiller);
    HookPush(pKilled);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnCreatureKill(Player* pKiller, Creature* pKilled)
{
    START_HOOK(PLAYER_EVENT_ON_KILL_CREATURE);
    HookPush(pKiller);
    HookPush(pKilled);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled)
{
    START_HOOK(PLAYER_EVENT_ON_KILLED_BY_CREATURE);
    HookPush(pKiller);
    HookPush(pKilled);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnLevelChanged(Player* pPlayer, uint8 oldLevel)
{
    START_HOOK(PLAYER_EVENT_ON_LEVEL_CHANGE);
    HookPush(pPlayer);
    HookPush(oldLevel);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints)
{
    START_HOOK(PLAYER_EVENT_ON_TALENTS_CHANGE);
    HookPush(pPlayer);
    HookPush(newPoints);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnTalentsReset(Player* pPlayer, bool noCost)
{
    START_HOOK(PLAYER_EVENT_ON_TALENTS_RESET);
    HookPush(pPlayer);
    HookPush(noCost);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnMoneyChanged(Player* pPlayer, int32& amount)
{
    START_HOOK(PLAYER_EVENT_ON_MONEY_CHANGE);
    HookPush(pPlayer);
    HookPush(amount);
    int amountIndex = lua_gettop(L);
    int n = SetupStack(PlayerEventBindings, key, 2);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 2, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<int32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(2);
}

void Eluna::OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim, uint8 xpSource)
{
    START_HOOK(PLAYER_EVENT_ON_GIVE_XP);
    HookPush(pPlayer);
    HookPush(amount);
    HookPush(pVictim);
    HookPush(xpSource);
    int amountIndex = lua_gettop(L) - 1;
    int n = SetupStack(PlayerEventBindings, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 1);

        if (lua_isnumber(L, r))
        {
            amount = CHECKVAL<uint32>(r);
            // Update the stack for subsequent calls.
            ReplaceArgument(amount, amountIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(4);
}

bool Eluna::OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_REPUTATION_CHANGE, true);
    bool result = true;
    HookPush(pPlayer);
    HookPush(factionID);
    HookPush(standing);
    HookPush(incremental);
    int standingIndex = lua_gettop(L) - 1;
    int n = SetupStack(PlayerEventBindings, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 1);

        if (lua_isnumber(L, r))
        {
            standing = CHECKVAL<int32>(r);
            if (standing == -1)
                result = false;
            // Update the stack for subsequent calls.
            ReplaceArgument(standing, standingIndex);
        }

        lua_pop(L, 1);
    }

    CleanUpStack(4);
    return result;
}

void Eluna::OnDuelRequest(Player* pTarget, Player* pChallenger)
{
    START_HOOK(PLAYER_EVENT_ON_DUEL_REQUEST);
    HookPush(pTarget);
    HookPush(pChallenger);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnDuelStart(Player* pStarter, Player* pChallenger)
{
    START_HOOK(PLAYER_EVENT_ON_DUEL_START);
    HookPush(pStarter);
    HookPush(pChallenger);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
{
    START_HOOK(PLAYER_EVENT_ON_DUEL_END);
    HookPush(pWinner);
    HookPush(pLoser);
    HookPush(type);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnEmote(Player* pPlayer, uint32 emote)
{
    START_HOOK(PLAYER_EVENT_ON_EMOTE);
    HookPush(pPlayer);
    HookPush(emote);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, ObjectGuid guid)
{
    START_HOOK(PLAYER_EVENT_ON_TEXT_EMOTE);
    HookPush(pPlayer);
    HookPush(textEmote);
    HookPush(emoteNum);
    HookPush(guid);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnPlayerSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck)
{
    START_HOOK(PLAYER_EVENT_ON_SPELL_CAST);
    HookPush(pPlayer);
    HookPush(pSpell);
    HookPush(skipCheck);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnLogin(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_LOGIN);
    HookPush(pPlayer);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnLogout(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_LOGOUT);
    HookPush(pPlayer);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnCreate(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_CHARACTER_CREATE);
    HookPush(pPlayer);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnDelete(uint32 guidlow)
{
    START_HOOK(PLAYER_EVENT_ON_CHARACTER_DELETE);
    HookPush(guidlow);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnSave(Player* pPlayer)
{
    START_HOOK(PLAYER_EVENT_ON_SAVE);
    HookPush(pPlayer);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent)
{
    START_HOOK(PLAYER_EVENT_ON_BIND_TO_INSTANCE);
    HookPush(pPlayer);
    HookPush(difficulty);
    HookPush(mapid);
    HookPush(permanent);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnUpdateArea(Player* pPlayer, uint32 oldArea, uint32 newArea)
{
    START_HOOK(PLAYER_EVENT_ON_UPDATE_AREA);
    HookPush(pPlayer);
    HookPush(oldArea);
    HookPush(newArea);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
{
    START_HOOK(PLAYER_EVENT_ON_UPDATE_ZONE);
    HookPush(pPlayer);
    HookPush(newZone);
    HookPush(newArea);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnMapChanged(Player* player)
{
    START_HOOK(PLAYER_EVENT_ON_MAP_CHANGE);
    HookPush(player);
    CallAllFunctions(PlayerEventBindings, key);
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, NULL);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CHAT, true);
    bool result = true;
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    int n = SetupStack(PlayerEventBindings, key, 4);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 4, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(4);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, pGroup, NULL);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_GROUP_CHAT, true);
    bool result = true;
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    HookPush(pGroup);
    int n = SetupStack(PlayerEventBindings, key, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, pGuild, NULL, NULL);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_GUILD_CHAT, true);
    bool result = true;
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    HookPush(pGuild);
    int n = SetupStack(PlayerEventBindings, key, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, NULL, NULL, NULL, pChannel);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CHANNEL_CHAT, true);
    bool result = true;
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    HookPush(pChannel->IsConstant() ? static_cast<int32>(pChannel->GetChannelId()) : -static_cast<int32>(pChannel->GetChannelDBId()));
    int n = SetupStack(PlayerEventBindings, key, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

bool Eluna::OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver)
{
    if (lang == LANG_ADDON)
        return OnAddonMessage(pPlayer, type, msg, pReceiver, NULL, NULL, NULL);

    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_WHISPER, true);
    bool result = true;
    HookPush(pPlayer);
    HookPush(msg);
    HookPush(type);
    HookPush(lang);
    HookPush(pReceiver);
    int n = SetupStack(PlayerEventBindings, key, 5);

    while (n > 0)
    {
        int r = CallOneFunction(n--, 5, 2);

        if (lua_isboolean(L, r + 0) && !lua_toboolean(L, r + 0))
            result = false;

        if (lua_isstring(L, r + 1))
            msg = std::string(lua_tostring(L, r + 1));

        lua_pop(L, 2);
    }

    CleanUpStack(5);
    return result;
}

void Eluna::OnPetAddedToWorld(Player* player, Creature* pet)
{
    START_HOOK(PLAYER_EVENT_ON_PET_ADDED_TO_WORLD);
    HookPush(player);
    HookPush(pet);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnLearnSpell(Player* player, uint32 spellId)
{
    START_HOOK(PLAYER_EVENT_ON_LEARN_SPELL);
    HookPush(player);
    HookPush(spellId);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnAchiComplete(Player* player, AchievementEntry const* achievement)
{
    START_HOOK(PLAYER_EVENT_ON_ACHIEVEMENT_COMPLETE);
    HookPush(player);
    HookPush(achievement);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnFfaPvpStateUpdate(Player* player, bool hasFfaPvp)
{
    START_HOOK(PLAYER_EVENT_ON_FFAPVP_CHANGE);
    HookPush(player);
    HookPush(hasFfaPvp);
    CallAllFunctions(PlayerEventBindings, key);
}

bool Eluna::OnCanInitTrade(Player* player, Player* target)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_INIT_TRADE, true);
    HookPush(player);
    HookPush(target);
    return CallAllFunctionsBool(PlayerEventBindings, key);
}

bool Eluna::OnCanSendMail(Player* player, ObjectGuid receiverGuid, ObjectGuid mailbox, std::string& subject, std::string& body, uint32 money, uint32 cod, Item* item)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_SEND_MAIL, true);
    HookPush(player);
    HookPush(receiverGuid);
    HookPush(mailbox);
    HookPush(subject);
    HookPush(body);
    HookPush(money);
    HookPush(cod);
    HookPush(item);
    return CallAllFunctionsBool(PlayerEventBindings, key);
}

bool Eluna::OnCanJoinLfg(Player* player, uint8 roles, lfg::LfgDungeonSet& dungeons, const std::string& comment)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_JOIN_LFG, true);
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
    ++push_counter;

    HookPush(comment);
    return CallAllFunctionsBool(PlayerEventBindings, key);
}

void Eluna::OnQuestRewardItem(Player* player, Item* item, uint32 count)
{
    START_HOOK(PLAYER_EVENT_ON_QUEST_REWARD_ITEM);
    HookPush(player);
    HookPush(item);
    HookPush(count);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnCreateItem(Player* player, Item* item, uint32 count)
{
    START_HOOK(PLAYER_EVENT_ON_CREATE_ITEM);
    HookPush(player);
    HookPush(item);
    HookPush(count);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnStoreNewItem(Player* player, Item* item, uint32 count)
{
    START_HOOK(PLAYER_EVENT_ON_STORE_NEW_ITEM);
    HookPush(player);
    HookPush(item);
    HookPush(count);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnPlayerCompleteQuest(Player* player, Quest const* quest)
{
    START_HOOK(PLAYER_EVENT_ON_COMPLETE_QUEST);
    HookPush(player);
    HookPush(quest);
    CallAllFunctions(PlayerEventBindings, key);
}

bool Eluna::OnCanGroupInvite(Player* player, std::string& memberName)
{
    START_HOOK_WITH_RETVAL(PLAYER_EVENT_ON_CAN_GROUP_INVITE, true);
    HookPush(player);
    HookPush(memberName);
    return CallAllFunctionsBool(PlayerEventBindings, key);
}

void Eluna::OnGroupRollRewardItem(Player* player, Item* item, uint32 count, RollVote voteType, Roll* roll)
{
    START_HOOK(PLAYER_EVENT_ON_GROUP_ROLL_REWARD_ITEM);
    HookPush(player);
    HookPush(item);
    HookPush(count);
    HookPush(voteType);
    HookPush(roll);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnBattlegroundDesertion(Player* player, const BattlegroundDesertionType type)
{
    START_HOOK(PLAYER_EVENT_ON_BG_DESERTION);
    HookPush(player);
    HookPush(type);
    CallAllFunctions(PlayerEventBindings, key);
}

void Eluna::OnCreatureKilledByPet(Player* player, Creature* killed)
{
    START_HOOK(PLAYER_EVENT_ON_PET_KILL);
    HookPush(player);
    HookPush(killed);
    CallAllFunctions(PlayerEventBindings, key);
}
