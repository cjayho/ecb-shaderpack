#ifndef	DOF_H_INCLUDED
#define	DOF_H_INCLUDED

#ifndef	USE_DOF

half3	dof(float2 center, half3 sum)
{
	return	sum;
}

#else	//	USE_DOF

#ifndef ecb_rd
	uniform half4 e_barrier;
	uniform half4 e_weights;
	uniform half4 e_kernel;
#endif

half3	dof(float2 center, half3 sum)
{

	float dep = tex2D( s_position, center ).z;
	float targetDist = tex2D( s_position, float2( 0.500001f, 0.500001f ) ).z;

	float mycof = MAXCOF;
	float myMINDIST = MINDIST;
	float myMAXDIST = MAXDIST;
	float myMAXNEAR = MAXNEAR;
	float myMINNEAR = MINNEAR;

	#ifdef ECB_USE_DDOF

		if (targetDist < MAXDIST && targetDist > DDOF_MINDIST)
		{
			myMINDIST = targetDist + DDOF_MINDIST_ADD;
			float maxFactor = (targetDist < DDOF_MAXDIST) ? 1 : (targetDist / DDOF_MAXDIST);
			myMAXDIST = myMINDIST * DDOF_MAXDIST_FACTOR * maxFactor;
		}

	#endif

	if (targetDist <= myMAXNEAR)
	{
		myMAXNEAR = targetDist;
	}

	if (dep < myMAXNEAR && dep > myMINNEAR) // && targetDist > myMAXNEAR)
	{
		dep = ( 1 - ( dep - myMINNEAR ) / ( myMAXNEAR - myMINNEAR ) ) * myMAXDIST;
		mycof = MAXCOF_NEAR;
	}

	half 	blur		= saturate( ( dep - myMINDIST ) / ( myMAXDIST - myMINDIST ) );

	half2 	scale 	= half2	( .5f / 1024.h, .5f / 768.h ) * mycof * blur;

	// poisson
	static const half2 o [6] = 
	{
		half2( -0.326212f , -0.405810f ) * scale,
		half2( -0.695914f ,  0.457137f ) * scale,
		half2( 0.962340f , -0.194983f ) * scale,
		half2( 0.519456f ,  0.767022f ) * scale,
		half2( 0.507431f ,  0.064425f ) * scale,
		half2( -0.321940f , -0.932615f ) * scale,
	};

	// sample 
	for ( int i = 0; i < 6; i++ )
	{
		sum 		+= tex2D	( s_image, (float2) ( center + o[i] ) );
	}

	return 	half3	( sum / 6 );

}

#endif	//	USE_DOF

#endif	//	DOF_H_INCLUDED
