#include "decomp.h"
#include "types.h"

#include <float.h>

// GLOBAL: LEGORACERS 0x004b03f4
extern const LegoFloat g_warpPortalHeightOffset = 6.0f;

// GLOBAL: LEGORACERS 0x004b1378
extern const LegoFloat g_unlimitedDrawDistance = FLT_MAX;

// GLOBAL: LEGORACERS 0x004b1840
extern const LegoFloat g_aimMinDistanceSquared = 100.0f;

// GLOBAL: LEGORACERS 0x004b1844
extern const LegoFloat g_aimMaxDistanceSquared = 160000.0f;

// GLOBAL: LEGORACERS 0x004b1848
extern const LegoFloat g_aimRacerConeCosine = 0.89999998f;

// GLOBAL: LEGORACERS 0x004b184c
extern const LegoFloat g_aimPointConeCosine = 0.94999999f;

// GLOBAL: LEGORACERS 0x004b1850
extern const LegoFloat g_dynamiteAimMinDistanceSquared = 100.0f;

// GLOBAL: LEGORACERS 0x004b1854
extern const LegoFloat g_dynamiteAimMaxDistanceSquared = 160000.0f;

// GLOBAL: LEGORACERS 0x004b1858
extern const LegoFloat g_dynamiteAimConeCosine = 0.89999998f;

// GLOBAL: LEGORACERS 0x004b185c
extern const LegoFloat g_hookAimMinDistanceSquared = 100.0f;

// GLOBAL: LEGORACERS 0x004b1860
extern const LegoFloat g_hookAimFarMaxDistanceSquared = 62500.0f;

// GLOBAL: LEGORACERS 0x004b1864
extern const LegoFloat g_hookAimMaxDistanceSquared = 160000.0f;

// GLOBAL: LEGORACERS 0x004b1868
extern const LegoFloat g_hookAimFarConeCosine = 0.93000001f;

// GLOBAL: LEGORACERS 0x004b186c
extern const LegoFloat g_hookAimWideConeCosine = 0.60000002f;

// GLOBAL: LEGORACERS 0x004b1930
extern const LegoFloat g_shieldExpireSoundMinDistance = 30.0f;

// GLOBAL: LEGORACERS 0x004b1934
extern const LegoFloat g_shieldExpireSoundMaxDistance = 300.0f;

// GLOBAL: LEGORACERS 0x004b1a6c
extern const LegoFloat g_warpFovBoost = 30.0f;
