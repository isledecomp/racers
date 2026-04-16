#ifndef GOLDP_SLATEPEAK0X58_H
#define GOLDP_SLATEPEAK0X58_H

#include "azureridge0x38.h"
#include "compat.h"
#include "pearldew0x0c.h"

// VTABLE: GOLDP 0x1005627c
// SIZE 0x58
class SlatePeak0x58 : public AzureRidge0x38 {
public:
	SlatePeak0x58();
	~SlatePeak0x58() override;                                      // vtable+0x00
	void VTable0x04(undefined4*, undefined4*, undefined4) override; // vtable+0x04
	void VTable0x08() override;                                     // vtable+0x08
	void VTable0x0c(undefined4*, undefined4*, undefined4) override; // vtable+0x0c
	void VTable0x10() override;                                     // vtable+0x10
	void VTable0x14(undefined4*) override;                          // vtable+0x14
	void VTable0x18() override;                                     // vtable+0x18
	undefined4 VTable0x1c() override;                               // vtable+0x1c
	void VTable0x20(undefined4, undefined4, undefined4) override;   // vtable+0x20
	void VTable0x28(undefined4, undefined4, undefined4*) override;  // vtable+0x28
	void VTable0x2c() override;                                     // vtable+0x2c
	void VTable0x30(
		GolDrawState* p_drawState,
		undefined4 p_width,
		undefined4 p_height,
		undefined4 p_bpp
	) override;                           // vtable+0x30
	void VTable0x34() override;           // vtable+0x34
	void VTable0x38(undefined4) override; // vtable+0x38
	void VTable0x3c() override;           // vtable+0x3c

	// SYNTHETIC: GOLDP 0x10003170
	// SlatePeak0x58::`scalar deleting destructor'

private:
	PearlDew0x0c m_unk0x38; // 0x38
	undefined4 m_unk0x44;   // 0x44
	undefined4 m_unk0x48;   // 0x48
	undefined4 m_unk0x4c;   // 0x4c
	undefined4 m_unk0x50;   // 0x50
	undefined4 m_unk0x54;   // 0x54
};

#endif // GOLDP_SLATEPEAK0X58_H
