/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef SPELLENTRYMETHODS_H
#define SPELLENTRYMETHODS_H

/***
 * Represents spell data loaded from the DBCs, including effects, costs, attributes, and requirements.
 *
 * Used for inspecting the properties of any spell in the game, such as mana cost, targets, or effects.
 *
 * Inherits all methods from: none
 */
namespace LuaSpellEntry
{
    /**
     * Returns the ID of the [SpellEntry].
     *
     * @return uint32 id
     */
    int GetId(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->Id);
        return 1;
    }

    /**
     * Returns the category ID for the [SpellEntry].
     *
     * @return uint32 categoryId
     */
    int GetCategory(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->Category);
        return 1;
    }

    /**
     * Returns the dispel ID for the [SpellEntry].
     *
     * @return uint32 dispelId
     */
    int GetDispel(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->Dispel);
        return 1;
    }

    /**
     * Returns the mechanic ID for the [SpellEntry].
     *
     * @return uint32 mechanicId
     */
    int GetMechanic(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->Mechanic);
        return 1;
    }

    /**
     * Returns the attribute bitflags for the [SpellEntry].
     *
     * @return uint32 attribute : bitmask, but returned as uint32
     */
    int GetAttributes(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->Attributes);
        return 1;
    }

    /**
     * Returns the attributeEx bitflags for the [SpellEntry].
     *
     * @return uint32 attributeEx : bitmask, but returned as uint32
     */
    int GetAttributesEx(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AttributesEx);
        return 1;
    }

    /**
     * Returns the attributeEx2 bitflags for the [SpellEntry].
     *
     * @return uint32 attributeEx2 : bitmask, but returned as uint32
     */
    int GetAttributesEx2(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AttributesEx2);
        return 1;
    }

    /**
     * Returns the attributeEx3 bitflags for the [SpellEntry].
     *
     * @return uint32 attributeEx3 : bitmask, but returned as uint32
     */
    int GetAttributesEx3(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AttributesEx3);
        return 1;
    }

    /**
     * Returns the attributeEx4 bitflags for the [SpellEntry].
     *
     * @return uint32 attributeEx4 : bitmask, but returned as uint32
     */
    int GetAttributesEx4(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AttributesEx4);
        return 1;
    }

    /**
     * Returns the attributeEx5 bitflags for the [SpellEntry].
     *
     * @return uint32 attributeEx5 : bitmask, but returned as uint32
     */
    int GetAttributesEx5(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AttributesEx5);
        return 1;
    }

    /**
     * Returns the attributeEx6 bitflags for the [SpellEntry].
     *
     * @return uint32 attributeEx6 : bitmask, but returned as uint32
     */
    int GetAttributesEx6(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AttributesEx6);
        return 1;
    }

    /**
     * Returns the attributeEx7 bitflags for the [SpellEntry].
     *
     * @return uint32 attributeEx7 : bitmask, but returned as uint32
     */
    int GetAttributesEx7(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AttributesEx7);
        return 1;
    }

    /**
     * Returns the stance bitflags for the [SpellEntry].
     *
     * @return uint32 stance : bitmask, but returned as uint32
     */
    int GetStances(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->Stances);
        return 1;
    }

    /**
     * Returns the stance restriction bitmask for which the [SpellEntry] cannot be used.
     *
     * This mask indicates which shapeshift forms (stances) prevent the spell from being cast.
     *
     * @return uint32 stancesNotMask
     */
    int GetStancesNot(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->StancesNot);
        return 1;
    }

    /**
     * Returns the target bitmasks for the [SpellEntry].
     *
     * @return uint32 target : bitmasks, but returned as uint32.
     */
    int GetTargets(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->Targets);
        return 1;
    }

    /**
     * Returns the target creature type bitmasks for the [SpellEntry].
     *
     * @return uint32 targetCreatureType : bitmasks, but returned as uint32.
     */
    int GetTargetCreatureType(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->TargetCreatureType);
        return 1;
    }

    /**
     * Returns the SpellFocus ID required to cast this [SpellEntry].
     *
     * Some spells require proximity to a specific game object (e.g., a brazier or altar).
     *
     * @return uint32 spellFocusId
     */
    int GetRequiresSpellFocus(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->RequiresSpellFocus);
        return 1;
    }

    /**
     * Returns the facing flags for this [SpellEntry].
     *
     * Indicates whether the caster must be facing the target or meet other orientation constraints.
     *
     * @return uint32 facingFlags
     */
    int GetFacingCasterFlags(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->FacingCasterFlags);
        return 1;
    }

    /**
     * Returns the required caster aura state for this [SpellEntry].
     *
     * The spell can only be cast if the caster has a specific aura state active.
     *
     * @return uint32 casterAuraState
     */
    int GetCasterAuraState(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->CasterAuraState);
        return 1;
    }

    /**
     * Returns the required target aura state for this [SpellEntry].
     *
     * The spell can only be cast if the target has a specific aura state active.
     *
     * @return uint32 targetAuraState
     */
    int GetTargetAuraState(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->TargetAuraState);
        return 1;
    }

    /**
     * Returns the forbidden caster aura state for this [SpellEntry].
     *
     * The spell cannot be cast if the caster has this aura state active.
     *
     * @return uint32 casterAuraStateNot
     */
    int GetCasterAuraStateNot(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->CasterAuraStateNot);
        return 1;
    }

    /**
     * Returns the forbidden target aura state for this [SpellEntry].
     *
     * The spell cannot be cast if the target has this aura state active.
     *
     * @return uint32 targetAuraStateNot
     */
    int GetTargetAuraStateNot(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->TargetAuraStateNot);
        return 1;
    }

    /**
     * Returns the required aura spell ID that must be on the caster.
     *
     * The spell can only be cast if the caster has an aura from this spell.
     *
     * @return uint32 casterAuraSpellId
     */
    int GetCasterAuraSpell(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->CasterAuraSpell);
        return 1;
    }

    /**
     * Returns the required aura spell ID that must be on the target.
     *
     * The spell can only be cast if the target has an aura from this spell.
     *
     * @return uint32 targetAuraSpellId
     */
    int GetTargetAuraSpell(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->TargetAuraSpell);
        return 1;
    }

    /**
     * Returns the aura spell ID that must NOT be on the caster.
     *
     * The spell cannot be cast if the caster has an aura from this spell.
     *
     * @return uint32 excludeCasterAuraSpellId
     */
    int GetExcludeCasterAuraSpell(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ExcludeCasterAuraSpell);
        return 1;
    }

    /**
     * Returns the aura spell ID that must NOT be on the target.
     *
     * The spell cannot be cast if the target has an aura from this spell.
     *
     * @return uint32 excludeTargetAuraSpellId
     */
    int GetExcludeTargetAuraSpell(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ExcludeTargetAuraSpell);
        return 1;
    }

    /**
     * Returns the casting time index of this [SpellEntry].
     *
     * This index is used to look up the base casting time in SpellCastTimes.dbc.
     *
     * @return uint32 castingTimeIndex
     */
    int GetCastingTimeIndex(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->CastingTimeIndex);
        return 1;
    }

    /**
     * Returns the recovery time for the [SpellEntry].
     *
     * @return uint32 recoveryTime
     */
    int GetRecoveryTime(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->RecoveryTime);
        return 1;
    }

    /**
     * Returns the category recovery time for the [SpellEntry].
     *
     * @return uint32 categoryRecoveryTime : in milliseconds, returned as uint32
     */
    int GetCategoryRecoveryTime(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->CategoryRecoveryTime);
        return 1;
    }

    /**
     * Returns the interrupt flags for this [SpellEntry].
     *
     * Determines what can interrupt this spell while casting (e.g., movement, taking damage).
     *
     * @return uint32 interruptFlags
     */
    int GetInterruptFlags(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->InterruptFlags);
        return 1;
    }

    /**
     * Returns the aura interrupt flags for this [SpellEntry].
     *
     * Indicates what actions will break or remove the aura applied by this spell.
     *
     * @return uint32 auraInterruptFlags
     */
    int GetAuraInterruptFlags(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AuraInterruptFlags);
        return 1;
    }

    /**
     * Returns the channel interrupt flags for this [SpellEntry].
     *
     * Specifies conditions under which a channeled spell will be interrupted (e.g., moving or turning).
     *
     * @return uint32 channelInterruptFlags
     */
    int GetChannelInterruptFlags(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ChannelInterruptFlags);
        return 1;
    }

    /**
     * Returns the proc flags for this [SpellEntry].
     *
     * Determines the types of actions or triggers that can cause this spell to proc.
     *
     * @return uint32 procFlags
     */
    int GetProcFlags(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ProcFlags);
        return 1;
    }

    /**
     * Returns the proc chance of [SpellEntry].
     *
     * @return uint32 procChance
     */
    int GetProcChance(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ProcChance);
        return 1;
    }

    /**
     * Returns the proc charges of [SpellEntry].
     *
     * @return uint32 procCharges
     */
    int GetProcCharges(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ProcCharges);
        return 1;
    }

    /**
     * Returns the max level for the [SpellEntry].
     *
     * @return uint32 maxLevel : the [SpellEntry] max level.
     */
    int GetMaxLevel(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->MaxLevel);
        return 1;
    }

    /**
     * Returns the base level required for the [SpellEntry].
     *
     * @return uint32 baseLevel
     */
    int GetBaseLevel(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->BaseLevel);
        return 1;
    }

    /**
     * Returns the spell level for the [SpellEntry].
     *
     * @return uint32 spellLevel
     */
    int GetSpellLevel(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->SpellLevel);
        return 1;
    }

    /**
     * Returns the duration index for the [SpellEntry].
     *
     * @return uint32 durationIndex
     */
    int GetDurationIndex(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->DurationIndex);
        return 1;
    }

    /**
     * Returns the power type ID for the [SpellEntry].
     *
     * @return uint32 powerTypeId
     */
    int GetPowerType(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->PowerType);
        return 1;
    }

    /**
     * Returns the mana cost for the [SpellEntry].
     *
     * @return uint32 manaCost
     */
    int GetManaCost(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ManaCost);
        return 1;
    }

    /**
     * Returns the mana cost per level for [SpellEntry].
     *
     * @return uint32 manaCostPerLevel
     */
    int GetManaCostPerlevel(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ManaCostPerlevel);
        return 1;
    }

    /**
     * Returns the mana per second for [SpellEntry].
     *
     * @return uint32 manaPerSecond
     */
    int GetManaPerSecond(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ManaPerSecond);
        return 1;
    }

    /**
     * Returns the mana per second per level for [SpellEntry].
     *
     * @return uint32 manaPerSecondPerLevel
     */
    int GetManaPerSecondPerLevel(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ManaPerSecondPerLevel);
        return 1;
    }

    /**
     * Returns the range index for [SpellEntry].
     *
     * @return uint32 rangeIndex
     */
    int GetRangeIndex(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->RangeIndex);
        return 1;
    }

    /**
     * Returns speed for [SpellEntry].
     *
     * @return uint32 speed
     */
    int GetSpeed(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->Speed);
        return 1;
    }

    /**
     * Returns the stack amount for [SpellEntry].
     *
     * @return uint32 stackAmount
     */
    int GetStackAmount(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->StackAmount);
        return 1;
    }

    /**
     * Returns a table with all totem values for [SpellEntry].
     *
     * @return table totem
     */
    int GetTotem(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->Totem.size(); ++index)
        {
            E->Push(entry->Totem[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all reagent values for [SpellEntry].
     *
     * @return table reagent
     */
    int GetReagent(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->Reagent.size(); ++index)
        {
            E->Push(entry->Reagent[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all reagent count values for [SpellEntry].
     *
     * @return table reagentCount
     */
    int GetReagentCount(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->ReagentCount.size(); ++index)
        {
            E->Push(entry->ReagentCount[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns the equipped item class ID for [SpellEntry].
     *
     * @return uint32 equippedItemClassId
     */
    int GetEquippedItemClass(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->EquippedItemClass);
        return 1;
    }

    /**
     * Returns the equipped item sub class masks for [SpellEntry].
     *
     * @return uint32 equippedItemSubClassMasks : bitmasks, returned as uint32.
     */
    int GetEquippedItemSubClassMask(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->EquippedItemSubClassMask);
        return 1;
    }

    /**
     * Returns the equipped item inventory type masks for [SpellEntry].
     *
     * @return uint32 equippedItemInventoryTypeMasks : bitmasks, returned as uint32.
     */
    int GetEquippedItemInventoryTypeMask(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->EquippedItemInventoryTypeMask);
        return 1;
    }

    /**
     * Returns a table with all spell effect IDs for [SpellEntry].
     *
     * @return table effect
     */
    int GetEffect(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->Effect.size(); ++index)
        {
            E->Push(entry->Effect[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect die sides values for [SpellEntry].
     *
     * @return table effectDieSides
     */
    int GetEffectDieSides(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectDieSides.size(); ++index)
        {
            E->Push(entry->EffectDieSides[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect real points per level values for [SpellEntry].
     *
     * @return table effectRealPointsPerLevel
     */
    int GetEffectRealPointsPerLevel(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectRealPointsPerLevel.size(); ++index)
        {
            E->Push(entry->EffectRealPointsPerLevel[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect base points values for [SpellEntry].
     *
     * @return table effectBasePoints
     */
    int GetEffectBasePoints(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectBasePoints.size(); ++index)
        {
            E->Push(entry->EffectBasePoints[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect mechanic IDs for [SpellEntry].
     *
     * @return table effectMechanic
     */
    int GetEffectMechanic(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectMechanic.size(); ++index)
        {
            E->Push(entry->EffectMechanic[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect implicit target a IDs for [SpellEntry].
     *
     * @return table effectImplicitTargetA
     */
    int GetEffectImplicitTargetA(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectImplicitTargetA.size(); ++index)
        {
            E->Push(entry->EffectImplicitTargetA[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect implicit target b IDs for [SpellEntry].
     *
     * @return table effectImplicitTargetB
     */
    int GetEffectImplicitTargetB(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectImplicitTargetB.size(); ++index)
        {
            E->Push(entry->EffectImplicitTargetB[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect radius index for [SpellEntry].
     *
     * @return table effectRadiusIndex
     */
    int GetEffectRadiusIndex(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectRadiusIndex.size(); ++index)
        {
            E->Push(entry->EffectRadiusIndex[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect apply aura IDs for [SpellEntry].
     *
     * @return table effectApplyAura
     */
    int GetEffectApplyAuraName(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectApplyAuraName.size(); ++index)
        {
            E->Push(entry->EffectApplyAuraName[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect amplitude values for [SpellEntry].
     *
     * @return table effectAmplitude
     */
    int GetEffectAmplitude(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectAmplitude.size(); ++index)
        {
            E->Push(entry->EffectAmplitude[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect value multiplier for [SpellEntry].
     *
     * @return table effectValueMultiplier
     */
    int GetEffectValueMultiplier(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectValueMultiplier.size(); ++index)
        {
            E->Push(entry->EffectValueMultiplier[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect chain target values for [SpellEntry].
     *
     * @return table effectChainTarget
     */
    int GetEffectChainTarget(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectChainTarget.size(); ++index)
        {
            E->Push(entry->EffectChainTarget[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect item type values for [SpellEntry].
     *
     * @return table effectItemType
     */
    int GetEffectItemType(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectItemType.size(); ++index)
        {
            E->Push(entry->EffectItemType[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect misc value A for [SpellEntry].
     *
     * @return table effectMiscValueA
     */
    int GetEffectMiscValue(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectMiscValue.size(); ++index)
        {
            E->Push(entry->EffectMiscValue[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect misc value B for [SpellEntry].
     *
     * @return table effectMiscValueB
     */
    int GetEffectMiscValueB(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectMiscValueB.size(); ++index)
        {
            E->Push(entry->EffectMiscValueB[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect trigger spell for [SpellEntry].
     *
     * @return table effectTriggerSpell
     */
    int GetEffectTriggerSpell(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectTriggerSpell.size(); ++index)
        {
            E->Push(entry->EffectTriggerSpell[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with all effect points per combo point of [SpellEntry]
     *
     * @return table effectPointsPerComboPoint : returns a table containing all the effect points per combo point values of [SpellEntry]
     */
    int GetEffectPointsPerComboPoint(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectPointsPerComboPoint.size(); ++index)
        {
            E->Push(entry->EffectPointsPerComboPoint[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table of [SpellFamilyFlags] for each effect of this [SpellEntry].
     *
     * These flags are used to categorize spell effects for use with spell group logic.
     * The table contains up to 3 bitmask entries, one per effect.
     *
     * @return table effectSpellClassMask : table of [SpellFamilyFlags] per effect
     */
    int GetEffectSpellClassMask(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectSpellClassMask.size(); ++index)
        {
            E->Push(entry->EffectSpellClassMask[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with both spell visuals of [SpellEntry]
     *
     * @return table spellVisuals : returns a table containing both spellVisuals for [SpellEntry].
     */
    int GetSpellVisual(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->SpellVisual.size(); ++index)
        {
            E->Push(entry->SpellVisual[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns the spell icon ID for the [SpellEntry].
     *
     * @return uint32 spellIconId
     */
    int GetSpellIconID(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->SpellIconID);
        return 1;
    }

    /**
     * Returns the active icon ID for the [SpellEntry].
     *
     * @return uint32 activeIconId
     */
    int GetActiveIconID(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ActiveIconID);
        return 1;
    }

    /**
     * Returns the spell Priority for the [SpellEntry].
     *
     * @return uint32 spellPriority
     */
    int GetSpellPriority(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->SpellPriority);
        return 1;
    }

    /**
     * Returns a table of the [SpellEntry] names of all locals.
     *
     * @return table spellNames
     */
    int GetSpellName(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->SpellName.size(); ++index)
        {
            E->Push(entry->SpellName[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table of the [SpellEntry] ranks.
     *
     * @return table spellRanks
     */
    int GetRank(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->Rank.size(); ++index)
        {
            E->Push(entry->Rank[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns the mana cost percentage of [SpellEntry].
     *
     * @return uint32 manaCostPercentage : the mana cost in percentage, returned as uint32.
     */
    int GetManaCostPercentage(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->ManaCostPercentage);
        return 1;
    }

    /**
     * Returns the global cooldown time value for [SpellEntry].
     *
     * @return uint32 globalCooldownTime
     */
    int GetStartRecoveryCategory(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->StartRecoveryCategory);
        return 1;
    }

    /**
     * Returns the global cooldown category value for [SpellEntry].
     *
     * @return uint32 globalCooldownCategory
     */
    int GetStartRecoveryTime(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->StartRecoveryTime);
        return 1;
    }

    /**
     * Returns the max target level value for [SpellEntry].
     *
     * @return uint32 maxTargetLevel
     */
    int GetMaxTargetLevel(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->MaxTargetLevel);
        return 1;
    }

    /**
     * Returns the spell family name of this [SpellEntry].
     *
     * This identifies the broader category or class of spells (e.g., Mage, Warrior, Rogue).
     *
     * @return uint32 spellFamilyName
     */
    int GetSpellFamilyName(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->SpellFamilyName);
        return 1;
    }

    /**
     * Returns the spell family flags of this [SpellEntry].
     *
     * These bitflags represent specific characteristics or subcategories of spells within a family.
     *
     * @return uint64 spellFamilyFlags
     */
    int GetSpellFamilyFlags(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->SpellFamilyFlags);
        return 1;
    }

    /**
     * Returns the max affected targets value [SpellEntry].
     *
     * @return uint32 maxAffectedTargets
     */
    int GetMaxAffectedTargets(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->MaxAffectedTargets);
        return 1;
    }

    /**
     * Returns the spell damage type ID [SpellEntry].
     *
     * @return uint32 spellDamageTypeId
     */
    int GetDmgClass(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->DmgClass);
        return 1;
    }

    /**
     * Returns the prevention type ID [SpellEntry].
     *
     * @return uint32 preventionTypeId
     */
    int GetPreventionType(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->PreventionType);
        return 1;
    }

    /**
     * Returns a table with all effect damage multiplier values [SpellEntry].
     *
     * @return table effectDamageMultipliers
     */
    int GetEffectDamageMultiplier(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectDamageMultiplier.size(); ++index)
        {
            E->Push(entry->EffectDamageMultiplier[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns a table with totem categories IDs [SpellEntry].
     *
     * @return table totemCategory
     */
    int GetTotemCategory(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->TotemCategory.size(); ++index)
        {
            E->Push(entry->TotemCategory[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }

    /**
     * Returns the Area Group ID associated with this [SpellEntry].
     *
     * AreaGroupId is used to restrict spell usage to specific zones or areas.
     *
     * @return uint32 areaGroupId
     */
    int GetAreaGroupId(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->AreaGroupId);
        return 1;
    }

    /**
     * Returns the school mask of [SpellEntry].
     *
     * @return uint32 schoolMask : bitmask, returned as uint32.
     */
    int GetSchoolMask(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->SchoolMask);
        return 1;
    }

    /**
     * Returns the rune cost id for the [SpellEntry].
     *
     * @return uint32 runeCostId
     */
    int GetRuneCostID(Eluna* E, SpellEntry* entry)
    {
        E->Push(entry->RuneCostID);
        return 1;
    }

    /**
     * Returns a table with all effect bonus multiplier values [SpellEntry].
     *
     * @return table effectBonusMultipliers
     */
    int GetEffectBonusMultiplier(Eluna* E, SpellEntry* entry)
    {
        lua_newtable(E->L);
        int tbl = lua_gettop(E->L);
        uint32 i = 0;

        for (size_t index = 0; index < entry->EffectBonusMultiplier.size(); ++index)
        {
            E->Push(entry->EffectBonusMultiplier[index]);
            lua_rawseti(E->L, tbl, ++i);
        }

        lua_settop(E->L, tbl); // push table to top of stack
        return 1;
    }
}

#endif
