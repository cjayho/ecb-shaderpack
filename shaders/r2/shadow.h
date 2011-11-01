#ifndef	SHADOW_H
#define SHADOW_H

#include "common.h"

//uniform	sampler	s_smap	: register(ps,s0);	// 2D/cube shadowmap

/*
Modded by cj ayho (ecb team). 29.08.2010 
���� ����������� - ���������� ������ �����.
*/



//////////////////////////////////////////////////////////////////////////////////////////
// software
//////////////////////////////////////////////////////////////////////////////////////////
half 	sample_sw	(float2 tc, float2 shift, float depth_cmp)
{
	static const float 	ts = ECB_SHADOW_KERNEL / float(SMAP_size);
	tc 		+= 		shift*ts;

	float  	texsize = SMAP_size;
	float  	offset 	= 0.5f/texsize;
	float2 	Tex00 	= tc + float2(-offset, -offset);
	float2 	Tex01 	= tc + float2(-offset,  offset);
	float2 	Tex10 	= tc + float2( offset, -offset);
	float2 	Tex11 	= tc + float2( offset,  offset);
	float4 	depth 	= float4(
		depth_cmp-tex2D	(s_smap, Tex00).x,
		depth_cmp-tex2D	(s_smap, Tex01).x,
		depth_cmp-tex2D	(s_smap, Tex10).x,
		depth_cmp-tex2D	(s_smap, Tex11).x);
	half4 	compare = step	(depth,0);
	float2 	fr 		= frac	(Tex00*texsize);
	half2 	ifr 	= half2	(1,1) - fr;
	half4 	fr4 	= half4	(ifr.x*ifr.y, ifr.x*fr.y, fr.x*ifr.y,  fr.x*fr.y);
	return	dot		(compare, fr4);
}
half 	shadow_sw	(float4 tc)	{ 
	float2	tc_dw	= tc.xy / tc.w;
	half4	s;
	s.x	= sample_sw	(tc_dw,float2(-1,-1),tc.z); 
	s.y	= sample_sw	(tc_dw,float2(+1,-1),tc.z); 
	s.z	= sample_sw	(tc_dw,float2(-1,+1),tc.z); 
	s.w	= sample_sw	(tc_dw,float2(+1,+1),tc.z);
	return	dot		(s, 1.h/4.h);
}

//////////////////////////////////////////////////////////////////////////////////////////
// hardware + PCF
//////////////////////////////////////////////////////////////////////////////////////////
half  	sample_hw_pcf	(float4 tc,float4 shift){
	static const float 	ts = ECB_SHADOW_KERNEL / float(SMAP_size);

//	half tst = tex2Dproj( s_smap, tc + tc.w * shift * ts ).x;
//	return tst;

	float4 tc2 = tc / tc.w + shift * ts;
	tc2.w = 0;
	return tex2Dlod(s_smap, tc2);

}
half 	shadow_hw	( float4 tc )
{

/*
Modded by cj ayho (ecb team). 29.08.2010. ���� ����������� - ���������� ������ �����.
version 1.1 by cj ayho (ecb team) 13.04.2011 - �����������

<mod>
*/

  half4 s0;

  int n = ECB_SHADOW_STEPS;

	for( int i = 0; i < n; i++ )
	{

		int ii = i + 1;
		int iii = i + 2;

					s0.x += sample_hw_pcf ( tc, float4( -i, -i, 0, 0 ) );
					s0.y += sample_hw_pcf ( tc, float4( +i, -i, 0, 0 ) );
					s0.z += sample_hw_pcf ( tc, float4( -i, +i, 0, 0 ) );
					s0.w += sample_hw_pcf ( tc, float4( +i, +i, 0, 0 ) );

					s0.x += sample_hw_pcf ( tc, float4( 0, +i, 0, 0 ) );
					s0.y += sample_hw_pcf ( tc, float4( 0, -i, 0, 0 ) );
					s0.z += sample_hw_pcf ( tc, float4( +i, 0, 0, 0 ) );
					s0.w += sample_hw_pcf ( tc, float4( -i, 0, 0, 0 ) );

					s0.x += sample_hw_pcf ( tc, float4( -ii, -ii, 0, 0 ) );
					s0.y += sample_hw_pcf ( tc, float4( +ii, -ii, 0, 0 ) );
					s0.z += sample_hw_pcf ( tc, float4( -ii, +ii, 0, 0 ) );
					s0.w += sample_hw_pcf ( tc, float4( +ii, +ii, 0, 0 ) );

					s0.x += sample_hw_pcf ( tc, float4( 0, +ii, 0, 0 ) );
					s0.y += sample_hw_pcf ( tc, float4( 0, -ii, 0, 0 ) );
					s0.z += sample_hw_pcf ( tc, float4( +ii, 0, 0, 0 ) );
					s0.w += sample_hw_pcf ( tc, float4( -ii, 0, 0, 0 ) );

					s0.x += sample_hw_pcf ( tc, float4( -iii, -iii, 0, 0 ) );
					s0.y += sample_hw_pcf ( tc, float4( +iii, -iii, 0, 0 ) );
					s0.z += sample_hw_pcf ( tc, float4( -iii, +iii, 0, 0 ) );
					s0.w += sample_hw_pcf ( tc, float4( +iii, +iii, 0, 0 ) );

					s0.x += sample_hw_pcf ( tc, float4( 0, +iii, 0, 0 ) );
					s0.y += sample_hw_pcf ( tc, float4( 0, -iii, 0, 0 ) );
					s0.z += sample_hw_pcf ( tc, float4( +iii, 0, 0, 0 ) );
					s0.w += sample_hw_pcf ( tc, float4( -iii, 0, 0, 0 ) );

	}

	return dot ( s0, 1.f / ( 24 * n ) );
/*
</mod>
*/

}


half 	shadow_nb	( float4 tc )
{
	return sample_hw_pcf ( tc, float4( 0, 0, 0, 0 ) );
}

//////////////////////////////////////////////////////////////////////////////////////////
// hardware (ATI) + DF24/Fetch4
//////////////////////////////////////////////////////////////////////////////////////////

/*
half  	sample_hw_f4	(float4 tc,float4 shift){
	static const float 	ts 	= ECB_SHADOW_KERNEL / 	float(SMAP_size);
	float4	D4				= tex2Dproj	(s_smap,tc + tc.w*shift*ts);
	float4 	dcmp			= tc.z/tc.w	;
	float4	cmp				= dcmp<D4	;
	return 	dot	(cmp,1.h/4.h);
}
*/

half  	sample_hw_f4	(float4 tc,float4 shift){
	static const float 	ts 	= 	ECB_SHADOW_KERNEL / 	float(SMAP_size);
	float4 	T4				= 	tc/tc.w		;
			T4.xy			+=	shift.xy*ts	;

	float4	D4				= 	tex2D		(s_smap, T4);
	float4	compare			= 	T4.z<D4		;

	float  	texsize 		= 	SMAP_size	;
	float2 	fr 				= 	frac		(T4.xy * texsize);
	half2 	ifr 			= 	half2		(1,1) - fr;
	half4 	fr4 			= 	half4		(ifr.x*ifr.y, ifr.x*fr.y, fr.x*ifr.y,  fr.x*fr.y);
	half4 	fr4s		 	= 	fr4.zywx	;

	return	dot	(compare, fr4s)	;
	// return 	dot	(compare, 1.h/4.h)	;
}


half 	shadow_hw_f4	(float4 tc)		{
  half  s0	= half4( sample_hw_f4	(tc,float4(-1,-1,0,0)), sample_hw_f4	(tc,float4(+1,-1,0,0)), sample_hw_f4	(tc,float4(-1,+1,0,0)), sample_hw_f4	(tc,float4(+1,+1,0,0)) );
  return	dot( s0, 1.h/4.h );
}


//////////////////////////////////////////////////////////////////////////////////////////
// select hardware or software shadowmaps
//////////////////////////////////////////////////////////////////////////////////////////
#ifdef	USE_HWSMAP_PCF
	// D24X8+PCF
	half 	shadow		(float4	tc)		{ return shadow_hw	(tc);	}
#else
	#ifdef USE_FETCH4
		// DF24+Fetch4
		half 	shadow 		(float4 tc)		{ return shadow_hw_f4(tc);	}
	#else
		// FP32
		half 	shadow		(float4 tc) 	{ return shadow_sw	(tc);	}
	#endif
#endif

//////////////////////////////////////////////////////////////////////////////////////////
// testbed

uniform sampler2D	jitter0;
uniform sampler2D	jitter1;
uniform sampler2D	jitter2;
uniform sampler2D	jitter3;
uniform half4 		jitterS;
half4 	test 		(float4 tc, half2 offset)
{
	float4	tcx	= float4 (tc.xy + tc.w*offset, tc.zw);
	return 	tex2Dproj (s_smap,tcx);
}
half 	shadowtest 	(float4 tc, float4 tcJ)				// jittered sampling
{
	half4	r;

	const 	float 	scale 	= (2.7f/float(SMAP_size));
	half4	J0 	= tex2Dproj	(jitter0,tcJ)*scale;
	half4	J1 	= tex2Dproj	(jitter1,tcJ)*scale;

		r.x 	= test 	(tc,J0.xy).x;
		r.y 	= test 	(tc,J0.wz).y;
		r.z		= test	(tc,J1.xy).z;
		r.w		= test	(tc,J1.wz).x;

	return	dot(r,1.h/4.h);
}
half 	shadowtest_sun 	(float4 tc, float4 tcJ)			// jittered sampling
{
	half4	r;

//	const 	float 	scale 	= (2.0f/float(SMAP_size));
	const 	float 	scale 	= (0.7f/float(SMAP_size));
	half4	J0 	= tex2D	(jitter0,tcJ)*scale;
	half4	J1 	= tex2D	(jitter1,tcJ)*scale;

		r.x 	= test 	(tc,J0.xy).x;
		r.y 	= test 	(tc,J0.wz).y;
		r.z		= test	(tc,J1.xy).z;
		r.w		= test	(tc,J1.wz).x;

	return	dot(r,1.h/4.h);
}

//////////////////////////////////////////////////////////////////////////////////////////
#ifdef  USE_SUNMASK	
uniform float3x4	m_sunmask	;				// ortho-projection
half 	sunmask		(float4 P)	{				// 
	float2 		tc	= mul	(m_sunmask, P);		//
	return 		tex2D 		(s_lmap,tc).w*0.75;		// A8 
	
}
#else
half 	sunmask		(float4 P)	{ return 0.75; }	// 
#endif

//////////////////////////////////////////////////////////////////////////////////////////
uniform float4x4	m_shadow;

#endif
