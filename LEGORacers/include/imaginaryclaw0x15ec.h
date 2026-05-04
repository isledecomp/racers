#ifndef IMAGINARYCLAW0X15EC
#define IMAGINARYCLAW0X15EC

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3a38
// SIZE 0x15ec
class ImaginaryClaw0x15ec : public ImaginaryTool0x368 {
public:
	ImaginaryClaw0x15ec();

	void VTable0x38(undefined4) override;                                              // vtable+0x38
	void VTable0x44(undefined4) override;                                              // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	~ImaginaryClaw0x15ec() override;                                                   // vtable+0x68
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484430
	// ImaginaryClaw0x15ec::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x15ec - 0x368]; // 0x0368
};

#endif // IMAGINARYCLAW0X15EC
