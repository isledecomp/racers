#ifndef IMAGINARYDRILL0x2450
#define IMAGINARYDRILL0x2450

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b36d8
// SIZE 0x2450
class ImaginaryDrill0x2450 : public ImaginaryTool0x368 {
public:
	ImaginaryDrill0x2450();

	undefined4 VTable0x18(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(undefined4, undefined4, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x38(undefined4) override;                                           // vtable+0x38
	void VTable0x4c(undefined4) override;                                           // vtable+0x4c
	void VTable0x54() override;                                                     // vtable+0x54
	~ImaginaryDrill0x2450() override;                                               // vtable+0x68
	void VTable0x74() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                     // vtable+0x78
	void VTable0x84() override;                                                     // vtable+0x84
	void VTable0x8c(undefined4, undefined4) override;                               // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x00480cb0
	//  ImaginaryDrill0x2450::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x2450 - 0x368]; // 0x368
};

#endif // IMAGINARYDRILL0x2450
