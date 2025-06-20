/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto key = EventKey<ServerEvents>(EVENT);\
    if (!ServerEventBindings->HasBindingsFor(key))\
        return;

#define START_HOOK_WITH_RETVAL(EVENT, RETVAL) \
    auto key = EventKey<ServerEvents>(EVENT);\
    if (!ServerEventBindings->HasBindingsFor(key))\
        return RETVAL;

bool Eluna::OnAddonMessage(Player* sender, uint32 type, std::string& msg, Player* receiver, Guild* guild, Group* group, Channel* channel)
{
    START_HOOK_WITH_RETVAL(ADDON_EVENT_ON_MESSAGE, true);
    ArgumentTracker tracker(L);
    HookPush(sender);
    HookPush(type);

    auto delimeter_position = msg.find('\t');
    if (delimeter_position == std::string::npos)
    {
        HookPush(msg); // prefix
        HookPush(); // msg
    }
    else
    {
        std::string prefix = msg.substr(0, delimeter_position);
        std::string content = msg.substr(delimeter_position + 1, std::string::npos);
        HookPush(prefix);
        HookPush(content);
    }

    if (receiver)
        HookPush(receiver);
    else if (guild)
        HookPush(guild);
    else if (group)
        HookPush(group);
    else if (channel)
        HookPush(channel->GetChannelId());
    else
        HookPush();

    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(ServerEventBindings, key, true, argument_count);
}

void Eluna::OnTimedEvent(int eventId, uint32 delay, uint32 calls, WorldObject* obj)
{
    ASSERT(!event_level);

    // Get function and its Lua state
    lua_State* eventL;
    int funcRef;
    if (!GlobalEventMgr::GetEvent(eventId, eventL, funcRef))
    {
        ELUNA_LOG_DEBUG("[Eluna]: Timed event ID {} not found", eventId);
        return;
    }

    // Get the Eluna instance for the event's Lua state
    Eluna* eventEluna = GetEluna(eventL);

    // Set event level on the correct Eluna instance
    ++eventEluna->event_level;

    lua_rawgeti(eventL, LUA_REGISTRYINDEX, funcRef);
    if (!lua_isfunction(eventL, -1))
    {
        ELUNA_LOG_DEBUG("[Eluna]: Event {} function reference invalid", eventId);
        lua_pop(eventL, 1);
        --eventEluna->event_level;
        return;
    }

    // Push parameters using the event's Eluna instance
    eventEluna->Push(eventId);
    eventEluna->Push(delay);
    eventEluna->Push(calls);
    eventEluna->Push(obj);

    // Execute on the event's Eluna instance
    eventEluna->ExecuteCall(4, 0);

    --eventEluna->event_level;
    ASSERT(!eventEluna->event_level);
    eventEluna->InvalidateObjects();
}

void Eluna::OnGameEventStart(uint32 eventid)
{
    START_HOOK(GAME_EVENT_START);
    ArgumentTracker tracker(L);
    HookPush(eventid);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnGameEventStop(uint32 eventid)
{
    START_HOOK(GAME_EVENT_STOP);
    ArgumentTracker tracker(L);
    HookPush(eventid);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnLuaStateClose()
{
    START_HOOK(ELUNA_EVENT_ON_LUA_STATE_CLOSE);
    ArgumentTracker tracker(L);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnLuaStateOpen()
{
    START_HOOK(ELUNA_EVENT_ON_LUA_STATE_OPEN);
    ArgumentTracker tracker(L);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

// AreaTrigger
bool Eluna::OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger)
{
    START_HOOK_WITH_RETVAL(TRIGGER_EVENT_ON_TRIGGER, false);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pTrigger->entry);

    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(ServerEventBindings, key, false, argument_count);
}

// Weather
void Eluna::OnChange(Weather* /*weather*/, uint32 zone, WeatherState state, float grade)
{
    START_HOOK(WEATHER_EVENT_ON_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(zone);
    HookPush(state);
    HookPush(grade);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

// Auction House
void Eluna::OnAdd(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
    Player* owner = eObjectAccessor()FindPlayer(entry->owner);

    Item* item = eAuctionMgr->GetAItem(entry->item_guid);
    uint32 expiretime = entry->expire_time;

    if (!owner || !item)
        return;

    START_HOOK(AUCTION_EVENT_ON_ADD);
    ArgumentTracker tracker(L);
    HookPush(entry->Id);
    HookPush(owner);
    HookPush(item);
    HookPush(expiretime);
    HookPush(entry->buyout);
    HookPush(entry->startbid);
    HookPush(entry->bid);
    HookPush(entry->bidder);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnRemove(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
    Player* owner = eObjectAccessor()FindPlayer(entry->owner);

    Item* item = eAuctionMgr->GetAItem(entry->item_guid);
    uint32 expiretime = entry->expire_time;

    if (!owner || !item)
        return;

    START_HOOK(AUCTION_EVENT_ON_REMOVE);
    ArgumentTracker tracker(L);
    HookPush(entry->Id);
    HookPush(owner);
    HookPush(item);
    HookPush(expiretime);
    HookPush(entry->buyout);
    HookPush(entry->startbid);
    HookPush(entry->bid);
    HookPush(entry->bidder);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnSuccessful(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
    Player* owner = eObjectAccessor()FindPlayer(entry->owner);

    Item* item = eAuctionMgr->GetAItem(entry->item_guid);
    uint32 expiretime = entry->expire_time;

    if (!owner || !item)
        return;

    START_HOOK(AUCTION_EVENT_ON_SUCCESSFUL);
    ArgumentTracker tracker(L);
    HookPush(entry->Id);
    HookPush(owner);
    HookPush(item);
    HookPush(expiretime);
    HookPush(entry->buyout);
    HookPush(entry->startbid);
    HookPush(entry->bid);
    HookPush(entry->bidder);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnExpire(AuctionHouseObject* /*ah*/, AuctionEntry* entry)
{
    Player* owner = eObjectAccessor()FindPlayer(entry->owner);

    Item* item = eAuctionMgr->GetAItem(entry->item_guid);
    uint32 expiretime = entry->expire_time;

    if (!owner || !item)
        return;

    START_HOOK(AUCTION_EVENT_ON_EXPIRE);
    ArgumentTracker tracker(L);
    HookPush(entry->Id);
    HookPush(owner);
    HookPush(item);
    HookPush(expiretime);
    HookPush(entry->buyout);
    HookPush(entry->startbid);
    HookPush(entry->bid);
    HookPush(entry->bidder);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnOpenStateChange(bool open)
{
    START_HOOK(WORLD_EVENT_ON_OPEN_STATE_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(open);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnConfigLoad(bool reload, bool isBefore)
{
    START_HOOK(WORLD_EVENT_ON_CONFIG_LOAD);
    ArgumentTracker tracker(L);
    HookPush(reload);
    HookPush(isBefore);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask)
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN_INIT);
    ArgumentTracker tracker(L);
    HookPush(code);
    HookPush(mask);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnShutdownCancel()
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN_CANCEL);
    ArgumentTracker tracker(L);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnWorldUpdate(uint32 diff)
{
    START_HOOK(WORLD_EVENT_ON_UPDATE);
    ArgumentTracker tracker(L);
    HookPush(diff);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnStartup()
{
    START_HOOK(WORLD_EVENT_ON_STARTUP);
    ArgumentTracker tracker(L);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnShutdown()
{
    START_HOOK(WORLD_EVENT_ON_SHUTDOWN);
    ArgumentTracker tracker(L);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

/* Map */
void Eluna::OnMapCreate(Map* map)
{
    START_HOOK(MAP_EVENT_ON_CREATE);
    ArgumentTracker tracker(L);
    HookPush(map);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnDestroy(Map* map)
{
    START_HOOK(MAP_EVENT_ON_DESTROY);
    ArgumentTracker tracker(L);
    HookPush(map);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnPlayerEnter(Map* map, Player* player)
{
    START_HOOK(MAP_EVENT_ON_PLAYER_ENTER);
    ArgumentTracker tracker(L);
    HookPush(map);
    HookPush(player);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnPlayerLeave(Map* map, Player* player)
{
    START_HOOK(MAP_EVENT_ON_PLAYER_LEAVE);
    ArgumentTracker tracker(L);
    HookPush(map);
    HookPush(player);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnUpdate(Map* map, uint32 diff)
{
    START_HOOK(MAP_EVENT_ON_UPDATE);
    ArgumentTracker tracker(L);
    // enable this for multithread
    HookPush(map);
    HookPush(diff);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnRemove(GameObject* gameobject)
{
    START_HOOK(WORLD_EVENT_ON_DELETE_GAMEOBJECT);
    ArgumentTracker tracker(L);
    HookPush(gameobject);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}

void Eluna::OnRemove(Creature* creature)
{
    START_HOOK(WORLD_EVENT_ON_DELETE_CREATURE);
    ArgumentTracker tracker(L);
    HookPush(creature);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(ServerEventBindings, key, argument_count);
}
