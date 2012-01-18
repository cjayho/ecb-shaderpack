#include "common.h"

struct 	a2v
{
	float4 P:	 	POSITION;	// Object-space position
 	float4 tc0:		TEXCOORD0;	// Texture coordinates
};

//////////////////////////////////////////////////////////////////////////////////////////
// Vertex
v_shadow_direct_aref 	main	( a2v  	I )
{
	v_shadow_direct_aref 	O;
	O.hpos 	= mul		(m_WVP,	I.P	);
	O.tc0 	= I.tc0;
#ifndef USE_HWSMAP
	O.depth = O.hpos.z;
#endif
 	return	O;
}
FXVS;
