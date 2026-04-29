#ifndef WHITEBAFFOON0X58_H
#define WHITEBAFFOON0X58_H

#include "decomp.h"
#include "types.h"

class BronzeFalcon0xc8770;

// This type is needed because
// - instances of this type have component access like `char[4]`, but copy like an `int`,
// - instances of this type are not aligned to 4 bytes.
struct FourBytes {
	LegoChar m_bytes[4];
};

// VTABLE: GOLDP 0x10056ee4
// SIZE 0x50
class WhiteBaffoon0x50 {
public:
	enum Flags {
		c_flagBit1 = 0x0002,
		c_flagBit2 = 0x0004,
		c_flagBit3 = 0x0008,
		c_flagBit4 = 0x0010,
		c_flagBit5 = 0x0020,
		c_flagBit6 = 0x0040,
		c_flagBit7 = 0x0080,
		c_flagBit11 = 0x0800,
		c_allFlags = 0xffff,
		c_flagsWithoutBit3 = c_allFlags & ~c_flagBit3,
		c_flagsWithoutBit4 = c_allFlags & ~c_flagBit4
	};

	enum StateFlags {
		c_stateFlagBit0 = 0x01
	};

	WhiteBaffoon0x50();

	virtual void VTable0x00() = 0;                                    // vtable+0x00
	virtual void VTable0x04() = 0;                                    // vtable+0x04
	virtual void VTable0x08() = 0;                                    // vtable+0x08
	virtual void VTable0x0c(undefined4, undefined4, undefined4*) = 0; // vtable+0x0c
	virtual void VTable0x10();                                        // vtable+0x10
	virtual ~WhiteBaffoon0x50();                                      // vtable+0x14
	virtual void Reset();                                             // vtable+0x18
	virtual undefined4 VTable0x1c(undefined4, undefined4) = 0;        // vtable+0x1c

	void FUN_1001f430();
	void FUN_1001f790();
	void FUN_1001fde0();

	LegoU32 GetUnk0x3c() const { return m_unk0x3c; }

	// SYNTHETIC: GOLDP 0x1001f240
	// WhiteBaffoon0x50::`scalar deleting destructor'

	struct InnerWhiteBaffon0x24 {
		InnerWhiteBaffon0x24()
		{
			m_unk0x0c = 0;
			m_unk0x10 = 0;
			m_unk0x14 = 0;
			m_unk0x18 = 0;
			m_unk0x1c = 0;
			m_unk0x20 = 0;
			m_unk0x22 = 0;
		}
		undefined4 m_unk0x0c; // 0x0c
		undefined4 m_unk0x10; // 0x10
		undefined4 m_unk0x14; // 0x14
		undefined4 m_unk0x18; // 0x18
		undefined4 m_unk0x1c; // 0x1c
		undefined2 m_unk0x20; // 0x20
		undefined2 m_unk0x22; // 0x22
	};

public:
	undefined4 m_unk0x04;             // 0x04
	undefined4 m_unk0x08;             // 0x08
	InnerWhiteBaffon0x24 m_unk0x0c;   // 0x0c
	BronzeFalcon0xc8770* m_renderer;  // 0x24
	FourBytes m_unk0x28;              // 0x28
	LegoU32 m_unk0x2c;                // 0x2c
	undefined4 m_unk0x30;             // 0x30
	undefined4 m_unk0x34;             // 0x34
	undefined4 m_unk0x38;             // 0x38
	LegoU32 m_unk0x3c;                // 0x3c
	LegoU16 m_flags;                  // 0x40
	FourBytes m_name[2];              // 0x42
	FourBytes m_unk0x4a;              // 0x4a
	undefined m_unk0x4e[0x50 - 0x4e]; // 0x4e
};

#endif // WHITEBAFFOON0X58_H
