function normal    (shader, t_base, t_second, t_detail)
  shader:begin  ("model_distort","particle")    -- particle_alphaonly
      : sorting  (1, true)
      : blend    (true,blend.srcalpha,blend.zero)
      : aref     (true,0)
      : zb     (true,true)
      : fog    (false)
      : distort   (false)
  shader:sampler  ("s_base")      :texture  (t_base)
end