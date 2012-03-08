#ifndef	MBLUR_H
#define MBLUR_H

	#include "dof.h"

	#if !defined( USE_MBLUR ) && !defined( ECB_LTRAILS )
		half3 	mblur	(float2 UV, half3 pos, half3 c_original)	{ return dof( UV, c_original ) ; }
	#else

		#include "common.h"

		uniform half4x4	m_current;
		uniform half4x4	m_previous;
		uniform half2 	m_blur;		// scale_x / 12, scale_y / 12

		half3 	mblur	(float2 UV, half3 pos, half3 c_original)
		{

			half4 	pos4		= half4	(pos,1.h);
			half4 	p_current	= mul	(m_current,	pos4);
			half4 	p_previous 	= mul	(m_previous,	pos4);

			//p_velocity	= clamp	(p_velocity,-MBLUR_CLAMP,+MBLUR_CLAMP);

			half2 	p_velocity 	= ( m_blur * ( (p_current.xy/p_current.w)-(p_previous.xy/p_previous.w) ) )/3;

			#ifdef USE_MBLUR

			  half4 blurred 	= 	(half4) 0; //tex2D(s_image, p_velocity + UV);
					blurred		+= 	tex2D(s_image, p_velocity * 2.h  + UV);
					blurred		+= 	tex2D(s_image, p_velocity * 3.h  + UV);
					blurred		+= 	tex2D(s_image, p_velocity * 4.h  + UV);
					blurred 	+= 	tex2D(s_image, p_velocity * 5.h  + UV);
					blurred		+= 	tex2D(s_image, p_velocity * 6.h  + UV);
					blurred		+= 	tex2D(s_image, p_velocity * 7.h  + UV);
					blurred		+= 	tex2D(s_image, p_velocity * 8.h  + UV);
					blurred 	+= 	tex2D(s_image, p_velocity * 9.h  + UV);
					blurred		+= 	tex2D(s_image, p_velocity * 10.h + UV);
					blurred		+= 	tex2D(s_image, p_velocity * 11.h + UV);

				blurred /= 10;

			#endif

			#ifdef ECB_LTRAILS

				half2 	t_velocity 	= p_velocity * 3 * ECB_LTRAIL_VELOCITY;

				#ifdef ECB_LTRAIL_CLAMP
					t_velocity	= clamp	( t_velocity, -ECB_LTRAIL_CLAMP_VALUE, +ECB_LTRAIL_CLAMP_VALUE );
				#endif

			  half4 trail		= 	tex2D(s_bloom, t_velocity + UV)*.9f;
					trail		+= 	tex2D(s_bloom, t_velocity * 2.h  + UV)*.8f;
					trail		+= 	tex2D(s_bloom, t_velocity * 3.h  + UV)*.7f;
					trail		+= 	tex2D(s_bloom, t_velocity * 4.h  + UV)*.6f;
					trail		+= 	tex2D(s_bloom, t_velocity * 5.h  + UV)*.5f;
					trail		+= 	tex2D(s_bloom, t_velocity * 6.h  + UV)*.4f;
					trail		+= 	tex2D(s_bloom, t_velocity * 7.h  + UV)*.3f;
					trail		+= 	tex2D(s_bloom, t_velocity * 8.h  + UV)*.2f;
					trail		+= 	tex2D(s_bloom, t_velocity * 9.h  + UV)*.1f;

				trail = ( trail * ECB_LTRAIL_FACTOR / 9 );

				#ifdef ECB_LTRAIL_USE_THRESHOLD
					trail *= saturate( abs( dot( t_velocity, ECB_LTRAIL_THRESHOLD ) ) );
				#endif

			#endif


			#if defined( USE_MBLUR ) && defined( ECB_LTRAILS )
				return 	((dof( UV, (half3) c_original ) + blurred.rgb)/2) + trail.rgb;
			#else
				#ifdef USE_MBLUR
					return 	((dof( UV, (half3) c_original ) + blurred.rgb)/2);
				#endif

				#ifdef ECB_LTRAILS
					return 	dof( UV, (half3) c_original ) + trail.rgb;
				#endif
			#endif

			return 	dof( UV, (half3) c_original );
		}

	#endif

#endif
