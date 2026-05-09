#include "golmath.h"

#include <math.h>

DECOMP_SIZE_ASSERT(GolVec2, 0x8)
DECOMP_SIZE_ASSERT(GolVec3, 0xc)
DECOMP_SIZE_ASSERT(GolQuat, 0x10)

// STUB: GOLDP 0x1002f3a0
void GolMath::FUN_1002f3a0(const D3DMATRIX*, const LegoFloat*, LegoFloat*)
{
	STUB(0x1002f3a0);
}

// STUB: GOLDP 0x1002f450
void GolMath::FUN_1002f450(const LegoFloat*, const LegoFloat*, LegoFloat*)
{
	STUB(0x1002f450);
}

// STUB: LEGORACERS 0x00449170
void GolMath::FUN_00449170(LegoFloat, LegoFloat*, LegoFloat*)
{
	STUB(0x00449170);
}

// STUB: LEGORACERS 0x00449190
void GolMath::FUN_00449190(const LegoFloat*, const LegoFloat*, LegoFloat*)
{
	STUB(0x00449190);
}

// STUB: GOLDP 0x1002f4e0
// STUB: LEGORACERS 0x00449280
void __fastcall GolMath::FUN_1002f4e0(const GolVec2*, GolVec2*)
{
	STUB(0x1002f4e0);
}

// FUNCTION: GOLDP 0x1002f530
// FUNCTION: LEGORACERS 0x004492d0
void __fastcall GolMath::NormalizeVector3(const GolVec3& p_src, GolVec3& p_dest)
{
	LegoFloat x = p_src.m_x;
	// TODO: Find the original clean source form. The double cast is only here
	// to make VC6 spill y through the FPU instead of using an integer move.
	LegoFloat y = (LegoFloat) ((double) p_src.m_y);
	LegoFloat z = p_src.m_z;
	LegoFloat lengthSquared = x * x;
	lengthSquared += y * y;
	LegoFloat length = (LegoFloat) sqrt(lengthSquared + (z * z));

	if (length == 0.0) {
		p_dest.m_x = 0.0f;
		p_dest.m_y = 0.0f;
		p_dest.m_z = 0.0f;
	}
	else {
		LegoFloat scale = 1.0f / length;
		p_dest.m_x = x * scale;
		p_dest.m_y = y * scale;
		p_dest.m_z = z * scale;
	}
}

// STUB: LEGORACERS 0x00449340
void GolMath::FUN_00449340(const GolQuat*, LegoFloat*)
{
	STUB(0x00449340);
}

// STUB: GOLDP 0x1002f5a0
// STUB: LEGORACERS 0x00449460
void GolMath::FUN_1002f5a0(const LegoFloat*, GolQuat*)
{
	STUB(0x1002f5a0);
}

// STUB: GOLDP 0x1002f720
void GolMath::FUN_1002f720(const LegoFloat*, GolQuat*)
{
	STUB(0x1002f720);
}

// STUB: GOLDP 0x1002f890
// STUB: LEGORACERS 0x004495e0
void GolMath::FUN_1002f890(const GolQuat*, const GolQuat*, LegoFloat, GolQuat*)
{
	STUB(0x1002f890);
}

// STUB: LEGORACERS 0x004496a0
void GolMath::FUN_004496a0(const GolVec3*, GolVec3*, const GolVec3*, LegoFloat)
{
	STUB(0x004496a0);
}

// STUB: LEGORACERS 0x004497f0
LegoBool32 GolMath::FUN_004497f0(const GolVec3*, const LegoFloat*)
{
	STUB(0x004497f0);
	return FALSE;
}

// STUB: LEGORACERS 0x00449a90
LegoBool32 GolMath::FUN_00449a90(GolVec3*, GolVec3*, LegoFloat, LegoFloat, LegoFloat)
{
	STUB(0x00449a90);
	return FALSE;
}

// STUB: LEGORACERS 0x00449b90
void GolMath::FUN_00449b90(LegoFloat, LegoFloat, LegoFloat, const LegoFloat*, GolVec3*)
{
	STUB(0x00449b90);
}

// STUB: LEGORACERS 0x00449bf0
void GolMath::FUN_00449bf0(const LegoFloat*, const LegoFloat*, LegoFloat*)
{
	STUB(0x00449bf0);
}
