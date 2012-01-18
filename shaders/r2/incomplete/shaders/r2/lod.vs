#include "common.h"

p_flat 	main	( v_static I )
{
	// Eye-space pos/normal
	p_flat 		O;
	O.hpos 		= mul		(m_WVP,			I.P	);
	float3	Pe	= mul		(m_WV,  		I.P	);
	float3 	Ne	= mul		((float3x3)m_WV,	I.Nh	);

	O.tcdh 		= float2	(I.tc			);
	O.position	= float4	(Pe, 		I.Nh.w	);
	O.N 		= float3 	(Ne			);

	return	O;
}
FXVS;
