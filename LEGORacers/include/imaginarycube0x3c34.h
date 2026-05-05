#ifndef IMAGINARYCUBE0X3C34
#define IMAGINARYCUBE0X3C34

#include "compat.h"
#include "decomp.h"
#include "imaginaryshape0x2b20.h"

// VTABLE: LEGORACERS 0x004b2a38
// SIZE 0x3c34
class ImaginaryCube0x3c34 : public ImaginaryShape0x2b20 {
public:
	ImaginaryCube0x3c34();

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
	) override;                                                                        // vtable+0x1c
	void VTable0x20(undefined4) override;                                              // vtable+0x20
	void VTable0x24(undefined4) override;                                              // vtable+0x24
	undefined4 VTable0x28(ObscureIcon0x1a8*, void*, undefined4, undefined4) override;  // vtable+0x28
	void VTable0x34(undefined4) override;                                              // vtable+0x34
	void VTable0x38(undefined4) override;                                              // vtable+0x38
	void VTable0x44(undefined4) override;                                              // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void VTable0x54() override;                                                        // vtable+0x54
	~ImaginaryCube0x3c34() override;                                                   // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00473790
	// ImaginaryCube0x3c34::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x3c34 - 0x2b20]; // 0x0368
};

#endif // IMAGINARYCUBE0X3C34
