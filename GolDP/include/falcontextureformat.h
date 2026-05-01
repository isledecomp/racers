#ifndef FALCONTEXTUREFORMAT_H
#define FALCONTEXTUREFORMAT_H

#include "decomp.h"
#include "types.h"

#include <windows.h>

// SIZE 0x18
class FalconTextureFormat {
public:
	FalconTextureFormat()
	{
		m_redBitMask = 0;
		m_grnBitMask = 0;
		m_bluBitMask = 0;
		m_alpBitMask = 0;
		m_unk0x10 = 0;
		m_unk0x14 = 0;
		m_rgbBitCount = 0;
	}

	LegoU32 GetRedBitCount() const;
	LegoU32 GetBlueBitCount() const;
	LegoU32 GetGreenBitCount() const;
	LegoU32 GetAlphaBitCount() const;
	LegoU32 FUN_1001cc10() const;
	LegoU32 FUN_1001cc40() const;
	LegoU32 GetRedBitShift() const;
	LegoU32 GetBlueBitShift() const;
	LegoU32 GetGreenBitShift() const;
	LegoU32 GetAlphaBitShift() const;
	LegoU32 MapRGBA(const PALETTEENTRY& p_rgba) const;

	LegoU32 m_redBitMask;
	LegoU32 m_grnBitMask;
	LegoU32 m_bluBitMask;
	LegoU32 m_alpBitMask;
	undefined4 m_unk0x10;
	undefined2 m_unk0x14;
	LegoU16 m_rgbBitCount;
};

#endif // FALCONTEXTUREFORMAT_H
