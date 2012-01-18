function normal		(shader, t_base, t_second, t_detail)
	shader:begin	("null","add_ppa")
			: fog		(false)
			: zb 		(true,false)
			: blend		(true,blend.one,blend.one)
			: aref 		(true,0)
	shader:sampler	("s_base0")	:texture(t_base): clamp() : f_linear ()
	shader:sampler	("s_base1")    	:texture(t_base): clamp() : f_linear ()
end
