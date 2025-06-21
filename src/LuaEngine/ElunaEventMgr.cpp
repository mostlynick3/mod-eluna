/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "ElunaEventMgr.h"
#include "LuaEngine.h"
#include "Object.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
};

std::unordered_map<int, GlobalEventMgr::EventData> GlobalEventMgr::globalEvents;
std::mutex GlobalEventMgr::eventMutex;
int GlobalEventMgr::nextEventId = 0;

int GlobalEventMgr::AddEvent(lua_State* L, int funcRef)
{
    std::lock_guard<std::mutex> lock(eventMutex);
    int eventId = ++nextEventId;
    globalEvents[eventId] = EventData{funcRef, L};
    return eventId;
}

bool GlobalEventMgr::GetEvent(int eventId, lua_State*& L, int& funcRef)
{
    std::lock_guard<std::mutex> lock(eventMutex);
    auto it = globalEvents.find(eventId);
    if (it != globalEvents.end()) {
        L = it->second.L;
        funcRef = it->second.funcRef;
        return true;
    }
    ELUNA_LOG_ERROR("[Eluna]: Global event ID {} called but not found!", eventId);
    return false;
}

void GlobalEventMgr::RemoveEvent(int eventId)
{
    std::lock_guard<std::mutex> lock(eventMutex);
    auto it = globalEvents.find(eventId);
    if (it != globalEvents.end()) {
        luaL_unref(it->second.L, LUA_REGISTRYINDEX, it->second.funcRef);
        globalEvents.erase(it);
    }
}

void GlobalEventMgr::ClearAllEvents()
{
    std::lock_guard<std::mutex> lock(eventMutex);
    for (auto& pair : globalEvents) {
        luaL_unref(pair.second.L, LUA_REGISTRYINDEX, pair.second.funcRef);
    }
    globalEvents.clear();
}

ElunaEventProcessor::ElunaEventProcessor(Eluna* _E, WorldObject* _obj) : m_time(0), obj(_obj), E(_E)
{
    if (obj && E && E->eventMgr)
        E->eventMgr->processors.insert(this);
}

ElunaEventProcessor::~ElunaEventProcessor()
{
    RemoveEvents_internal();

    if (obj && E && E->eventMgr)
        E->eventMgr->processors.erase(this);
}

void ElunaEventProcessor::Update(uint32 diff)
{
    m_time += diff;
    for (EventList::iterator it = eventList.begin(); it != eventList.end() && it->first <= m_time; it = eventList.begin())
    {
        LuaEvent* luaEvent = it->second;
        eventList.erase(it);

        if (luaEvent->state != LUAEVENT_STATE_ERASE)
            eventMap.erase(luaEvent->eventId);

        if (luaEvent->state == LUAEVENT_STATE_RUN)
        {
            uint32 delay = luaEvent->delay;
            bool remove = luaEvent->repeats == 1;
            if (!remove)
                AddEvent(luaEvent); // Reschedule before calling incase RemoveEvents used

            ELUNA_LOG_INFO("[Eluna]: Executing timed event ID {}", luaEvent->eventId);
            E->OnTimedEvent(luaEvent->eventId, delay, luaEvent->repeats ? luaEvent->repeats-- : luaEvent->repeats, obj);

            if (!remove)
                continue;
        }

        // Event should be deleted (executed last time or set to be aborted)
        RemoveEvent(luaEvent);
    }
}

void ElunaEventProcessor::SetStates(LuaEventState state)
{
    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        it->second->SetState(state);
    if (state == LUAEVENT_STATE_ERASE)
        eventMap.clear();
}

void ElunaEventProcessor::RemoveEvents_internal()
{
    for (EventList::iterator it = eventList.begin(); it != eventList.end(); ++it)
        RemoveEvent(it->second);

    eventList.clear();
    eventMap.clear();
}

void ElunaEventProcessor::SetState(int eventId, LuaEventState state)
{
    if (eventMap.find(eventId) != eventMap.end())
        eventMap[eventId]->SetState(state);
    if (state == LUAEVENT_STATE_ERASE)
        eventMap.erase(eventId);
}

void ElunaEventProcessor::AddEvent(LuaEvent* luaEvent)
{
    luaEvent->GenerateDelay();
    eventList.insert(std::pair<uint64, LuaEvent*>(m_time + luaEvent->delay, luaEvent));
    eventMap[luaEvent->eventId] = luaEvent;
}

void ElunaEventProcessor::AddEvent(int eventId, uint32 min, uint32 max, uint32 repeats)
{
    AddEvent(new LuaEvent(eventId, min, max, repeats));
}

void ElunaEventProcessor::RemoveEvent(LuaEvent* luaEvent)
{
    // Unreference if should and if Eluna was not yet uninitialized and if the lua state still exists
    if (luaEvent->state != LUAEVENT_STATE_ERASE && E->HasLuaState())
        GlobalEventMgr::RemoveEvent(luaEvent->eventId);
    delete luaEvent;
}

EventMgr::EventMgr(Eluna* _E) : globalProcessor(new ElunaEventProcessor(_E, NULL)), E(_E)
{
}

EventMgr::~EventMgr()
{
    {
        if (!processors.empty())
            for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
                (*it)->RemoveEvents_internal();
        globalProcessor->RemoveEvents_internal();
    }
    delete globalProcessor;
    globalProcessor = NULL;
}

void EventMgr::SetStates(LuaEventState state)
{
    if (!processors.empty())
        for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
            (*it)->SetStates(state);
    globalProcessor->SetStates(state);
}

void EventMgr::SetState(int eventId, LuaEventState state)
{
    if (!processors.empty())
        for (ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it) // loop processors
            (*it)->SetState(eventId, state);
    globalProcessor->SetState(eventId, state);
}

