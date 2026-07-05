#include "golsurfaceformat.h"

#include "decomp.h"
#include "surface/color.h"

DECOMP_SIZE_ASSERT(GolSurfaceFormat, 0x18)

// FUNCTION: GOLDP 0x1001cb50
// FUNCTION: LEGORACERS 0x00407210
LegoU32 GolSurfaceFormat::GetRedBitCount() const
{
	LegoU32 mask = m_redBitMask;
	if (mask == 0) {
		return 0;
	}

	while (!(mask & 0x1)) {
		mask >>= 1;
	}

	LegoU32 count = 0;
	while (mask & 0x1) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001cb80
// FUNCTION: LEGORACERS 0x00407240
LegoU32 GolSurfaceFormat::GetGreenBitCount() const
{
	LegoU32 mask = m_grnBitMask;
	if (mask == 0) {
		return 0;
	}

	while (!(mask & 0x1)) {
		mask >>= 1;
	}

	LegoU32 count = 0;
	while (mask & 0x1) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001cbb0
// FUNCTION: LEGORACERS 0x00407270
LegoU32 GolSurfaceFormat::GetBlueBitCount() const
{
	LegoU32 mask = m_bluBitMask;
	if (mask == 0) {
		return 0;
	}

	while (!(mask & 0x1)) {
		mask >>= 1;
	}

	LegoU32 count = 0;
	while (mask & 0x1) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001cbe0
// FUNCTION: LEGORACERS 0x004072a0
LegoU32 GolSurfaceFormat::GetAlphaBitCount() const
{
	LegoU32 mask = m_alpBitMask;
	if (mask == 0) {
		return 0;
	}

	while (!(mask & 0x1)) {
		mask >>= 1;
	}

	LegoU32 count = 0;
	while (mask & 0x1) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001cc10
LegoU32 GolSurfaceFormat::GetIntensityBitCount() const
{
	LegoU32 mask = m_intensityMask;
	if (mask == 0) {
		return 0;
	}

	while (!(mask & 0x1)) {
		mask >>= 1;
	}

	LegoU32 count = 0;
	while (mask & 0x1) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001cc40
// FUNCTION: LEGORACERS 0x004072d0
LegoU32 GolSurfaceFormat::GetPaletteBitCount() const
{
	LegoU16 mask = m_paletteMask;
	if (mask == 0) {
		return 0;
	}

	LegoU32 work = mask;
	while (!(work & 0x1)) {
		work >>= 1;
	}

	LegoU32 count = 0;
	while (work & 0x1) {
		work >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001cc70
// FUNCTION: LEGORACERS 0x00407300
LegoU32 GolSurfaceFormat::GetRedBitShift() const
{
	LegoU32 mask = m_redBitMask;
	if (mask == 0) {
		return 32;
	}

	LegoU32 count = 0;
	while (!(mask & 0x1)) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001cc90
// FUNCTION: LEGORACERS 0x00407320
LegoU32 GolSurfaceFormat::GetGreenBitShift() const
{
	LegoU32 mask = m_grnBitMask;
	if (mask == 0) {
		return 32;
	}

	LegoU32 count = 0;
	while (!(mask & 0x1)) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001ccb0
// FUNCTION: LEGORACERS 0x00407340
LegoU32 GolSurfaceFormat::GetBlueBitShift() const
{
	LegoU32 mask = m_bluBitMask;
	if (mask == 0) {
		return 32;
	}

	LegoU32 count = 0;
	while (!(mask & 0x1)) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001ccd0
// FUNCTION: LEGORACERS 0x00407360
LegoU32 GolSurfaceFormat::GetAlphaBitShift() const
{
	LegoU32 mask = m_alpBitMask;
	if (mask == 0) {
		return 32;
	}

	LegoU32 count = 0;
	while (!(mask & 0x1)) {
		mask >>= 1;
		count += 1;
	}

	return count;
}

// FUNCTION: GOLDP 0x1001ccf0
// FUNCTION: LEGORACERS 0x00407380
LegoU32 GolSurfaceFormat::MapRGBA(const ColorRGBA& p_rgba) const
{
	LegoU32 redShift = 8 - GetRedBitCount();
	LegoU32 grnShift = 8 - GetGreenBitCount();
	LegoU32 bluShift = 8 - GetBlueBitCount();
	LegoU32 alpShift = 8 - GetAlphaBitCount();

	LegoU32 red = p_rgba.m_red >> redShift;
	LegoU32 grn = p_rgba.m_grn >> grnShift;
	LegoU32 blu = p_rgba.m_blu >> bluShift;
	LegoU32 alp = p_rgba.m_alp >> alpShift;

	red <<= GetRedBitShift();
	grn <<= GetGreenBitShift();
	red |= grn;
	blu <<= GetBlueBitShift();
	red |= blu;
	alp <<= GetAlphaBitShift();

	return red | alp;
}
