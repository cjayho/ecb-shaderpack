function normal		(shader, t_base, t_second, t_detail)
	shader:begin	("lod","lod")
			: blend	(true,blend.srcalpha,blend.invsrcalpha)
			: aref	(true,16)
			: zb	(true,false)
			: fog	(true)
	shader:sampler	("s_base")      :texture	(t_base)
end
