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

#define START_HOOK(EVENT) \
    auto key = EventKey<TicketEvents>(EVENT);\
    if (!TicketEventBindings->HasBindingsFor(key))\
        return;\

void Eluna::OnTicketCreate(GmTicket* ticket)
{
    START_HOOK(TICKET_EVENT_ON_CREATE);
    ArgumentTracker tracker(L);
    HookPush(ticket);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(TicketEventBindings, key, argument_count);
}

void Eluna::OnTicketUpdateLastChange(GmTicket* ticket)
{
    START_HOOK(TICKET_EVENT_UPDATE_LAST_CHANGE);
    ArgumentTracker tracker(L);
    HookPush(ticket);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(TicketEventBindings, key, argument_count);
}

void Eluna::OnTicketClose(GmTicket* ticket)
{
    START_HOOK(TICKET_EVENT_ON_CLOSE);
    ArgumentTracker tracker(L);
    HookPush(ticket);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(TicketEventBindings, key, argument_count);
}

void Eluna::OnTicketResolve(GmTicket* ticket)
{
    START_HOOK(TICKET_EVENT_ON_RESOLVE);
    ArgumentTracker tracker(L);
    HookPush(ticket);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(TicketEventBindings, key, argument_count);
}

