function normal		(shader, t_base, t_second, t_detail)
	shader:begin	("lod","lod")
			: zb	(true,false)
	shader:sampler	("s_base")      :texture	(t_base)
end
