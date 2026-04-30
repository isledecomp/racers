#ifndef GOLDP_UTOPIANPAN_H
#define GOLDP_UTOPIANPAN_H

#include "bronzedune0x4c.h"
#include "decomp.h"
#include "types.h"
#include "whitebaffoon0x50.h"

class DuskwindBananaRelic0x30;

// SIZE 0xa4
// VTABLE: GOLDP 0x10056340
class UtopianPan0xa4 : public WhiteBaffoon0x50 {
public:
	UtopianPan0xa4();

	void VTable0x00() override;                                    // vtable+0x00
	void VTable0x04() override;                                    // vtable+0x04
	void VTable0x08() override;                                    // vtable+0x08
	void VTable0x0c(undefined4, undefined4, undefined4*) override; // vtable+0x0c
	void VTable0x10() override;                                    // vtable+0x10
	~UtopianPan0xa4() override;                                    // vtable+0x14
	void Reset() override;                                         // vtable+0x18
	undefined4 VTable0x1c(undefined4, undefined4) override;        // vtable+0x1c

	void FUN_100051c0();
	void FUN_10005210();
	void FUN_10005440(undefined4*, undefined4*, undefined4*);

	// SYNTHETIC: GOLDP 0x10005e60
	// UtopianPan0xa4::`vector deleting destructor'

protected:
	undefined4 m_unk0x50;               // 0x50
	DuskwindBananaRelic0x30* m_unk0x54; // 0x54
	BronzeDune0x4c m_unk0x58;           // 0x58
};

#endif // GOLDP_UTOPIANPAN_H
