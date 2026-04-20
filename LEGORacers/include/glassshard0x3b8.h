#ifndef GLASSSHARD0X3B8_H
#define GLASSSHARD0X3B8_H

#include "compat.h"
#include "decomp.h"
#include "opalhaven0xf4.h"
#include "silverhollow0xb8.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b01a0
// SIZE 0x3b8
class GlassShard0x3b8 {
public:
	GlassShard0x3b8();
	virtual ~GlassShard0x3b8(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x00422390
	// GlassShard0x3b8::`scalar deleting destructor'

	void FUN_004223c0();
	void FUN_00422670();

private:
	undefined m_unk0x04[0x1c - 0x04];    // 0x04
	OpalHaven0xf4 m_unk0x1c;             // 0x1c
	undefined m_unk0x110[0x114 - 0x110]; // 0x110
	OpalHaven0xf4 m_unk0x114;            // 0x114
	undefined m_unk0x208[0x20c - 0x208]; // 0x208
	OpalHaven0xf4 m_unk0x20c;            // 0x20c
	SilverHollow0xb8 m_unk0x300;         // 0x300
};

#endif // GLASSSHARD0X3B8_H
