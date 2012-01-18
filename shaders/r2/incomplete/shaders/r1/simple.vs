#include "common.h"

struct vf
{
	float4 hpos	: POSITION;
	float2 tc0	: TEXCOORD0;
	float  fog	: FOG;
};

vf main (v_vert v)
{
	vf 		o;

	o.hpos 		= mul			(m_VP, v.pos);			// xform, input in world coords
	o.tc0		= unpack_tc_base	(v.tc);				// copy tc
	o.fog 		= calc_fogging 		(v.pos);			// fog, input in world coords

	return o;
}
