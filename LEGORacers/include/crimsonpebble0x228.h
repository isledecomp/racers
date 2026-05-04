#ifndef CRIMSONPEBBLE0X228_H
#define CRIMSONPEBBLE0X228_H

#include "audio/soundnode.h"
#include "bluebellfog0x4.h"
#include "decomp.h"
#include "golnametable.h"
#include "golstringtable.h"
#include "types.h"

class GolFileParser;

// VTABLE: LEGORACERS 0x004b4970
// SIZE 0x228
class CrimsonPebble0x228 : public BluebellFog0x4 {
public:
	CrimsonPebble0x228();

	void VTable0x00(undefined4, undefined4, undefined4) override; // vtable+0x00
	void VTable0x04(undefined4, undefined4, undefined4) override; // vtable+0x04
	void VTable0x08(undefined4, undefined4, undefined4) override; // vtable+0x08
	void VTable0x0c(undefined4, undefined4, undefined4) override; // vtable+0x0c
	void VTable0x10(undefined4, undefined4, undefined4) override; // vtable+0x10
	void VTable0x14(undefined4, undefined4, undefined4) override; // vtable+0x14
	void VTable0x18(undefined4, undefined4, undefined4) override; // vtable+0x18
	void VTable0x1c(undefined4, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x20(undefined4, undefined4, undefined4) override; // vtable+0x20
	void VTable0x24(undefined4, undefined4, undefined4) override; // vtable+0x24
	void VTable0x28(undefined4, undefined4, undefined4) override; // vtable+0x28
	void VTable0x2c(undefined4, undefined4, undefined4) override; // vtable+0x2c
	virtual ~CrimsonPebble0x228();                                // vtable+0x30

	void Reset();
	void FUN_004a12e0(GolFileParser* p_unk0x04);
	void FUN_004a24e0();

	undefined4 GetUnk0x118() const { return m_unk0x118; }
	void SetStringTable(GolStringTable* p_stringTable) { m_stringTable = p_stringTable; }

	// SYNTHETIC: LEGORACERS 0x004a0390
	// CrimsonPebble0x228::`scalar deleting destructor'

private:
	void FUN_004a0bf0();

	undefined4* m_unk0x04;         // 0x004
	undefined4 m_unk0x08;          // 0x008
	undefined4* m_unk0x0c;         // 0x00c
	undefined4 m_unk0x10;          // 0x010
	SoundNode m_unk0x14;           // 0x014
	undefined4* m_unk0x64;         // 0x064
	undefined4 m_unk0x68;          // 0x068
	undefined4* m_unk0x6c;         // 0x06c
	undefined4* m_unk0x70;         // 0x070
	undefined4* m_unk0x74;         // 0x074
	LegoU32 m_unk0x78;             // 0x078
	GolStringTable* m_unk0x7c;     // 0x07c
	LegoChar* m_unk0x80;           // 0x080
	undefined4 m_unk0x84;          // 0x084
	undefined4* m_unk0x88;         // 0x088
	undefined4* m_unk0x8c;         // 0x08c
	undefined4 m_unk0x90;          // 0x090
	undefined4* m_unk0x94;         // 0x094
	undefined4* m_unk0x98;         // 0x098
	undefined4 m_unk0x9c;          // 0x09c
	undefined4* m_unk0xa0;         // 0x0a0
	undefined4* m_unk0xa4;         // 0x0a4
	GolNameTable m_unk0xa8;        // 0x0a8
	undefined4 m_unk0xb4;          // 0x0b4
	undefined4* m_unk0xb8;         // 0x0b8
	GolNameTable m_unk0xbc;        // 0x0bc
	undefined4 m_unk0xc8;          // 0x0c8
	undefined4* m_unk0xcc;         // 0x0cc
	GolNameTable m_unk0xd0;        // 0x0d0
	undefined4 m_unk0xdc;          // 0x0dc
	undefined4* m_unk0xe0;         // 0x0e0
	GolNameTable m_unk0xe4;        // 0x0e4
	undefined4 m_unk0xf0;          // 0x0f0
	undefined4* m_unk0xf4;         // 0x0f4
	GolNameTable m_unk0xf8;        // 0x0f8
	undefined4 m_unk0x104;         // 0x104
	undefined4* m_unk0x108;        // 0x108
	GolNameTable m_unk0x10c;       // 0x10c
	undefined4 m_unk0x118;         // 0x118
	undefined4* m_unk0x11c;        // 0x11c
	GolNameTable m_unk0x120;       // 0x120
	undefined4 m_unk0x12c;         // 0x12c
	undefined4* m_unk0x130;        // 0x130
	undefined4 m_unk0x134;         // 0x134
	undefined4* m_unk0x138;        // 0x138
	GolNameTable m_unk0x13c;       // 0x13c
	undefined4 m_unk0x148;         // 0x148
	undefined4* m_unk0x14c;        // 0x14c
	GolNameTable m_unk0x150;       // 0x150
	undefined4 m_unk0x15c;         // 0x15c
	undefined4* m_unk0x160;        // 0x160
	GolNameTable m_unk0x164;       // 0x164
	undefined4 m_unk0x170;         // 0x170
	undefined4* m_unk0x174;        // 0x174
	GolNameTable m_unk0x178;       // 0x178
	undefined4 m_unk0x184;         // 0x184
	undefined4* m_unk0x188;        // 0x188
	GolNameTable m_unk0x18c;       // 0x18c
	undefined4 m_unk0x198;         // 0x198
	undefined4* m_unk0x19c;        // 0x19c
	GolNameTable m_unk0x1a0;       // 0x1a0
	undefined4 m_unk0x1ac;         // 0x1ac
	undefined4* m_unk0x1b0;        // 0x1b0
	GolNameTable m_unk0x1b4;       // 0x1b4
	undefined4 m_unk0x1c0;         // 0x1c0
	undefined4* m_unk0x1c4;        // 0x1c4
	GolNameTable m_unk0x1c8;       // 0x1c8
	undefined4 m_unk0x1d4;         // 0x1d4
	undefined4* m_unk0x1d8;        // 0x1d8
	GolNameTable m_unk0x1dc;       // 0x1dc
	undefined4 m_unk0x1e8;         // 0x1e8
	undefined4* m_unk0x1ec;        // 0x1ec
	GolNameTable m_unk0x1f0;       // 0x1f0
	undefined4 m_unk0x1fc;         // 0x1fc
	undefined4* m_unk0x200;        // 0x200
	GolNameTable m_unk0x204;       // 0x204
	undefined4 m_unk0x210;         // 0x210
	undefined4* m_unk0x214;        // 0x214
	GolNameTable m_unk0x218;       // 0x218
	GolStringTable* m_stringTable; // 0x224
};

#endif // CRIMSONPEBBLE0X228_H
