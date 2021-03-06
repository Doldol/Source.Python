/**
* =============================================================================
* Source Python
* Copyright (C) 2012-2015 Source Python Development Team.  All rights reserved.
* =============================================================================
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License, version 3.0, as published by the
* Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
* details.
*
* You should have received a copy of the GNU General Public License along with
* this program.  If not, see <http://www.gnu.org/licenses/>.
*
* As a special exception, the Source Python Team gives you permission
* to link the code of this program (as well as its derivative works) to
* "Half-Life 2," the "Source Engine," and any Game MODs that run on software
* by the Valve Corporation.  You must obey the GNU General Public License in
* all respects for all other code used.  Additionally, the Source.Python
* Development Team grants this exception to all derivative works.
*/

//-----------------------------------------------------------------------------
// Includes.
//-----------------------------------------------------------------------------
#include "players_generator.h"
#include "export_main.h"
#include "modules/memory/memory_tools.h"

#include "game/shared/shareddefs.h"
#include "game/shared/usercmd.h"
#include "public/game/server/iplayerinfo.h"
#include "iclient.h"
#include "inetchannelinfo.h"
#include "inetchannel.h"
#include "players_wrap.h"

#include ENGINE_INCLUDE_PATH(players_wrap.h)


//-----------------------------------------------------------------------------
// Forward declarations.
//-----------------------------------------------------------------------------
void export_playerinfo(scope);
void export_player_generator(scope);
void export_client(scope);
void export_user_cmd(scope);


//-----------------------------------------------------------------------------
// Declare the _players module.
//-----------------------------------------------------------------------------
DECLARE_SP_MODULE(_players)
{
	export_playerinfo(_players);
	export_player_generator(_players);
	export_client(_players);
	export_user_cmd(_players);
}


//-----------------------------------------------------------------------------
// Exports IPlayerInfo.
//-----------------------------------------------------------------------------
void export_playerinfo(scope _players)
{
	class_<IPlayerInfo, boost::noncopyable>("PlayerInfo", no_init)
		.def("get_name",
			&IPlayerInfoExt::GetName,
			"Returns the player's name"
		)

		.def("get_userid",
			&IPlayerInfo::GetUserID,
			"Returns the player's userid."
		)

		.def("get_networkid_string",
			&IPlayerInfo::GetNetworkIDString,
			"Returns the player's SteamID."
		)

		.def("get_team_index",
			&IPlayerInfo::GetTeamIndex,
			"Returns the player's team number."
		)

		.def("change_team",
			&IPlayerInfo::ChangeTeam,
			"Moves the player to the given team.",
			args("team_number")
		)

		.def("get_frag_count",
			&IPlayerInfo::GetFragCount,
			"Returns the player's frag count."
		)
		
		.def("get_death_count",
			&IPlayerInfo::GetDeathCount,
			"Returns the player's death count."
		)

		.def("is_connected",
			&IPlayerInfo::IsConnected,
			"Returns whether the player is connected."
		)

		.def("get_armor_value",
			&IPlayerInfo::GetArmorValue,
			"Returns the player's armor value."
		)

		.def("is_hltv",
			&IPlayerInfo::IsHLTV,
			"Returns whether the player is HLTV."
		)

		.def("is_player",
			&IPlayerInfo::IsPlayer,
			"Returns whether the player is a client."
		)

		.def("is_fake_client",
			&IPlayerInfo::IsFakeClient,
			"Returns whether the player is a fake client."
		)

		.def("is_dead",
			&IPlayerInfo::IsDead,
			"Returns whether the player is dead."
		)

		.def("is_in_a_vehicle",
			&IPlayerInfo::IsInAVehicle,
			"Returns whether the player is in a vehicle."
		)

		.def("is_observer",
			&IPlayerInfo::IsObserver,
			"Returns whether the player is an observer."
		)

		.def("get_abs_origin",
			&IPlayerInfo::GetAbsOrigin,
			"Returns the player's origin Vector instance."
		)

		.def("get_abs_angles",
			&IPlayerInfo::GetAbsAngles,
			"Returns the player's angle QAngle instance."
		)

		.def("get_player_mins",
			&IPlayerInfo::GetPlayerMins,
			"Returns the player's min Vector instance."
		)

		.def("get_player_maxs",
			&IPlayerInfo::GetPlayerMaxs,
			"Returns the player's max Vector instance."
		)

		.def("get_weapon_name",
			&IPlayerInfo::GetWeaponName,
			"Returns the name of the weapon the player is carrying."
		)

		.def("get_model_name",
			&IPlayerInfo::GetModelName,
			"Returns the name of the player's model."
		)

		.def("get_health",
			&IPlayerInfo::GetHealth,
			"Returns the player's health."
		)

		.def("get_max_health",
			&IPlayerInfo::GetMaxHealth,
			"Returns the player's maximum health."
		)
		
		.def("get_last_user_command",
			&IPlayerInfo::GetLastUserCommand
		)

		ADD_MEM_TOOLS(IPlayerInfo)
	;
}


//-----------------------------------------------------------------------------
// Exports CPlayerGenerator.
//-----------------------------------------------------------------------------
void export_player_generator(scope _players)
{
	class_<CPlayerGenerator>("PlayerGenerator")
		.def("__iter__",
			&CPlayerGenerator::iter,
			"Returns the iterable object."
		)

		.def("__next__",
			&CPlayerGenerator::next,
			"Returns the next valid instance.",
			reference_existing_object_policy()
		)
	;
}


//-----------------------------------------------------------------------------
// Exports IClient.
//-----------------------------------------------------------------------------
void export_client(scope _players)
{
	class_<IClient, IClient*, bases<INetChannelHandler>, boost::noncopyable> Client("Client", no_init);

	Client.def(
		"get_client_name",
		&IClient::GetClientName,
		"Return the client's name."
	);

	Client.def(
		"get_net_channel",
		&IClient::GetNetChannel,
		reference_existing_object_policy()
	);

	// TODO: Export more

	Client ADD_MEM_TOOLS(IClient);
}


//-----------------------------------------------------------------------------
// Exports CUserCmd.
//-----------------------------------------------------------------------------
void export_user_cmd(scope _players)
{
	class_<CUserCmd, CUserCmd*> UserCmd("UserCmd");

	UserCmd.def(
		"reset",
		&CUserCmd::Reset
	);

	UserCmd.def(
		"get_checksum",
		&CUserCmd::GetChecksum
	);

	UserCmd.def_readwrite("command_number",
		&CUserCmd::command_number,
		"For matching server and client commands for debugging."
	);

	UserCmd.def_readwrite("tick_count",
		&CUserCmd::tick_count,
		"The tick the client created this command."
	);

	UserCmd.def_readwrite("view_angles",
		&CUserCmd::viewangles,
		"Player instantaneous view angles."
	);

	UserCmd.NOT_IMPLEMENTED("aim_direction");

	UserCmd.def_readwrite("forward_move",
		&CUserCmd::forwardmove,
		"Forward velocity."
	);

	UserCmd.def_readwrite("side_move",
		&CUserCmd::sidemove,
		"Sideways velocity."
	);

	UserCmd.def_readwrite("up_move",
		&CUserCmd::upmove,
		"Upward velocity."
	);

	UserCmd.def_readwrite("buttons",
		&CUserCmd::buttons,
		"Button states."
	);

	UserCmd.def_readwrite("impulse",
		&CUserCmd::impulse,
		"Impulse command."
	);

	UserCmd.def_readwrite("weaponselect",
		&CUserCmd::weaponselect,
		"Current weapon ID."
	);

	UserCmd.def_readwrite("weaponsubtype",
		&CUserCmd::weaponsubtype,
		"Current weapon ID."
	);

	UserCmd.def_readwrite("random_seed",
		&CUserCmd::random_seed,
		"For shared random functions."
	);

	UserCmd.def_readwrite("mousedx",
		&CUserCmd::mousedx,
		"Mouse accum in x from create move."
	);

	UserCmd.def_readwrite("mousedy",
		&CUserCmd::mousedy,
		"Mouse accum in y from create move."
	);

	UserCmd.def_readwrite("has_been_predicted",
		&CUserCmd::hasbeenpredicted,
		"Client only, tracks whether we've predicted this command at least once."
	);
	
	UserCmd.NOT_IMPLEMENTED("head_angles");
	UserCmd.NOT_IMPLEMENTED("head_offset");

	export_engine_specific_user_cmd(_players, UserCmd);

	UserCmd ADD_MEM_TOOLS(CUserCmd);
}
