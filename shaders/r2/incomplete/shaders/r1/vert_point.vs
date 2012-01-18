#include "common.h"

vf_point main (v_vert v)
{
	vf_point	o;

	o.hpos 		= mul			(m_VP, v.pos);					// xform, input in world coords
	o.tc0		= unpack_tc_base	(v.tc);						// copy tc
	o.color		= calc_point 		(o.tc1,o.tc2,v.pos,unpack_normal(v.norm));	// just hemisphere

	return o;
}
