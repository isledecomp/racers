#ifndef IMAGINARYBOLT0X4774
#define IMAGINARYBOLT0X4774

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b332c
// SIZE 0x4774
class ImaginaryBolt0x4774 : public ImaginaryTool0x368 {
public:
	ImaginaryBolt0x4774();

	undefined4 VTable0x18(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x18
	void VTable0x38(undefined4) override;                                           // vtable+0x38
	void VTable0x44(undefined4) override;                                           // vtable+0x44
	void VTable0x4c(undefined4) override;                                           // vtable+0x4c
	void VTable0x54() override;                                                     // vtable+0x54
	~ImaginaryBolt0x4774() override;                                                // vtable+0x68
	void VTable0x74() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                     // vtable+0x78
	void VTable0x84() override;                                                     // vtable+0x84
	void VTable0x88() override;                                                     // vtable+0x88
	void VTable0x8c(undefined4, undefined4) override;                               // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047cf70
	// ImaginaryBolt0x4774::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x4774 - 0x368]; // 0x0368
};

#endif // IMAGINARYBOLT0X4774
