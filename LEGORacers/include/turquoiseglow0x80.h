#ifndef TURQUOISEGLOW0X80_H
#define TURQUOISEGLOW0X80_H

#include "compat.h"
#include "decomp.h"
#include "golname.h"
#include "golnametable.h"
#include "turquoiseglowcolor.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b00a4
// SIZE 0x80
class TurquoiseGlow0x80 : public GolNameTable {
public:
	// SIZE 0x30
	struct Entry0x30 {
		LegoU16 m_unk0x00;          // 0x00
		GolName m_unk0x02;          // 0x02
		GolName m_unk0x0a;          // 0x0a
		GolName m_unk0x12;          // 0x12
		GolName m_unk0x1a;          // 0x1a
		LegoU8 m_unk0x22;           // 0x22
		LegoU8 m_unk0x23;           // 0x23
		LegoU8 m_unk0x24;           // 0x24
		LegoU8 m_unk0x25;           // 0x25
		LegoU8 m_unk0x26;           // 0x26
		LegoU8 m_unk0x27;           // 0x27
		LegoU8 m_unk0x28;           // 0x28
		LegoU8 m_unk0x29;           // 0x29
		LegoU8 m_unk0x2a;           // 0x2a
		TurquoiseGlowColor m_color; // 0x2b
	};

	TurquoiseGlow0x80();
	~TurquoiseGlow0x80() override; // vtable+0x00

	void Clear() override; // vtable+0x08
	void FUN_00421050(LegoU32 p_index, TurquoiseGlowColor* p_color);

	// SYNTHETIC: LEGORACERS 0x004206f0
	// TurquoiseGlow0x80::`scalar deleting destructor'

private:
	undefined m_unk0x0c[0x28 - 0x0c]; // 0x0c
	Entry0x30* m_entries;             // 0x28
	undefined m_unk0x2c[0x80 - 0x2c]; // 0x2c
};

#endif // TURQUOISEGLOW0X80_H
