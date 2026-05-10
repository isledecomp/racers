#ifndef IMAGINARYORB0X7B0
#define IMAGINARYORB0X7B0

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b2c5c
// SIZE 0x7b0
class ImaginaryOrb0x7b0 : public ImaginaryTool0x368 {
public:
	ImaginaryOrb0x7b0();

	void VTable0x4c() override;                                                        // vtable+0x4c
	~ImaginaryOrb0x7b0() override;                                                     // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00475cb0
	// ImaginaryOrb0x7b0::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x7b0 - 0x368]; // 0x368
};

#endif // IMAGINARYORB0X7B0
