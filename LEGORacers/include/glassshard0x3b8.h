#ifndef GLASSSHARD0X3B8_H
#define GLASSSHARD0X3B8_H

#include "bronzefalcon0xc8770.h"
#include "compat.h"
#include "decomp.h"
#include "opalhaven0xf4.h"
#include "silverhollow0xb8.h"
#include "types.h"

class GolExport;

// VTABLE: LEGORACERS 0x004b01a0
// SIZE 0x3b8
class GlassShard0x3b8 {
public:
	GlassShard0x3b8();
	virtual ~GlassShard0x3b8(); // vtable+0x00

	// SYNTHETIC: LEGORACERS 0x00422390
	// GlassShard0x3b8::`scalar deleting destructor'

	void FUN_004223c0();
	void FUN_00422420(BronzeFalcon0xc8770* p_unk0x04, GolExport* p_unk0x08, undefined4 p_unk0x0c, undefined4 p_unk0x10);
	void FUN_00422670();
	undefined4* GetUnk0x14() { return m_unk0x14; }

private:
	undefined4* m_unk0x04;               // 0x04
	GolExport* m_golExport;              // 0x08
	undefined4* m_unk0x0c;               // 0x0c
	undefined4* m_unk0x10;               // 0x10
	undefined4* m_unk0x14;               // 0x14
	undefined m_unk0x18[0x1c - 0x18];    // 0x18
	OpalHaven0xf4 m_unk0x1c;             // 0x1c
	undefined m_unk0x110[0x114 - 0x110]; // 0x110
	OpalHaven0xf4 m_unk0x114;            // 0x114
	undefined m_unk0x208[0x20c - 0x208]; // 0x208
	OpalHaven0xf4 m_unk0x20c;            // 0x20c
	SilverHollow0xb8 m_unk0x300;         // 0x300
};

#endif // GLASSSHARD0X3B8_H
