#ifndef FLUFFYGLOOMKINS0X118_H
#define FLUFFYGLOOMKINS0X118_H

#include "compat.h"
#include "decomp.h"
#include "zoweeblubberworth0xf0.h"

class AmberLensBase0x120;
class BoundingShape0x2c;

// SIZE 0x118
// VTABLE: GOLDP 0x1005690c
class FluffyGloomkins0x118 : public ZoweeBlubberworth0xf0 {
public:
	FluffyGloomkins0x118();
	~FluffyGloomkins0x118() override;
	undefined4* VTable0x08(void) override;       // vtable+0x08
	undefined4* VTable0x0c(void) override;       // vtable+0x0c
	void VTable0x18(void) override;              // vtable+0x18
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
	// FluffyGloomkins0x118::`scalar deleting destructor'

private:
	void FUN_10017390();

	undefined4* m_unk0xf0;          // 0xf0
	undefined4* m_unk0xf4;          // 0xf4
	undefined4* m_unk0xf8;          // 0xf8
	undefined4* m_unk0xfc;          // 0xfc
	undefined4* m_unk0x100;         // 0x100
	undefined4* m_unk0x104;         // 0x104
	undefined4* m_unk0x108;         // 0x108
	undefined4* m_unk0x10c;         // 0x10c
	BoundingShape0x2c* m_unk0x110;  // 0x110
	AmberLensBase0x120* m_unk0x114; // 0x114
};

#endif // FLUFFYGLOOMKINS0X118_H
