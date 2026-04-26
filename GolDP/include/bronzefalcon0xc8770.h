#ifndef BRONZEFALCON0XC8770_H
#define BRONZEFALCON0XC8770_H

#include "decomp.h"
#include "types.h"

class GolCommonDrawState;
class SmallCocoon0xc;

// VTABLE: GOLDP 0x100565b8
// SIZE 0xc8770
class BronzeFalcon0xc8770 {
public:
	BronzeFalcon0xc8770();

	virtual void VTable0x00();                                              // vtable+0x00
	virtual void VTable0x04();                                              // vtable+0x04
	virtual ~BronzeFalcon0xc8770();                                         // vtable+0x08
	virtual void VTable0x0c(undefined4, undefined4, undefined4);            // vtable+0x0c
	virtual GolCommonDrawState* GetDrawState();                             // vtable+0x10
	virtual void VTable0x14();                                              // vtable+0x14
	virtual void VTable0x18();                                              // vtable+0x18
	virtual void VTable0x1c(undefined4);                                    // vtable+0x1c
	virtual void VTable0x20(undefined4);                                    // vtable+0x20
	virtual void VTable0x24();                                              // vtable+0x24
	virtual void VTable0x28();                                              // vtable+0x28
	virtual void VTable0x2c(undefined4);                                    // vtable+0x2c
	virtual void VTable0x30(undefined4);                                    // vtable+0x30
	virtual void VTable0x34(LegoS32 p_unk0x04, const LegoFloat* p_unk0x08); // vtable+0x34
	virtual void VTable0x38();                                              // vtable+0x38

	void FUN_10028ad0(SmallCocoon0xc* p_param);
	void FUN_10028ae0(SmallCocoon0xc* p_param);

	// SYNTHETIC: GOLDP 0x10007960
	// BronzeFalcon0xc8770::`scalar deleting destructor'

	undefined4* GetUnk0x0c() { return m_unk0x0c; }

private:
	friend class GolCommonDrawState;

	undefined m_unk0x04[0x0c - 0x04];             // 0x04
	undefined4* m_unk0x0c;                        // 0x0c
	undefined m_unk0x10[0x48 - 0x10];             // 0x10
	BronzeFalcon0xc8770* m_nextDrawStateRenderer; // 0x48
	undefined m_unk0x4c[0x140 - 0x4c];            // 0x4c
	GolCommonDrawState* m_drawState;              // 0x140
	undefined m_unk0x144[0xc8770 - 0x144];        // 0x144
};

#endif // BRONZEFALCON0XC8770_H
