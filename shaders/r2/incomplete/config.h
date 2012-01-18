/*---------------------------------------#
|  Library of shader variables ECB Team  |
#---------------------------------------*/

#ifndef	CONFIG_H
#define CONFIG_H

// Motion Blur
//#define USE_MBLUR

// Bloom
#define ECB_BLOOM_DIV 0.69h          // на каком значении картинка становитс€ блумом
#define ECB_BLOOM_SKYDIV 0.95h       // на каком значении картинка становитс€ блумом (небо)
#define ECB_BLOOM_BRIGHTNESS 0.33f   // €ркость блума
#define ECB_SPECULAR 0.61f           // €ркость бликов
//#define USE_LCOMPRESS                   // bloom 2218

// Depth of Field
#define USE_DOF
#define NEAR 0.2h                    // 
#define MINDIST 0.4h                 // минимальное рассто€ние, минимальна€ размывка
#define MAXDIST 600.h                // максимальное рассто€ние, максимальна€ размывка
#define MAXCOF 5.h                   // сила максимальной размывки
#define MAXCOF_NEAR	100.h            // 
#define EPSDEPTH 0.0001h             // 

// Screen Space Ambient Occlusion
#define ECB_SSAO
#define SSAO_QUALITY 2               // 2 - low, 3 - high
#define FADE_DIST 4.f                // размер области затемнени€ у углов
#define FADE_COEF 0.2f               // сила затемнени€

// Condensation Light Trail
#define USE_ECB_LTRAILS
#define ECB_LTRAIL_VELOCITY 12.5f    // длина хвоста в зависимости от скорости
#define ECB_LTRAIL_FACTOR 1.75f      // €ркость хвоста
#define USE_TCLAMP                   // ограничивать длину хвоста
#define TRAIL_CLAMP	half(0.0175)     // значение ограничени€ длины
#define LTRAIL_THRESHOLD 100.f       // скорость движени€ дл€ по€влени€ хвоста
//#define USE_LTRAIL_THRESHOLD            // убирать хвосты при отсутствии движени€

// Fog
#define ECB_FOG_COLOR 0.25           // умножение €ркости тумана (fog_color)
#define ECB_FOG_DIST 0.9             // умножение рассто€ни€ тумана (fog_distance)

// Shader Sun
#define ECB_SUN_SAT 0.9h             // насыщенность солнца
#define USE_OGSM_RESTORESUN          // использовать шейдерное солнце (ѕќћ≈Ќя“№ —ћџ—Ћ ¬ Ћё„ј“≈Ћя)

// Shadow
#define	ECB_SHADOW_KERNEL 0.9f       // ширина одиночных полосок-переходов в тен€х
#define ECB_SHADOW_STEPS 2           // количество полосок перехода тени от светлой к темной (integer)
//#define ECB_SHADOW_LENGTH 3.0f          // длинные тени

// Lightmaps
#define ECB_H *lerp(0.5f, 1.f, h*2)  // это формула подгонки уровней €ркости лайтмапов
#define ECB_H3 *lerp(0.4f, 1.f, h*3) // это формула подгонки уровней €ркости лайтмапов (столбики и домики)
#define ECB_H2 *lerp(0.4f, 1.f, h)   // это формула подгонки уровней €ркости лайтмапов
#define ECB_R2A_LMAP_FACTOR .2f+.8f  // €ркость лайтмапов на R2a
#define ECB_S1 0.045                 // base_aref_bump, base_aref_flat, base_flat, impl_bump
#define ECB_S2 0.045                 // base_bump
#define ECB_S3 0.045                 // impl_flat

// Setting local light
#define ECB_LL_DIST 1.2f             // дальность освещени€ ламп и костров
#define ECB_LL_BRIGHTNESS 2.0f       // €ркость освещени€ ламп и костров

// Setting brightness and color
#define ECB_EMISSIVE_MUL 1.5f        // €ркость свет€щихс€ поверхностей
#define ECB_DIFFUSE_AMBIENT_SAT 1.0f // цветность диффузного амбиента
#define ECB_ANTI_OVERBRIGHT 0.85h    // максимальный цвет текстуры
#define ECB_BRIGHTNESS 2.5f          // €ркость картинки в целом
#define ECB_SUN_FAR 1.0f             // €ркость дальнего кольца солнечного освещени€
#define ECB_TERRAIN_SAT 0.8f         // цветность терейна
#define ECB_AUTOSAT_FACTOR 21.25f    // уменьшение цветности картинки при снижении освещенности

uniform sampler 	s_smap;		  // 2D/cube shadowmap (”Ѕ–ј“№ в COMMON и удалить отсюда!)

#endif
