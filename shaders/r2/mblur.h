#ifndef	MBLUR_H
#define MBLUR_H

#include "dof.h"

#if !defined( USE_MBLUR ) && !defined( USE_ECB_LTRAILS )
	half3 	mblur	(float2 UV, half3 pos, half3 c_original)	{ return dof( UV, c_original ) ; }
#else

#include "common.h"

uniform half4x4	m_current;
uniform half4x4	m_previous;
uniform half2 	m_blur;		// scale_x / 12, scale_y / 12

#define MBLUR_SAMPLES 	half(11)
//#define MBLUR_CLAMP	half(0.001)

half3 	mblur	(float2 UV, half3 pos, half3 c_original)	{
	half4 	pos4		= half4	(pos,1.h);

	half4 	p_current	= mul	(m_current,	pos4);
	half4 	p_previous 	= mul	(m_previous,	pos4);

		//p_velocity	= clamp	(p_velocity,-MBLUR_CLAMP,+MBLUR_CLAMP);

	// For each sample, sum up each sample's color in "Blurred" and then divide
	// to average the color after all the samples are added.

#ifdef USE_MBLUR

	half2 	p_velocity 	= ( m_blur * ( (p_current.xy/p_current.w)-(p_previous.xy/p_previous.w) ) );

	half3 	blurred 	= 	(half3) 0; //c_original	;
		blurred 	+= 	tex2D(s_image, p_velocity + UV).rgb;
		blurred		+= 	tex2D(s_image, p_velocity * 2.h  + UV).rgb;
		blurred		+= 	tex2D(s_image, p_velocity * 3.h  + UV).rgb;
		blurred		+= 	tex2D(s_image, p_velocity * 4.h  + UV).rgb;
		blurred 	+= 	tex2D(s_image, p_velocity * 5.h  + UV).rgb;
		blurred		+= 	tex2D(s_image, p_velocity * 6.h  + UV).rgb;
		blurred		+= 	tex2D(s_image, p_velocity * 7.h  + UV).rgb;
		blurred		+= 	tex2D(s_image, p_velocity * 8.h  + UV).rgb;
		blurred 	+= 	tex2D(s_image, p_velocity * 9.h  + UV).rgb;
		blurred		+= 	tex2D(s_image, p_velocity * 10.h + UV).rgb;
		blurred		+= 	tex2D(s_image, p_velocity * 11.h + UV).rgb;

	blurred /= MBLUR_SAMPLES;
#endif

#ifdef USE_ECB_LTRAILS

	half2 	t_velocity 	= ( m_blur * ( (p_current.xy/p_current.w)-(p_previous.xy/p_previous.w) ) )*ECB_LTRAIL_VELOCITY;

	half3 	trail 	= 	(half3) 0; //c_original	;
		trail		+= 	tex2D(s_bloom, t_velocity + UV).rgb;
		trail		+= 	tex2D(s_bloom, t_velocity * 2.h  + UV).rgb;
		trail		+= 	tex2D(s_bloom, t_velocity * 3.h  + UV).rgb*.9f;
		trail		+= 	tex2D(s_bloom, t_velocity * 4.h  + UV).rgb*.8f;
		trail		+= 	tex2D(s_bloom, t_velocity * 5.h  + UV).rgb*.7f;
		trail		+= 	tex2D(s_bloom, t_velocity * 6.h  + UV).rgb*.6f;
		trail		+= 	tex2D(s_bloom, t_velocity * 7.h  + UV).rgb*.5f;
		trail		+= 	tex2D(s_bloom, t_velocity * 8.h  + UV).rgb*.4f;
		trail		+= 	tex2D(s_bloom, t_velocity * 9.h  + UV).rgb*.3f;
		trail		+= 	tex2D(s_bloom, t_velocity * 10.h + UV).rgb*.2f;
		trail		+= 	tex2D(s_bloom, t_velocity * 11.h + UV).rgb*.1f;

	trail *= ECB_LTRAIL_FACTOR;

	trail /= MBLUR_SAMPLES;
#endif


#if defined( USE_MBLUR ) && defined( USE_ECB_LTRAILS )
	return 	((dof( UV, (half3) c_original ) + blurred)/2) + trail;
#else
	#ifdef USE_MBLUR
		return 	((dof( UV, (half3) c_original ) + blurred)/2);
	#endif

	#ifdef USE_ECB_LTRAILS
		return 	dof( UV, (half3) c_original ) + trail;
	#endif
#endif

	return 	dof( UV, (half3) c_original );
}
#endif

#endif
