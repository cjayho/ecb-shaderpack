/*
    ECB-shaderpack configuration file
    ______________________________________
*/

#ifndef CONFIG_H
#define CONFIG_H

// Motion Blur and Bump
#define USE_MBLUR                                   // размытие картинки при движении
#define ECB_MBUMP                                   // микроструктурный бамп

// Bloom
#define ECB_BLOOM_DIV 0.69h                         // на каком значении картинка становится блумом
#define ECB_BLOOM_SKYDIV 0.95h                      // на каком значении картинка становится блумом (небо)
#define ECB_BLOOM_BRIGHTNESS 0.5f                   // яркость блума
#define ECB_SPECULAR 0.61f                          // яркость бликов
//#define ECB_LCOMPRESS                             // bloom 2218

#define ECB_DOF                                     // Depth of Field
    #define ECB_DOF_MINDIST 0.5f                    // минимальное расстояние для эффекта
    #define ECB_DOF_MAXDIST 600.f                   // максимальное расстояние для эффекта
    #define ECB_DOF_MAXCOF 4.f                      // максимальный фактор размытия удаленных объектов
    #define ECB_DOF_MAXCOF_NEAR 4.f                 // максимальный фактор размытия близких объектов
    #define ECB_DOF_MAXNEAR float(0.7)              // расстояние до близкого кольца DoF с минимальным размытием
    #define ECB_DOF_MINNEAR float(0.0)              // расстояние до окончания близкого кольца DoF с максимальным размытием

#define ECB_DDOF                                    // Dynamic Depth of Field
    #define ECB_DDOF_MINDIST_ADD float(0.7)         // расстояние старта размытия
    #define ECB_DDOF_MAXDIST_FACTOR float(4.0)      // домножение величины размытия удаленных объектов при взгляде на близкий
    #define ECB_DDOF_MINDIST float(0.0)             // минимальное расстояние применения эффекта
    #define ECB_DDOF_MAXDIST float(10.0)            // максимальное расстояние применения эффекта

#define ECB_SSAO                                  // Screen Space Ambient Occlusion
    #define ECB_SSAO_QUALITY 2                      // 2 - low, 3 - high, 4 - slow as hell
    #define ECB_SSAO_FADE_DIST 12.f                 // размер области затемнения у углов
    #define ECB_SSAO_FADE_COEF .15f                 // сила затемнения

#define ECB_LTRAILS                                 // Condensation Light Trail
    #define ECB_LTRAIL_VELOCITY 12.5f               // длина хвоста в зависимости от скорости
    #define ECB_LTRAIL_FACTOR 1.5f                  // яркость хвоста
    #define ECB_LTRAIL_CLAMP                        // ограничивать длину хвоста
    #define ECB_LTRAIL_CLAMP_VALUE half(0.0175)     // значение ограничения длины
    #define ECB_LTRAIL_USE_THRESHOLD                // убирать хвосты при отсутствии движения
    #define ECB_LTRAIL_THRESHOLD 100.f              // скорость движения для появления хвоста

// Fog
#define ECB_FOG_COLOR 0.25                          // умножение яркости тумана (fog_color)
#define ECB_FOG_DIST 0.9                            // умножение расстояния тумана (fog_distance)

// Sun
//#define ECB_SHADER_RESTORE_SUN                    // использовать шейдерное солнце
#define ECB_SUN_SAT 0.9h                            // насыщенность солнца

// Shadow
#define ECB_SHADOW_KERNEL .9f                       // ширина одиночных полосок-переходов в тенях
#define ECB_SHADOW_STEPS 2                          // количество полосок перехода тени от светлой к темной (integer)
//#define ECB_SHADOW_LENGTH 3.0f                    // длина теней

// Lightmaps
#define ECB_R2A_LMAP_FACTOR .2f + .8f               // яркость лайтмапов на R2a
#define ECB_SB 0.66f                                // яркость теней
#define ECB_H*lerp(ECB_SB, 1.f, h*2)                // формула подгонки уровней яркости лайтмапов
#define ECB_H2*lerp(ECB_SB, 1.f, h)                 // формула подгонки уровней яркости лайтмапов
#define ECB_H3*lerp(ECB_SB, 1.f, h*3)               // формула подгонки уровней яркости лайтмапов (столбики и домики)
#define ECB_S1 0.045                                // base_aref_bump, base_aref_flat, base_flat, impl_bump
#define ECB_S2 0.045                                // base_bump
#define ECB_S3 0.045                                // impl_flat

// Setting local light
#define ECB_LL_DIST 1.2f                            // дальность освещения ламп и костров
#define ECB_LL_BRIGHTNESS 0.7f                      // яркость освещения ламп и костров

// Setting brightness and color
#define ECB_EMISSIVE_MUL 1.1f                       // яркость светящихся поверхностей
#define ECB_DIFFUSE_AMBIENT_SAT 1.0f                // цветность диффузного амбиента
#define ECB_ANTI_OVERBRIGHT 0.85h                   // максимальная цветность текстуры
#define ECB_BRIGHTNESS 2.5f                         // яркость картинки в целом
#define ECB_SUN_FAR 1.0f                            // яркость дальнего кольца солнечного освещения
#define ECB_TERRAIN_SAT 1.0f                        // цветность терейна
#define ECB_AUTOSAT_FACTOR 21.25f                   // уменьшение цветности картинки при снижении освещенности
#define ECB_PARTICLE_FACTOR *.75f                   // яркость партиклов

#endif
