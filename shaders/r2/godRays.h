float4 godrays( half2 TC )
{
	float4 P = mul( m_VP, float4( L_sun_dir_w + eye_position, 1 ) );
	half2 deltaTC = TC - ( float2( P.x + P.w, P.w - P.y ) / ( 2 * P.w ) );
	deltaTC = clamp( deltaTC, -.2f, .2f );
	deltaTC *= ECB_GR_DENSITY / ECB_GR_SAMPLES;
	half color = 0.f;
	half illum_decay = 1.0f;

	for ( int i = 0; i < ECB_GR_SAMPLES; i++ )
	{
		TC -= deltaTC;
		half sample = dot( tex2D( s_image, TC ), .33f );
		sample *= illum_decay;
		color += sample;
		illum_decay *= ECB_GR_DECAY;
	}

	return float4( L_sun_color.rgb * saturate( color - .5f ) * ECB_GR_EXPOSURE * saturate( saturate( -P.z ) - .3f ), 1 );
}
