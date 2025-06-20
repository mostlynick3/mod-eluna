/*
* Copyright (C) 2010 - 2016 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef TICKETMETHODS_H
#define TICKETMETHODS_H

/***
 * An instance of a ticket, created when the ticket is opened by a [Player].
 *
 * Inherits all methods from: none
 */
namespace LuaTicket
{
    /**
     * Returns true if the [Ticket] is closed or false.
     *
     * @return bool is_closed
     */
    int IsClosed(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->IsClosed());
        return 1;
    }

    /**
     * Returns true if the [Ticket] is completed or false.
     *
     * @return bool is_completed
     */
    int IsCompleted(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->IsCompleted());
        return 1;
    }

    /**
     * Return true if this GUID is the same as the [Player] who created the [Ticket] or false.
     *
     * @param guid playerGuid : desired playerGuid
     *
     * @return bool same_guid
     */
    int IsFromPlayer(Eluna* E, GmTicket* ticket)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);

        E->Push(ticket->IsFromPlayer(guid));
        return 1;
    }

    /**
     * Return true if the [Ticket] is assigned or false.
     *
     * @return bool is_assigned
     */
    int IsAssigned(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->IsAssigned());
        return 1;
    }

    /**
     * Return true if the [Ticket] is assigned to the GUID or false.
     *
     * @param guid playerGuid : desired playerGuid
     *
     * @return bool is_assigned_to
     */
    int IsAssignedTo(Eluna* E, GmTicket* ticket)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);

        E->Push(ticket->IsAssignedTo(guid));
        return 1;
    }

    /**
     * Return true if the [Ticket] is not assigned to the GUID or false.
     *
     * @param guid playerGuid : desired playerGuid
     *
     * @return bool is_assigned_not_to
     */
    int IsAssignedNotTo(Eluna* E, GmTicket* ticket)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);

        E->Push(ticket->IsAssignedNotTo(guid));
        return 1;
    }

    /**
     * Return the [Ticket] id.
     *
     * @return unint32 ticket_id
     */
    int GetId(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetId());
        return 1;
    }

    /**
     * Return the [Player] from the [Ticket].
     *
     * @return [Player] player
     */
    int GetPlayer(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetPlayer());
        return 1;
    }

    /**
     * Return the [Player] name from the [Ticket].
     *
     * @return string player_name
     */
    int GetPlayerName(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetPlayerName());
        return 1;
    }

    /**
     * Returns the message sent in the [Ticket].
     *
     * @return string message
     */
    int GetMessage(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetMessage());
        return 1;
    }

    /**
     * Returns the assigned [Player].
     *
     * @return [Player] assigned_player
     */
    int GetAssignedPlayer(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetAssignedPlayer());
        return 1;
    }

    /**
     * Returns the assigned guid.
     *
     * @return [ObjectGUID] assigned_guid
     */
    int GetAssignedToGUID(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetAssignedToGUID());
        return 1;
    }

    /**
     * Returns the last modified time from the [Ticket].
     *
     * @return uint64 last_modified
     */
    int GetLastModifiedTime(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetLastModifiedTime());
        return 1;
    }

    /**
     * Assign the [Ticket] to a player via his GUID.
     *
     * @param guid playerGuid : desired playerGuid
     * @param bool isAdmin : true if the guid is an Admin or false (default false)
     */
    int SetAssignedTo(Eluna* E, GmTicket* ticket)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        bool is_admin = E->CHECKVAL<bool>(2, false);
        ticket->SetAssignedTo(guid, is_admin);
        return 0;
    }

    /**
     * Set [Ticket] resolved by player via his GUID.
     *
     * @param guid playerGuid : desired playerGuid
     */
    int SetResolvedBy(Eluna* E, GmTicket* ticket)
    {
        ObjectGuid guid = E->CHECKVAL<ObjectGuid>(2);
        ticket->SetResolvedBy(guid);
        return 0;
    }

    /**
     * Set [Ticket] completed.
     *
     */
    int SetCompleted(Eluna* E, GmTicket* ticket)
    {
        ticket->SetCompleted();
        return 0;
    }

    /**
     * Set [Ticket] message.
     *
     * @param string message: desired message
     *
     */
    int SetMessage(Eluna* E, GmTicket* ticket)
    {
        std::string message = E->CHECKVAL<std::string>(2);

        ticket->SetMessage(message);
        return 0;
    }

    /**
     * Set [Ticket] comment.
     *
     * @param string comment: desired comment
     *
     */
    int SetComment(Eluna* E, GmTicket* ticket)
    {
        std::string comment = E->CHECKVAL<std::string>(2);

        ticket->SetComment(comment);
        return 0;
    }

    /**
     * Set [Ticket] is viewed.
     *
     */
    int SetViewed(Eluna* E, GmTicket* ticket)
    {
        ticket->SetViewed();
        return 0;
    }

    /**
     * Set [Ticket] is unassigned.
     *
     */
    int SetUnassigned(Eluna* E, GmTicket* ticket)
    {
        ticket->SetUnassigned();
        return 0;
    }

    /**
     * Set the new [Ticket] creation position.
     *
     * @param uint32 mapId
     * @param float x
     * @param float y
     * @param float z
     *
     */
    int SetPosition(Eluna* E, GmTicket* ticket)
    {
        uint32 mapId = E->CHECKVAL<uint32>(2);
        float x = E->CHECKVAL<float>(2);
        float y = E->CHECKVAL<float>(2);
        float z = E->CHECKVAL<float>(2);

        ticket->SetPosition(mapId, x, y, z);
        return 0;
    }

    /**
     * Adds a response to the [Ticket].
     *
     * @param string response: desired response
     *
     */
    int AppendResponse(Eluna* E, GmTicket* ticket)
    {
        std::string response = E->CHECKVAL<std::string>(2);

        ticket->AppendResponse(response);
        return 0;
    }

    /**
     * Return the [Ticket] response.
     *
     * @return string response
     */
    int GetResponse(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetResponse());
        return 1;
    }

    /**
     * Delete the [Ticket] response.
     *
     */
    int DeleteResponse(Eluna* E, GmTicket* ticket)
    {
        ticket->DeleteResponse();
        return 0;
    }

    /**
     * Return the [Ticket] chatlog.
     *
     * @return string chatlog
     */
    int GetChatLog(Eluna* E, GmTicket* ticket)
    {
        E->Push(ticket->GetChatLog());
        return 1;
    }
	
	ElunaRegister<GmTicket> TicketMethods[] =
	{
		{ "IsClosed", &LuaTicket::IsClosed },
		{ "IsCompleted", &LuaTicket::IsCompleted },
		{ "IsFromPlayer", &LuaTicket::IsFromPlayer },
		{ "IsAssigned", &LuaTicket::IsAssigned },
		{ "IsAssignedTo", &LuaTicket::IsAssignedTo },
		{ "IsAssignedNotTo", &LuaTicket::IsAssignedNotTo },

		{ "GetId", &LuaTicket::GetId },
		{ "GetPlayer", &LuaTicket::GetPlayer },
		{ "GetPlayerName", &LuaTicket::GetPlayerName },
		{ "GetMessage", &LuaTicket::GetMessage },
		{ "GetAssignedPlayer", &LuaTicket::GetAssignedPlayer },
		{ "GetAssignedToGUID", &LuaTicket::GetAssignedToGUID },
		{ "GetLastModifiedTime", &LuaTicket::GetLastModifiedTime },
		{ "GetResponse", &LuaTicket::GetResponse },
		{ "GetChatLog", &LuaTicket::GetChatLog },

		{ "SetAssignedTo", &LuaTicket::SetAssignedTo },
		{ "SetResolvedBy", &LuaTicket::SetResolvedBy },
		{ "SetCompleted", &LuaTicket::SetCompleted },
		{ "SetMessage", &LuaTicket::SetMessage },
		{ "SetComment", &LuaTicket::SetComment },
		{ "SetViewed", &LuaTicket::SetViewed },
		{ "SetUnassigned", &LuaTicket::SetUnassigned },
		{ "SetPosition", &LuaTicket::SetPosition },
		{ "AppendResponse", &LuaTicket::AppendResponse },
		{ "DeleteResponse", &LuaTicket::DeleteResponse }
	};
};
#endif

