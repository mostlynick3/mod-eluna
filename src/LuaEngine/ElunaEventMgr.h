/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef ELUNA_EVENT_MGR_H
#define ELUNA_EVENT_MGR_H

#include "ElunaUtility.h"
#include "Common.h"
#include "Util.h"
#include <map>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include "Define.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};

class Eluna;
class EventMgr;
class ElunaEventProcessor;
class WorldObject;

enum LuaEventState
{
    LUAEVENT_STATE_RUN,    // On next call run the function normally
    LUAEVENT_STATE_ABORT,  // On next call unregisters reffed function and erases the data
    LUAEVENT_STATE_ERASE,  // On next call just erases the data
};

class GlobalEventMgr
{
private:
    struct EventData {
        int funcRef;
        lua_State* L;
    };

    static std::unordered_map<int, EventData> globalEvents;
    static std::mutex eventMutex;
    static int nextEventId;

public:
    static int AddEvent(lua_State* L, int funcRef);
    static bool GetEvent(int eventId, lua_State*& L, int& funcRef);
    static void RemoveEvent(int eventId);
    static void ClearAllEvents();
};

struct LuaEvent
{
    LuaEvent(int _eventId, uint32 _min, uint32 _max, uint32 _repeats) :
        eventId(_eventId), min(_min), max(_max), delay(0), repeats(_repeats), state(LUAEVENT_STATE_RUN)
    {
    }

    void SetState(LuaEventState _state)
    {
        if (state != LUAEVENT_STATE_ERASE)
            state = _state;
    }

    void GenerateDelay()
    {
        delay = urand(min, max);
    }

    int eventId;    // Lua function reference ID, also used as event ID
    uint32 min;   // Minimum delay between event calls
    uint32 max;   // Maximum delay between event calls
    uint32 delay; // The currently used waiting time
    uint32 repeats; // Amount of repeats to make, 0 for infinite
    LuaEventState state;    // State for next call
};

class ElunaEventProcessor
{
    friend class EventMgr;

public:
    typedef std::multimap<uint64, LuaEvent*> EventList;
    typedef std::unordered_map<int, LuaEvent*> EventMap;

    ElunaEventProcessor(Eluna* _E, WorldObject* _obj);
    ~ElunaEventProcessor();

    void Update(uint32 diff);
    // removes all timed events on next tick or at tick end
    void SetStates(LuaEventState state);
    // set the event to be removed when executing
    void SetState(int eventId, LuaEventState state);
    void AddEvent(int eventId, uint32 min, uint32 max, uint32 repeats);
    EventMap eventMap;

private:
    void RemoveEvents_internal();
    void AddEvent(LuaEvent* luaEvent);
    void RemoveEvent(LuaEvent* luaEvent);
    EventList eventList;
    uint64 m_time;
    WorldObject* obj;
    Eluna* E;
};

class EventMgr
{
public:
    typedef std::unordered_set<ElunaEventProcessor*> ProcessorSet;
    ProcessorSet processors;
    ElunaEventProcessor* globalProcessor;
    Eluna* E;

    EventMgr(Eluna* _E);
    ~EventMgr();

    // Set the state of all timed events
    // Execute only in safe env
    void SetStates(LuaEventState state);

    // Sets the eventId's state in all processors
    // Execute only in safe env
    void SetState(int eventId, LuaEventState state);
};

#endif

