//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Handling for the suit batteries.
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "hl2_player.h"
#include "basecombatweapon.h"
#include "gamerules.h"
#include "items.h"
#include "engine/IEngineSound.h"
//////////ADD/////////////////////////////////////////////////////////
#include "dlight.h"
#include "iefx.h"
//////////ADD/////////////////////////////////////////////////////////

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//////////ADD/////////////////////////////////////////////////////////
IVEfx *effects;
//////////ADD/////////////////////////////////////////////////////////
class CItemBattery : public CItem
{
public:
	DECLARE_CLASS( CItemBattery, CItem );

	void Spawn( void )
	{ 
		Precache( );
		SetModel( "models/items/battery.mdl" );
		BaseClass::Spawn( );
		//////////ADD/////////////////////////////////////////////////////////
			Vector vAttachment, vAng;
			QAngle angles;
			GetAttachment( 1, vAttachment, angles );

			AngleVectors( angles, &vAng );
			vAttachment += vAng;
		
			dlight_t *dl = effects->CL_AllocDlight ( -1 );
			dl->origin = vAttachment;
			dl->color.r = 140;
			dl->color.g = 180;
			dl->color.b = 255;
			dl->radius = random->RandomFloat( 140.0f, 156.0f ); // 245.0 256.0
			dl->decay = 512.0f;
		/////////ADD//////////////////////////////////////////////////////////
	}
	void Precache( void )
	{
		PrecacheModel ("models/items/battery.mdl");

		PrecacheScriptSound( "ItemBattery.Touch" );

	}
	bool MyTouch( CBasePlayer *pPlayer )
	{
		CHL2_Player *pHL2Player = dynamic_cast<CHL2_Player *>( pPlayer );
		/////////ADD//////////////////////////////////////////////////////////
			dlight_t *dl = effects->CL_AllocDlight ( -1 );
		    dl->die;
		/////////ADD//////////////////////////////////////////////////////////
		return ( pHL2Player && pHL2Player->ApplyBattery() );
	}
};

LINK_ENTITY_TO_CLASS(item_battery, CItemBattery);
PRECACHE_REGISTER(item_battery);

