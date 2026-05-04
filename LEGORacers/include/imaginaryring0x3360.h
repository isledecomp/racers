#ifndef IMAGINARYRING0X3360
#define IMAGINARYRING0X3360

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3160
// SIZE 0x3360
class ImaginaryRing0x3360 : public ImaginaryTool0x368 {
public:
	ImaginaryRing0x3360();

	undefined4 VTable0x18(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override; // vtable+0x18
	undefined4 VTable0x1c(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override;                                                                  // vtable+0x1c
	void VTable0x34(undefined4) override;                                        // vtable+0x34
	void VTable0x38(undefined4) override;                                        // vtable+0x38
	void VTable0x44(undefined4) override;                                        // vtable+0x44
	void VTable0x4c(undefined4) override;                                        // vtable+0x4c
	void VTable0x54() override;                                                  // vtable+0x54
	~ImaginaryRing0x3360() override;                                             // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                  // vtable+0x78
	void VTable0x84() override;                                                  // vtable+0x84
	void VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047a690
	// ImaginaryRing0x3360::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x3360 - 0x368]; // 0x0368
};

#endif // IMAGINARYRING0X3360
