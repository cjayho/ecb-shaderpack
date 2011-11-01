#ifndef        HMODEL_H
#define HMODEL_H

#include "common.h"

uniform samplerCUBE 	env_s0		;
uniform samplerCUBE 	env_s1		;
uniform half4 		env_color	;	// color.w  = lerp factor
uniform half3x4		m_v2w		;

void        hmodel                 (out half3 hdiffuse, out half3 hspecular, half m, half h, half s, float3 point, half3 normal)
{
        // hscale - something like diffuse reflection
        half3         nw                         = mul                 (m_v2w,normal);
        half         hscale                 = h;                                //. *        (.5h + .5h*nw.y);
#ifdef         USE_GAMMA_22
                        hscale                = (hscale*hscale);        // make it more linear
#endif

	// reflection vector
	float3	v2pointL= normalize	(point);
	half3 	v2point	= mul		(m_v2w,v2pointL);
	half3	vreflect= reflect 	(v2point,nw);

	half 	hspec 	= /*.5h+.5h**/dot	(vreflect,v2point);

	// material
  	half4 	light	= tex3D		(s_material, half3(hscale, hspec, m) );		// sample material

	// diffuse color
	half3 	e0d 	= texCUBE 	(env_s0,nw);
	half3 	e1d 	= texCUBE 	(env_s1,nw);
	half3 	env_d 	= env_color.xyz*lerp(e0d,e1d,env_color.w)	;

	// specular color
	half3 	e0s 	= texCUBE 	(env_s0,vreflect);
	half3 	e1s 	= texCUBE 	(env_s1,vreflect);
	half3 	env_s  	= env_color.xyz*lerp(e0s,e1s,env_color.w)	;

	hdiffuse	= env_d	*light.xyz 	+ sat( half4( L_ambient.rgb, 1 ), ECB_DIFFUSE_AMBIENT_SAT ).rgb; // (L_ambient.rgb*1.4)	- (L_sun_color.xyz*0.13f);

	hspecular	= env_s	*light.w 	* s * ECB_SPECULAR;
}

void         hmodel_table        (out half3 hdiffuse, out half3 hspecular, half m, half h, half s, half3 point, half3 normal)
{
	// hscale - something like diffuse reflection
	half 	hscale 	= h;

#ifdef         USE_GAMMA_22
                        hscale                = (hscale*hscale);        // make it more linear
#endif

	// reflection vector
	half3 	v2point	= normalize	(point);
	half3	vreflect= reflect 	(v2point,normal);

	half 	hspec 	= /*.5h+.5h**/dot	(vreflect,v2point);

	// material
  	half4 	light	= tex3D		(s_material, half3(hscale, hspec, m) );		// sample material

	// diffuse color
	half3 	env_d 	= texCUBE 	(env_s0,normal);

	// specular color
	half3 	env_s  	= texCUBE 	(env_s0,vreflect);

	hdiffuse	= env_d	*light.xyz 	+ sat( half4( L_ambient.rgb, 1 ), ECB_DIFFUSE_AMBIENT_SAT ).rgb; // (L_ambient.rgb*1.4)	- (L_sun_color.xyz*0.13f);

	hspecular	= env_s	*light.w 	* s * ECB_SPECULAR;
}

#endif
