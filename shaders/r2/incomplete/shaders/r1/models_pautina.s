function normal    (shader, t_base, t_second, t_detail)
  shader:begin  ("model_distort4ghost","particle")
      : sorting  (2, true)
      : fog    (false)
      : zb     (true,true)
      : blend    (true,blend.srccolor,blend.invsrcalpha)
      : aref     (true,0)
  shader:sampler  ("s_base")      :texture  (t_base)
end


function l_special  (shader, t_base, t_second, t_detail)
  shader:begin  ("model_distort4ghost","particle")
      : sorting  (3, false)
      : blend    (true,blend.srcalpha,blend.invsrcalpha)
      : zb     (true,true)
      : fog    (false)
      : distort   (true)
  shader:sampler  ("s_base")      :texture  (t_base)
  shader:sampler  ("s_distort")   :texture  (t_base)  -- "pfx\\pfx_distortion"
end
