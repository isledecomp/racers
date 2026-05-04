#ifndef IMAGINARYLEVER0X1D7C
#define IMAGINARYLEVER0X1D7C

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3d1c
// SIZE 0x1d7c
class ImaginaryLever0x1d7c : public ImaginaryTool0x368 {
public:
	ImaginaryLever0x1d7c();

	void VTable0x38(undefined4) override;                                              // vtable+0x38
	void VTable0x4c() override;                                                        // vtable+0x4c
	~ImaginaryLever0x1d7c() override;                                                  // vtable+0x68
	void VTable0x74() override;                                                        // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00486c80
	// ImaginaryLever0x1d7c::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x1d7c - 0x368]; // 0x0368
};

#endif // IMAGINARYLEVER0X1D7C
