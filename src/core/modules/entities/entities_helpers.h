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

#ifndef _ENTITIES_HELPERS_H
#define _ENTITIES_HELPERS_H

//-----------------------------------------------------------------------------
// Includes.
//-----------------------------------------------------------------------------
#include "toolframework/itoolentity.h"
#include "modules/memory/memory_tools.h"
#include "utilities/conversions.h"


//-----------------------------------------------------------------------------
// External variables.
//-----------------------------------------------------------------------------
extern IServerTools *servertools;


//-----------------------------------------------------------------------------
// Creates an entity of the given name and returns its index...
//-----------------------------------------------------------------------------
unsigned int create_entity(const char *szClassName)
{
	CBaseEntity *pBaseEntity = (CBaseEntity *)servertools->CreateEntityByName(szClassName);

	if (!pBaseEntity)
		BOOST_RAISE_EXCEPTION(PyExc_TypeError, "Unable to create an entity of type \"%s\".", szClassName);

	return IndexFromBaseEntity(pBaseEntity);
}


//-----------------------------------------------------------------------------
// Spawns the given entity index...
//-----------------------------------------------------------------------------
void spawn_entity(unsigned int uiEntityIndex)
{
	servertools->DispatchSpawn(BaseEntityFromIndex(uiEntityIndex, true));
}


#endif // _ENTITIES_HELPERS_H
