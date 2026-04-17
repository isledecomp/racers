#ifndef FLUFFYGLOOMKINS0X118_H
#define FLUFFYGLOOMKINS0X118_H

#include "compat.h"
#include "decomp.h"
#include "zoweeblubberworth0xf0.h"

// SIZE 0x118
// VTABLE: GOLDP 0x1005690c
class FluffyGloomkins : public ZoweeBlubberworth0xf0 {
public:
	FluffyGloomkins();
	~FluffyGloomkins() override;
	undefined4* VTable0x08(void) override;       // vtable+0x08
	undefined4* VTable0x0c(void) override;       // vtable+0x0c
	void VTable0x18(void) override;              // vtable+0x1c
	void VTable0x1c(undefined4*) override;       // vtable+0x1c
	void VTable0x20(undefined4) override;        // vtable+0x20
	void VTable0x24(undefined4) override;        // vtable+0x24
	void VTable0x28(undefined4*) override;       // vtable+0x28
	undefined4* VTable0x2c(undefined4) override; // vtable+0x2c
	undefined4* VTable0x30(undefined4) override; // vtable+0x30
	undefined4* VTable0x34(undefined4) override; // vtable+0x34
	undefined4* VTable0x38(undefined4) override; // vtable+0x38
	undefined4* VTable0x3c(undefined4) override; // vtable+0x3c
	undefined4* VTable0x40(undefined4) override; // vtable+0x40
	undefined4* VTable0x44(undefined4) override; // vtable+0x44
	undefined4* VTable0x48(undefined4) override; // vtable+0x48
	undefined4* VTable0x4c(undefined4) override; // vtable+0x4c
	undefined4* VTable0x50(undefined4) override; // vtable+0x50

	// SYNTHETIC: GOLDP 0x100171e0
	// FluffyGloomkins::`scalar deleting destructor'

private:
	void FUN_10017390();

	undefined m_unk0xc0[0x118 - 0xf0];
};

#endif // FLUFFYGLOOMKINS0X118_H
