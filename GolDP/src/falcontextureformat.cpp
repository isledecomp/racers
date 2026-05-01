#include "falcontextureformat.h"

// FUNCTION: GOLDP 0x1001cb50
LegoU32 FalconTextureFormat::GetRedBitCount() const
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
LegoU32 FalconTextureFormat::GetGreenBitCount() const
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
LegoU32 FalconTextureFormat::GetBlueBitCount() const
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
LegoU32 FalconTextureFormat::GetAlphaBitCount() const
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
LegoU32 FalconTextureFormat::FUN_1001cc10() const
{

	LegoU32 mask = m_unk0x10;
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
LegoU32 FalconTextureFormat::FUN_1001cc40() const
{

	LegoU16 mask = m_unk0x14;
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

// FUNCTION: GOLDP 0x1001cc70
LegoU32 FalconTextureFormat::GetRedBitShift() const
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
LegoU32 FalconTextureFormat::GetGreenBitShift() const
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
LegoU32 FalconTextureFormat::GetBlueBitShift() const
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
LegoU32 FalconTextureFormat::GetAlphaBitShift() const
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
LegoU32 FalconTextureFormat::MapRGBA(const PALETTEENTRY& p_rgba) const
{
#if 0
	LegoU32 redCount = GetRedBitCount();
	LegoU32 grnCount = GetGreenBitCount();
	LegoU32 bluCount = GetBlueBitCount();
	LegoU32 alpCount = GetAlphaBitCount();
	LegoU32 redShift = GetRedBitShift();
	LegoU32 grnShift = GetGreenBitShift();
	LegoU32 bluShift = GetBlueBitShift();
	LegoU32 alpShift = GetAlphaBitShift();
	return ((p_rgba.peRed >> (8 - redCount)) << redShift) |
		   ((p_rgba.peGreen >> (8 - grnCount)) << grnShift) |
		   ((p_rgba.peBlue >> (8 - bluCount)) << bluShift) |
		   ((p_rgba.peFlags >> (8 - alpCount)) << alpShift);
#else
	return ((p_rgba.peRed >> (8 - GetRedBitCount())) << GetRedBitShift()) |
		   ((p_rgba.peGreen >> (8 - GetGreenBitCount())) << GetGreenBitShift()) |
		   ((p_rgba.peBlue >> (8 - GetBlueBitCount())) << GetBlueBitShift()) |
		   ((p_rgba.peFlags >> (8 - GetAlphaBitCount())) << GetAlphaBitShift());
#endif
}
