#ifndef FALCONTEXTUREFORMAT_H
#define FALCONTEXTUREFORMAT_H

#include "color.h"
#include "decomp.h"
#include "types.h"

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
		m_paletteMask = 0;
		m_bitsPerPixel = 0;
	}

	LegoU32 GetRedBitCount() const;
	LegoU32 GetBlueBitCount() const;
	LegoU32 GetGreenBitCount() const;
	LegoU32 GetAlphaBitCount() const;
	LegoU32 FUN_1001cc10() const;
	LegoU32 GetPaletteBitCount() const;
	LegoU32 GetRedBitShift() const;
	LegoU32 GetBlueBitShift() const;
	LegoU32 GetGreenBitShift() const;
	LegoU32 GetAlphaBitShift() const;
	LegoU32 MapRGBA(const ColorRGBA& p_rgba) const;

	LegoU32 m_redBitMask;   // 0x00
	LegoU32 m_grnBitMask;   // 0x04
	LegoU32 m_bluBitMask;   // 0x08
	LegoU32 m_alpBitMask;   // 0x0c
	undefined4 m_unk0x10;   // 0x10
	LegoU16 m_paletteMask;  // 0x14
	LegoU16 m_bitsPerPixel; // 0x16
};

#endif // FALCONTEXTUREFORMAT_H
