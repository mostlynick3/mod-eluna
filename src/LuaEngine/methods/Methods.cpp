/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

// Eluna
#include "LuaEngine.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaUtility.h"

// Method includes
#include "GlobalMethods.h"

// Custom methods
// #include "CustomMethods.h"

void RegisterMethods(Eluna* E)
{
    ElunaTemplate<>::SetMethods(E, LuaGlobalFunctions::GlobalMethods);

    ElunaTemplate<long long>::Register(E, "long long");

    ElunaTemplate<unsigned long long>::Register(E, "unsigned long long");

    ElunaTemplate<ObjectGuid>::Register(E, "ObjectGuid");
}
