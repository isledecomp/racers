#ifndef IMAGINARYBELT0X2548
#define IMAGINARYBELT0X2548

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3ad0
// SIZE 0x2548
class ImaginaryBelt0x2548 : public ImaginaryTool0x368 {
public:
	ImaginaryBelt0x2548();

	void VTable0x38(undefined4) override;                                              // vtable+0x38
	void VTable0x4c() override;                                                        // vtable+0x4c
	~ImaginaryBelt0x2548() override;                                                   // vtable+0x68
	void VTable0x74() override;                                                        // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484800
	// ImaginaryBelt0x2548::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x2548 - 0x368]; // 0x0368
};

#endif // IMAGINARYBELT0X2548
