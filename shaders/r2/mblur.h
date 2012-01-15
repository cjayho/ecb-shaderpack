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

	half4 trails( half2 t_v, half2 UV )
	{
		return tex2D(s_bloom, t_v + UV);
	}


		half3 	mblur	(float2 UV, half3 pos, half3 c_original)
		{

			half4 	pos4		= half4	(pos,1.h);
			half4 	p_current	= mul	(m_current,	pos4);
			half4 	p_previous 	= mul	(m_previous,	pos4);

			//p_velocity	= clamp	(p_velocity,-MBLUR_CLAMP,+MBLUR_CLAMP);

			float zfactor =  tex2D( s_position, UV ).z / 3;

			half2 	p_velocity 	= ( m_blur * ( (p_current.xy/p_current.w)-(p_previous.xy/p_previous.w) ) );

			#ifdef USE_ECB_LTRAILS

				half2 	t_velocity 	= p_velocity * ECB_LTRAIL_VELOCITY;

			#endif

			#ifdef USE_MBLUR

			p_velocity *= saturate(zfactor-.33f)*2;

			  half4 blurred 	= 	tex2D(s_image, p_velocity + UV);
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

				blurred /= 11;
				//blurred *= zfactor;

			#endif

			#ifdef USE_ECB_LTRAILS

				#ifdef USE_TCLAMP
					t_velocity	= clamp	( t_velocity, -TRAIL_CLAMP, +TRAIL_CLAMP );
				#endif

					half4 trail		= 	trails( t_velocity, UV )*.9f;
					trail		+= 	trails( t_velocity * 2.h, UV )*.8f;
					trail		+= 	trails( t_velocity * 3.h, UV )*.7f;
					trail		+= 	trails( t_velocity * 4.h, UV )*.6f;
					trail		+= 	trails( t_velocity * 5.h, UV )*.5f;
					trail		+= 	trails( t_velocity * 6.h, UV )*.4f;
					trail		+= 	trails( t_velocity * 7.h, UV )*.3f;
					trail		+= 	trails( t_velocity * 8.h, UV )*.2f;
					trail		+= 	trails( t_velocity * 9.h, UV )*.1f;

				trail = ( trail * ECB_LTRAIL_FACTOR / 9 ) * saturate( tex2D( s_position, UV ).z - 0.99f );

				#ifdef USE_LTRAIL_THRESHOLD
					trail *= saturate( abs( dot( t_velocity, LTRAIL_THRESHOLD ) ) );
				#endif

			#endif


			#if defined( USE_MBLUR ) && defined( USE_ECB_LTRAILS )
				return 	((dof( UV, (half3) c_original ) + blurred.rgb)/2) + trail.rgb;
			#else
				#ifdef USE_MBLUR
					return 	((dof( UV, (half3) c_original ) + blurred.rgb)/2);
				#endif

				#ifdef USE_ECB_LTRAILS
					return 	dof( UV, (half3) c_original ) + trail.rgb;
				#endif
			#endif

			return 	dof( UV, (half3) c_original );
		}

	#endif

#endif
