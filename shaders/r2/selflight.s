function normal		(shader, t_base, t_second, t_detail)
	shader:begin	("ecb_fx_generic","effects_glow_p")
			: fog		(false)
			: zb 		(false,false)
--			: blend		(true,blend.zero,blend.one)
--			: aref 		(false,0)
			: sorting	(1, false)
	shader:sampler	("s_base")      :texture	(t_base)
end

function l_special		(shader, t_base, t_second, t_detail)
	shader:begin	("ecb_fx_generic","effects_glow_p")
			: fog		(false)
			: zb 		(false,false)
--			: blend		(true,blend.zero,blend.one)
--			: aref 		(false,0)
			: sorting	(1, false)
	shader:sampler	("s_base")      :texture	(t_base)
end
