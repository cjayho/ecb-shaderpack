
     ECB-Shaderpack

     Improved shader pack for the game S.T.A.L.K.E.R.: Shadow of Chernobyl
_____________________________________________________________________________

     Revision 0014



     Features:
    _______________________

1) Opaque fog in R2, ability to swicth using configfile to opaque/transparent fog

2) Fixed "very blue color tone" on R2

3) Light trails on R2

4) Static and dynamic Depth of field on R2 (thanks meltac for permission to use 
   his code, see below for more details)
   Blurring screen edges while aiming (needs additional script)

5) Builds-like colorful bloom R2, ability to switch tonemapping in mode,
   which is used in build 2218

6) Screen space ambient occlusion on R2

7) Correct drawing lamp glow on R1

8) Correct drawing sun gradient on both renders

9) Improved drawing of occlusion lightmaps on R2

10) Microstructure (detail) bump.

11) Specular improvements

12) Autosaturation - per-pixel decreasing of saturation for less-lighed objects

13) Soft shadows on R2

14) Experimental feature - correct angle for drawing shadows of the trees on R2

15) Improved Motion blur, like in old builds

16) Fixed oversaturated sun lighting of objects on R2

17) Reflective water on R2

18) Experimental feature - sunshafts aka godRays on R2

Plus many subtle adjustments and improvements on both renders

     Terms of use
    _______________________

This product is distributed under the terms of Creative Commons CC-BY 3.0,
More details here: http://creativecommons.org/licenses/by/3.0/deed.ru
Maintainer of ECB-shaderpack is cjayho

New releases are available here http://code.google.com/p/ecb-shaderpack/downloads/list

     Installation
    ___________

This product was tested on game versions 1.0004 and 1.0006
Just copy mod's files to gamedata folder in the root directory of game
Initial version of shaderpack needs clean game. In case using third-party 
weater mods, you will need to merge config/weathers/flares.ltx

For advanced configuration of R2 you can use shaders/r2/config.h. 

For correct drawing of shadows you can set game console variables in values:

r2_sun_near_border 1
r2_sun_near 20

     Thanks to
    _______________

Sergy172 for ideas and testing/

-=Diablo=- for shaders of 2232 build, these shaders were used as basis

macron for reflective water and shaders from builds 2217 and 2588

Билдоман for shaders from build 2571

BAC9-FLCL, KamikaZZe for additional ideas and cryticism

Shadows for assistance in development and testing of experimental versions

Meltac <metzinger@gmx.net> (His mod "Dynamic shaders" is here: http://www.moddb.com/mods/dynamic-shaders) 
    for Depth of Field and Dynamic Depth of Field efect code. DoF and DDoF code is used under his permission. 

Sky4CE for the algorythm of SSAO effect


   
