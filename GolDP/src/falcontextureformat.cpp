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
	LegoU32 redMask = m_redBitMask;
	LegoU32 mask = redMask;
	LegoU32 redCount;
	if (mask == 0) {
		redCount = 0;
	}
	else {
		while (!(mask & 1)) {
			mask >>= 1;
		}
		redCount = 0;
		while (mask & 1) {
			mask >>= 1;
			redCount++;
		}
	}
	LegoU32 redRightShift = 8 - redCount;

	LegoU32 grnMask = m_grnBitMask;
	mask = grnMask;
	LegoU32 grnCount;
	if (mask == 0) {
		grnCount = 0;
	}
	else {
		while (!(mask & 1)) {
			mask >>= 1;
		}
		grnCount = 0;
		while (mask & 1) {
			mask >>= 1;
			grnCount++;
		}
	}
	LegoU32 grnRightShift = 8 - grnCount;

	LegoU32 bluMask = m_bluBitMask;
	mask = bluMask;
	if (mask != 0) {
		while (!(mask & 1)) {
			mask >>= 1;
		}
		LegoU32 bluCount = 0;
		while (mask & 1) {
			mask >>= 1;
			bluCount++;
		}
		mask = bluCount;
	}
	mask = 8 - mask;

	LegoU32 alpMask = m_alpBitMask;
	LegoU32 alpWork = alpMask;
	LegoU32 alpCount;
	if (alpWork == 0) {
		alpCount = 0;
	}
	else {
		while (!(alpWork & 1)) {
			alpWork >>= 1;
		}
		alpCount = 0;
		while (alpWork & 1) {
			alpWork >>= 1;
			alpCount++;
		}
	}

	LegoU32 blu;
	LegoU32 red;
	LegoU32 grn;

	red = p_rgba.peRed >> redRightShift;
	grn = p_rgba.peGreen >> grnRightShift;
	blu = p_rgba.peBlue >> mask;
	LegoU32 alp = p_rgba.peFlags >> (8 - alpCount);

	{
		LegoU32 shift = redMask;
		if (shift == 0) {
			shift = 32;
		}
		else {
			LegoU32 count = 0;
			while (!(shift & 1)) {
				shift >>= 1;
				count++;
			}
			shift = count;
		}
		red <<= shift;
	}

	{
		LegoU32 shift = grnMask;
		if (shift == 0) {
			shift = 32;
		}
		else {
			LegoU32 count = 0;
			while (!(shift & 1)) {
				shift >>= 1;
				count++;
			}
			shift = count;
		}
		grn <<= shift;
	}
	red |= grn;

	{
		LegoU32 shift = bluMask;
		if (shift == 0) {
			shift = 32;
		}
		else {
			LegoU32 count = 0;
			while (!(shift & 1)) {
				shift >>= 1;
				count++;
			}
			shift = count;
		}
		blu <<= shift;
	}
	red |= blu;

	{
		LegoU32 shift = alpMask;
		if (shift == 0) {
			shift = 32;
		}
		else {
			LegoU32 count = 0;
			while (!(shift & 1)) {
				shift >>= 1;
				count++;
			}
			shift = count;
		}
		alp <<= shift;
	}

	return red | alp;
}
