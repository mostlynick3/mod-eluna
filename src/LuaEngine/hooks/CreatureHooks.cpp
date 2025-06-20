/*
 * Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

using namespace Hooks;

#define START_HOOK(EVENT, CREATURE) \
    auto entry_key = EntryKey<CreatureEvents>(EVENT, CREATURE->GetEntry());\
    auto unique_key = UniqueObjectKey<CreatureEvents>(EVENT, CREATURE->GET_GUID(), CREATURE->GetInstanceId());\
    if (!CreatureEventBindings->HasBindingsFor(entry_key))\
        if (!CreatureUniqueBindings->HasBindingsFor(unique_key))\
            return;

#define START_HOOK_WITH_RETVAL(EVENT, CREATURE, RETVAL) \
    auto entry_key = EntryKey<CreatureEvents>(EVENT, CREATURE->GetEntry());\
    auto unique_key = UniqueObjectKey<CreatureEvents>(EVENT, CREATURE->GET_GUID(), CREATURE->GetInstanceId());\
    if (!CreatureEventBindings->HasBindingsFor(entry_key))\
        if (!CreatureUniqueBindings->HasBindingsFor(unique_key))\
            return RETVAL;

void Eluna::OnDummyEffect(WorldObject* pCaster, uint32 spellId, SpellEffIndex effIndex, Creature* pTarget)
{
    START_HOOK(CREATURE_EVENT_ON_DUMMY_EFFECT, pTarget);
    ArgumentTracker tracker(L);
    HookPush(pCaster);
    HookPush(spellId);
    HookPush(effIndex);
    HookPush(pTarget);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

bool Eluna::OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_QUEST_ACCEPT, pCreature, false);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pCreature);
    HookPush(pQuest);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

bool Eluna::OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest, uint32 opt)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_QUEST_REWARD, pCreature, false);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pCreature);
    HookPush(pQuest);
    HookPush(opt);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

void Eluna::GetDialogStatus(const Player* pPlayer, const Creature* pCreature)
{
    START_HOOK(CREATURE_EVENT_ON_DIALOG_STATUS, pCreature);
    ArgumentTracker tracker(L);
    HookPush(pPlayer);
    HookPush(pCreature);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

void Eluna::OnAddToWorld(Creature* pCreature)
{
    START_HOOK(CREATURE_EVENT_ON_ADD, pCreature);
    ArgumentTracker tracker(L);
    HookPush(pCreature);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

void Eluna::OnRemoveFromWorld(Creature* pCreature)
{
    START_HOOK(CREATURE_EVENT_ON_REMOVE, pCreature);
    ArgumentTracker tracker(L);
    HookPush(pCreature);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

bool Eluna::OnSummoned(Creature* pCreature, Unit* pSummoner)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_SUMMONED, pCreature, false);
    ArgumentTracker tracker(L);
    HookPush(pCreature);
    HookPush(pSummoner);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

bool Eluna::UpdateAI(Creature* me, const uint32 diff)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_AIUPDATE, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(diff);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

//Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
//Called at creature aggro either by MoveInLOS or Attack Start
bool Eluna::EnterCombat(Creature* me, Unit* target)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_ENTER_COMBAT, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(target);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called at any Damage from any attacker (before damage apply)
bool Eluna::DamageTaken(Creature* me, Unit* attacker, uint32& damage)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_DAMAGE_TAKEN, me, false);
    ArgumentTracker tracker(L);
    bool result = false;
    HookPush(me);
    HookPush(attacker);
    HookPush(damage);
    int damageIndex = 2;
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 2);
        if (lua_isboolean(L, r + 0) && lua_toboolean(L, r + 0))
            result = true;
        if (lua_isnumber(L, r + 1))
        {
            damage = CHECKVAL<uint32>(r + 1);
            // Update the stack for subsequent calls.
            ReplaceArgument(damage, damageIndex, argument_count);
        }
        lua_pop(L, 2);
    }
    CleanUpStack(argument_count);
    return result;
}

//Called at creature death
bool Eluna::JustDied(Creature* me, Unit* killer)
{
    On_Reset(me);
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_DIED, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(killer);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

//Called at creature killing another unit
bool Eluna::KilledUnit(Creature* me, Unit* victim)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_TARGET_DIED, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(victim);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called when the creature summon successfully other creature
bool Eluna::JustSummoned(Creature* me, Creature* summon)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(summon);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called when a summoned creature is despawned
bool Eluna::SummonedCreatureDespawn(Creature* me, Creature* summon)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(summon);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

//Called at waypoint reached or PointMovement end
bool Eluna::MovementInform(Creature* me, uint32 type, uint32 id)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_REACH_WP, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(type);
    HookPush(id);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called before EnterCombat even before the creature is in combat.
bool Eluna::AttackStart(Creature* me, Unit* target)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_PRE_COMBAT, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(target);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called for reaction at stopping attack at no attackers or targets
bool Eluna::EnterEvadeMode(Creature* me)
{
    On_Reset(me);
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_LEAVE_COMBAT, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called when creature is spawned or respawned (for reseting variables)
bool Eluna::JustRespawned(Creature* me)
{
    On_Reset(me);
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_SPAWN, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called at reaching home after evade
bool Eluna::JustReachedHome(Creature* me)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_REACH_HOME, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called at text emote receive from player
bool Eluna::ReceiveEmote(Creature* me, Player* player, uint32 emoteId)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_RECEIVE_EMOTE, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(player);
    HookPush(emoteId);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// called when the corpse of this creature gets removed
bool Eluna::CorpseRemoved(Creature* me, uint32& respawnDelay)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_CORPSE_REMOVED, me, false);
    ArgumentTracker tracker(L);
    bool result = false;
    HookPush(me);
    HookPush(respawnDelay);
    int respawnDelayIndex = 1;
    int argument_count = tracker.GetArgumentCount();
    int n = SetupStack(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
    while (n > 0)
    {
        int r = CallOneFunction(n--, argument_count, 2);
        if (lua_isboolean(L, r + 0) && lua_toboolean(L, r + 0))
            result = true;
        if (lua_isnumber(L, r + 1))
        {
            respawnDelay = CHECKVAL<uint32>(r + 1);
            // Update the stack for subsequent calls.
            ReplaceArgument(respawnDelay, respawnDelayIndex, argument_count);
        }
        lua_pop(L, 2);
    }
    CleanUpStack(argument_count);
    return result;
}

bool Eluna::MoveInLineOfSight(Creature* me, Unit* who)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_MOVE_IN_LOS, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(who);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called on creature initial spawn, respawn, death, evade (leave combat)
void Eluna::On_Reset(Creature* me) // Not an override, custom
{
    START_HOOK(CREATURE_EVENT_ON_RESET, me);
    ArgumentTracker tracker(L);
    HookPush(me);
    int argument_count = tracker.GetArgumentCount();
    CallAllFunctions(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called when hit by a spell
bool Eluna::SpellHit(Creature* me, WorldObject* caster, SpellInfo const* spell)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_HIT_BY_SPELL, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(caster);
    HookPush(spell->Id); // Pass spell object?
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called when spell hits a target
bool Eluna::SpellHitTarget(Creature* me, WorldObject* target, SpellInfo const* spell)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_SPELL_HIT_TARGET, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(target);
    HookPush(spell->Id); // Pass spell object?
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

bool Eluna::SummonedCreatureDies(Creature* me, Creature* summon, Unit* killer)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(summon);
    HookPush(killer);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called when owner takes damage
bool Eluna::OwnerAttackedBy(Creature* me, Unit* attacker)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_OWNER_ATTACKED_AT, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(attacker);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}

// Called when owner attacks something
bool Eluna::OwnerAttacked(Creature* me, Unit* target)
{
    START_HOOK_WITH_RETVAL(CREATURE_EVENT_ON_OWNER_ATTACKED, me, false);
    ArgumentTracker tracker(L);
    HookPush(me);
    HookPush(target);
    int argument_count = tracker.GetArgumentCount();
    return CallAllFunctionsBool(CreatureEventBindings, CreatureUniqueBindings, entry_key, unique_key, argument_count);
}
