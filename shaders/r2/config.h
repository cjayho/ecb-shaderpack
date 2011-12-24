#ifndef	CONFIG_H
#define CONFIG_H

// Ќе думайте что названи€ переменных включают "ECB" дл€ самопиара. 
// ѕросто это наиболее простой и верный способ обезопасить себ€ от возможности 
// того, что мои переменные и переменные оригинальных шейдеров пересекутс€ на одном имени.

// бќльшие значени€ дают бќльшие значени€ соответствующего параметра конфига погоды в скобках
#define ECB_FOG_COLOR 0.35 // ”множение €ркости тумана (fog_color)
#define ECB_FOG_DIST 0.9 // ”множение рассто€ни€ тумана (fog_distance)

// shadows
#define	ECB_SHADOW_KERNEL	.9f // Ўирина одиночных полосок-переходов в тен€х
#define ECB_SHADOW_STEPS 2 // integer; количество полосок перехода тени от светлой к темной. 

#define ECB_H *lerp( 0.5f, 1.f, h * 2 ) //  это формула подгонки уровней €ркости лайтмапов.
#define ECB_H3 *lerp( 0.4f, 1.f, h * 3 ) //  это формула подгонки уровней €ркости лайтмапов. (столбики и домики)
#define ECB_H2 *lerp( 0.4f, 1.f, h ) //  это формула подгонки уровней €ркости лайтмапов.

#define ECB_S1 0.045 // base_aref_bump, base_aref_flat, base_flat, impl_bump // 0.05
#define ECB_S2 0.045 // base_bump // 0.02
#define ECB_S3 0.045 // impl_flat // 0.04

#define ECB_SUN_SAT 0.9h // насыщенность солнца

#define ECB_EMISSIVE_MUL 1.5f // €ркость свет€щихс€ поверхностей: чем больше тем блум желтее а потом зеленее и тд.

#define ECB_BLOOM_DIV 0.69h // на каком значении картинка становитс€ блумом.
#define ECB_BLOOM_SKYDIV 0.92h // на каком значении картинка становитс€ блумом (небо)
#define ECB_BLOOM_BRIGHTNESS 0.5f // €ркость блума
#define ECB_SPECULAR 0.61f // €ркость бликов
#define ECB_DIFFUSE_AMBIENT_SAT 1.0f // цветность диффузного амбиента
//#define ECB_SHADOW_LENGTH 3.0f // удлинение теней в n раз (экспериментальна€ фича)
#define ECB_USE_ECB_BLOOM // »спользовать "тот самый" блум
#define ECB_ANTI_OVERBRIGHT 0.85h // ѕеременна€, до которой максимум возрастает цвет текстуры. ƒл€ того чтобы текстура не отсекалась сверху при наложении освещени€.
#define ECB_BRIGHTNESS 2.5f // €ркость картинки в целом 1.6
#define ECB_SUN_FAR 1.0f // дл€ компенсации разницы между внешним кольцом солнечного света и внутренним. ”множаетс€ €ркость внешнего кольца
#define ECB_R2A_LMAP_FACTOR .2f+.8f

//#define USE_MBLUR

// DoF
//#define USE_DOF
#define NEAR 		0.2h
#define MINDIST 	0.4h
#define MAXDIST 	600.h
#define MAXCOF		5.h
#define MAXCOF_NEAR	100.h
#define EPSDEPTH	0.0001h

//#define ECB_SSAO
#define SSAO_QUALITY 2 	//2 - low quality; 3 - high quality
#define FADE_DIST 4.f
#define FADE_COEF .2f

#define USE_ECB_LTRAILS //  омпенсационный световой след
#define ECB_LTRAIL_VELOCITY 20.f
#define ECB_LTRAIL_FACTOR 1.0f

//#define USE_ECBOPTS // задействовать оптимизации
uniform sampler 	s_smap;		// 2D/cube shadowmap

#define USE_OGSM_RESTORESUN

#define ECB_TERRAIN_SAT 0.8f

//#define USE_LCOMPRESS # блум ал€ 2218

#define ECB_LL_DIST 1.4f
#define ECB_LL_BRIGHTNESS 2.0f

#define ECB_AUTOSAT_FACTOR 18.75f

#endif
