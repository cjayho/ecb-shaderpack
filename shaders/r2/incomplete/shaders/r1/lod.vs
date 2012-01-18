#include "common.h"

struct vv
{
	float4 pos	: POSITION;
	float2 tc0	: TEXCOORD0;
	float4 c	: COLOR0;
};
struct vf
{
	float4 hpos	: POSITION;
	float2 tc0	: TEXCOORD0;
	float4 c	: COLOR0;
	float  fog	: FOG;
};

vf main (vv v)
{
	vf 		o;

	o.hpos 		= mul			(m_VP, v.pos);			// xform, input in world coords
	o.tc0		= v.tc0;						// copy tc
	o.c		= v.c;
	o.fog 		= calc_fogging 		(v.pos);			// fog, input in world coords

	return o;
}
