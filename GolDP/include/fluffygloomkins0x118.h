#ifndef FLUFFYGLOOMKINS0X118_H
#define FLUFFYGLOOMKINS0X118_H

#include "compat.h"
#include "decomp.h"
#include "zoweeblubberworth0xf0.h"

// SIZE 0x118
// VTABLE GOLDP 0x1005690c
class FluffyGloomkins : public ZoweeBlubberworth0xf0 {
public:
	FluffyGloomkins();
	~FluffyGloomkins() override;
	void Vtable0x08(void) override;              // vtable+0x08
	void Vtable0x0c(void) override;              // vtable+0x0c
	void Vtable0x18(void) override;              // vtable+0x1c
	void Vtable0x1c(undefined4*) override;       // vtable+0x1c
	void Vtable0x20(undefined4) override;        // vtable+0x20
	void Vtable0x24(undefined4) override;        // vtable+0x24
	void Vtable0x28(undefined4*) override;       // vtable+0x28
	undefined4* Vtable0x2c(undefined4) override; // vtable+0x2c
	undefined4* Vtable0x30(undefined4) override; // vtable+0x30
	undefined4* Vtable0x34(undefined4) override; // vtable+0x34
	undefined4* Vtable0x38(undefined4) override; // vtable+0x38
	undefined4* Vtable0x3c(undefined4) override; // vtable+0x3c
	undefined4* Vtable0x40(undefined4) override; // vtable+0x40
	undefined4* Vtable0x44(undefined4) override; // vtable+0x44
	undefined4* Vtable0x48(undefined4) override; // vtable+0x48
	undefined4* Vtable0x4c(undefined4) override; // vtable+0x4c
	undefined4* Vtable0x50(undefined4) override; // vtable+0x50

	// SYNTHETIC: GOLDP 0x100171e0
	// FluffyGloomkins::`scalar deleting destructor'

private:
	void FUN_10017390();

	undefined m_unk0xc0[0x118 - 0xf0];
};

#endif // FLUFFYGLOOMKINS0X118_H
