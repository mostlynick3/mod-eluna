/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _HOOK_HELPERS_H
#define _HOOK_HELPERS_H

#include "LuaEngine.h"
#include "ElunaUtility.h"

/*
 * Sets up the stack so that event handlers can be called.
 *
 * Returns the number of functions that were pushed onto the stack.
 */
template<typename K1, typename K2>
int Eluna::SetupStack(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2, int number_of_arguments)
{
    if (key1.event_id != key2.event_id)
    {
        ELUNA_LOG_ERROR("[Eluna]: SetupStack: key1.event_id ({}) does not match key2.event_id ({})", 
            static_cast<int>(key1.event_id), static_cast<int>(key2.event_id));
        return -1;
    }

    // Stack: [arguments]

    Push(key1.event_id);
    ++number_of_arguments;

    // Stack: [arguments], event_id

    int arguments_top = lua_gettop(L);
    int first_argument_index = arguments_top - number_of_arguments + 1;

    if (arguments_top < number_of_arguments)
    {
        ELUNA_LOG_ERROR("[Eluna]: SetupStack: arguments_top ({}) is less than number_of_arguments ({})", arguments_top, number_of_arguments);
        return -1; //
    }

    lua_insert(L, first_argument_index);
    // Stack: event_id, [arguments]

    bindings1->PushRefsFor(key1);
    if (bindings2)
        bindings2->PushRefsFor(key2);
    // Stack: event_id, [arguments], [functions]

    int number_of_functions = lua_gettop(L) - arguments_top;
    return number_of_functions;
}

/*
 * Replace one of the arguments pushed before `SetupStack` with a new value.
 */
template<typename T>
void Eluna::ReplaceArgument(T value, uint8 index, int current_argument_count)
{
    ASSERT(index < current_argument_count && index > 0);
    // Stack: event_id, [arguments], [functions], [results]

    Push(value);
    // Stack: event_id, [arguments], [functions], [results], value

    lua_replace(L, index + 1);
    // Stack: event_id, [arguments and value], [functions], [results]
}

/*
 * Call all event handlers registered to the event ID/entry combination and ignore any results.
 */
template<typename K1, typename K2>
void Eluna::CallAllFunctions(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2, int number_of_arguments)
{
    // Stack: [arguments]

    int initial_stack_size = lua_gettop(L);
    int number_of_functions = SetupStack(bindings1, bindings2, key1, key2, number_of_arguments);
    if (number_of_functions < 0)
    {
        ELUNA_LOG_ERROR("[Eluna]: CallAllFunctions: SetupStack failed, returned: {}", number_of_functions);
        return;
    }
    // Stack: event_id, [arguments], [functions]

    int stack_size_after_setup = lua_gettop(L);
    int original_function_count = number_of_functions;
    while (number_of_functions > 0)
    {
        int stack_before_call = lua_gettop(L);

        int result_index = CallOneFunction(number_of_functions, number_of_arguments, 0);

        if (result_index < 0)
        {
            ELUNA_LOG_ERROR("[Eluna]: CallAllFunctions: CallOneFunction failed, returned: {}", result_index);
            break;
        }

        --number_of_functions;

        int stack_after_call = lua_gettop(L);
        // Stack: event_id, [arguments], [functions - 1]

    }

    if (number_of_functions != 0)
        ELUNA_LOG_ERROR("[Eluna]: CallAllFunctions: Stopped early, {} functions remaining uncalled", number_of_functions);

    // Stack: event_id, [arguments]

    int stack_before_cleanup = lua_gettop(L);

    CleanUpStack(number_of_arguments);

    // Stack: (empty)
    int final_stack_size = lua_gettop(L);

	if (final_stack_size < 0)
		ELUNA_LOG_ERROR("[Eluna]: CallAllFunctions: Stack not properly cleaned up! Final size: {}.", final_stack_size);
}
/*
 * Call all event handlers registered to the event ID/entry combination,
 *   and returns `default_value` if ALL event handlers returned `default_value`,
 *   otherwise returns the opposite of `default_value`.
 */
template<typename K1, typename K2>
bool Eluna::CallAllFunctionsBool(BindingMap<K1>* bindings1, BindingMap<K2>* bindings2, const K1& key1, const K2& key2, int number_of_arguments, bool default_value/* = false*/)
{
    bool result = default_value;
    // Stack: [arguments]

    int number_of_functions = SetupStack(bindings1, bindings2, key1, key2, number_of_arguments);
    // Stack: event_id, [arguments], [functions]

    while (number_of_functions > 0)
    {
        int r = CallOneFunction(number_of_functions, number_of_arguments, 1);
        --number_of_functions;
        // Stack: event_id, [arguments], [functions - 1], result

        if (lua_isboolean(L, r) && (lua_toboolean(L, r) == 1) != default_value)
            result = !default_value;

        lua_pop(L, 1);
        // Stack: event_id, [arguments], [functions - 1]
    }
    // Stack: event_id, [arguments]

    CleanUpStack(number_of_arguments);
    // Stack: (empty)
    return result;
}

#endif // _HOOK_HELPERS_H

