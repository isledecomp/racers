#ifndef IMAGINARYGEAR0X4C8C
#define IMAGINARYGEAR0X4C8C

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3b68
// SIZE 0x4c8c
class ImaginaryGear0x4c8c : public ImaginaryTool0x368 {
public:
	ImaginaryGear0x4c8c();

	void VTable0x10(undefined4) override;                                              // vtable+0x10
	void VTable0x38(undefined4) override;                                              // vtable+0x38
	void VTable0x44(undefined4) override;                                              // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void VTable0x54() override;                                                        // vtable+0x54
	~ImaginaryGear0x4c8c() override;                                                   // vtable+0x68
	void VTable0x74() override;                                                        // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x80() override;                                                        // vtable+0x80
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x88() override;                                                  // vtable+0x88
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484cc0
	// ImaginaryGear0x4c8c::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x4c8c - 0x368]; // 0x0368
};

#endif // IMAGINARYGEAR0X4C8C
