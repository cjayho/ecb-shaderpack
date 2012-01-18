#ifndef	CONFIG_H
#define CONFIG_H

// Не думайте что названия переменных включают "ECB" для самопиара. 
// Просто это наиболее простой и верный способ обезопасить себя от возможности 
// того, что мои переменные и переменные оригинальных шейдеров пересекутся на одном имени.

// бОльшие значения дают бОльшие значения соответствующего параметра конфига погоды в скобках
#define ECB_FOG_COLOR 0.25 // Умножение яркости тумана (fog_color)
#define ECB_FOG_DIST 0.9 // Умножение расстояния тумана (fog_distance)

// shadows
#define	ECB_SHADOW_KERNEL	.9f // Ширина одиночных полосок-переходов в тенях
#define ECB_SHADOW_STEPS 2 // integer; количество полосок перехода тени от светлой к темной. 

#define ECB_H *lerp( 0.5f, 1.f, h * 2 ) //  это формула подгонки уровней яркости лайтмапов.
#define ECB_H3 *lerp( 0.4f, 1.f, h * 3 ) //  это формула подгонки уровней яркости лайтмапов. (столбики и домики)
#define ECB_H2 *lerp( 0.4f, 1.f, h ) //  это формула подгонки уровней яркости лайтмапов.

#define ECB_S1 0.045 // base_aref_bump, base_aref_flat, base_flat, impl_bump // 0.05
#define ECB_S2 0.045 // base_bump // 0.02
#define ECB_S3 0.045 // impl_flat // 0.04

#define ECB_SUN_SAT 0.9h // насыщенность солнца

#define ECB_EMISSIVE_MUL 1.5f // яркость светящихся поверхностей: чем больше тем блум желтее а потом зеленее и тд.

#define ECB_BLOOM_DIV 0.69h // на каком значении картинка становится блумом.
#define ECB_BLOOM_SKYDIV 0.95h // на каком значении картинка становится блумом (небо)
#define ECB_BLOOM_BRIGHTNESS 0.5f // яркость блума
#define ECB_SPECULAR 0.61f // яркость бликов
#define ECB_DIFFUSE_AMBIENT_SAT 1.0f // цветность диффузного амбиента
//#define ECB_SHADOW_LENGTH 3.0f // удлинение теней в n раз (экспериментальная фича)
#define ECB_ANTI_OVERBRIGHT 0.85h // Переменная, до которой максимум возрастает цвет текстуры. Для того чтобы текстура не отсекалась сверху при наложении освещения.
#define ECB_BRIGHTNESS 2.5f // яркость картинки в целом 1.6
#define ECB_SUN_FAR 1.0f // для компенсации разницы между внешним кольцом солнечного света и внутренним. Умножается яркость внешнего кольца
#define ECB_R2A_LMAP_FACTOR .2f+.8f

//#define USE_MBLUR

// DoF
#define USE_DOF

#define MINDIST 	0.5f
#define MAXDIST 	600.f
#define MAXCOF		1.f
#define MAXCOF_NEAR	15.f
#define MAXNEAR float(0.5)					// Distance at which Near Field DOF starts. Default is 0.7. Larger values will blur your weapon more, and not only its near part.
#define MINNEAR float(0.0)					// Distance at which Near Field DOF stops. Default is 0.0

// DDoF
#define ECB_USE_DDOF

#define DDOF_MINDIST_ADD float(0.5)			// Added to view distance, at this distance begins blurring
#define DDOF_MAXDIST_FACTOR float(1.0)		// Mindist times factor = maxdist
#define DDOF_MINDIST float(0.0)				// Minimum distance DDOF starts.
#define DDOF_MAXDIST float(10.0)			// Distance at which DOF stops rendering. Beyond this view distance, only minor DDOF

//#define ECB_SSAO
#define SSAO_QUALITY 2 	//2 - low quality; 3 - high quality
#define FADE_DIST 4.f
#define FADE_COEF .2f

#define USE_ECB_LTRAILS // Компенсационный световой след
#define ECB_LTRAIL_VELOCITY 12.5f // Длина хвоста в зависимости от скорости
#define ECB_LTRAIL_FACTOR 1.5f // яркость хвоста
#define USE_TCLAMP // ограничивать длину хвоста
#define TRAIL_CLAMP	half(0.0175) // значение ограничения длины
#define USE_LTRAIL_THRESHOLD // убирать хвосты при отсутствии движения
#define LTRAIL_THRESHOLD 100.f // чем бОльшее значение, тем меньшую скорость движения нужно делать для появления хвоста

//#define USE_SHADER_RESTORESUN

#define ECB_TERRAIN_SAT 0.8f

//#define USE_LCOMPRESS # блум аля 2218

#define ECB_LL_DIST 1.2f
#define ECB_LL_BRIGHTNESS 1.0f

#define ECB_AUTOSAT_FACTOR 21.25f

#define ECB_PARTICLE_FACTOR *.75f

#define ECB_MBUMP

#endif
