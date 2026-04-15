#ifndef IMAGINARYTOOL0X368_H
#define IMAGINARYTOOL0X368_H

#include "compat.h"
#include "decomp.h"
#include "imaginarynotion0x280.h"

// VTABLE: LEGORACERS 0x004b3518
// SIZE 0x368
class ImaginaryTool0x368 : public ImaginaryNotion0x280 {
public:
	ImaginaryTool0x368();

	undefined4 VTable0x18(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x34(undefined4) override;                                           // vtable+0x34
	void VTable0x3c(undefined4) override;                                           // vtable+0x3c
	void VTable0x40(undefined4) override;                                           // vtable+0x40
	void VTable0x54() override;                                                     // vtable+0x54
	void VTable0x5c() override;                                                     // vtable+0x5c
	void VTable0x64() override;                                                     // vtable+0x64
	void VTable0x68() override;                                                     // vtable+0x68
	void VTable0x6c() override;                                                     // vtable+0x6c
	void VTable0x74() override;                                                     // vtable+0x74
	void VTable0x78() override;                                                     // vtable+0x78
	virtual void VTable0x80();                                                      // vtable+0x80
	virtual void VTable0x84() = 0;                                                  // vtable+0x84
	virtual void VTable0x88();                                                      // vtable+0x88
	virtual void VTable0x8c();                                                      // vtable+0x8c
	virtual void VTable0x90(undefined4);                                            // vtable+0x90
	virtual void VTable0x94(undefined4);                                            // vtable+0x94

protected:
	undefined m_unk0x280[0x368 - 0x280]; // 0x280
};

#endif // IMAGINARYTOOL0X368_H
