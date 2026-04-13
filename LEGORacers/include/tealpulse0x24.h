#ifndef TEALPULSE0X24_H
#define TEALPULSE0X24_H

#include "decomp.h"
#include "types.h"

#include <windows.h>

// VTABLE: LEGORACERS 0x4b0f28
// SIZE 0x24
class TealPulse0x24 {
public:
	struct Entry {
		LegoChar* m_data; // 0x00
		Entry* m_next;    // 0x04
	};

	TealPulse0x24();
	~TealPulse0x24();

	virtual void VTable0x00();                           // vtable+0x00
	virtual Entry* VTable0x04(Entry**, const LegoChar*); // vtable+0x04
	virtual LegoS32 VTable0x08(LegoS32, LegoU32);        // vtable+0x08
	virtual LegoS32 VTable0x0c();                        // vtable+0x0c

	void FUN_0044c5a0();

private:
	HANDLE m_unk0x04;     // 0x04
	Entry** m_unk0x08;    // 0x08
	LegoChar* m_unk0x0c;  // 0x0c
	LegoChar* m_unk0x10;  // 0x10
	LegoS32 m_unk0x14;    // 0x14
	LegoU32 m_unk0x18;    // 0x18
	undefined4 m_unk0x1c; // 0x1c
	undefined m_unk0x20;  // 0x20
};

#endif // TEALPULSE0X24_H
