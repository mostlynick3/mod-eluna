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
    auto key = EventKey<VehicleEvents>(EVENT);\
    if (!VehicleEventBindings->HasBindingsFor(key))\
        return;

void Eluna::OnInstall(Vehicle* vehicle)
{
    START_HOOK(VEHICLE_EVENT_ON_INSTALL);
    ArgumentTracker tracker(L);
    HookPush(vehicle);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(VehicleEventBindings, key, argument_count);
}

void Eluna::OnUninstall(Vehicle* vehicle)
{
    START_HOOK(VEHICLE_EVENT_ON_UNINSTALL);
    ArgumentTracker tracker(L);
    HookPush(vehicle);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(VehicleEventBindings, key, argument_count);
}

void Eluna::OnInstallAccessory(Vehicle* vehicle, Creature* accessory)
{
    START_HOOK(VEHICLE_EVENT_ON_INSTALL_ACCESSORY);
    ArgumentTracker tracker(L);
    HookPush(vehicle);
    HookPush(accessory);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(VehicleEventBindings, key, argument_count);
}

void Eluna::OnAddPassenger(Vehicle* vehicle, Unit* passenger, int8 seatId)
{
    START_HOOK(VEHICLE_EVENT_ON_ADD_PASSENGER);
    ArgumentTracker tracker(L);
    HookPush(vehicle);
    HookPush(passenger);
    HookPush(seatId);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(VehicleEventBindings, key, argument_count);
}

void Eluna::OnRemovePassenger(Vehicle* vehicle, Unit* passenger)
{
    START_HOOK(VEHICLE_EVENT_ON_REMOVE_PASSENGER);
    ArgumentTracker tracker(L);
    HookPush(vehicle);
    HookPush(passenger);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(VehicleEventBindings, key, argument_count);
}
