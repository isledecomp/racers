#ifndef IMAGINARYBRUSH0X6410
#define IMAGINARYBRUSH0X6410

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b33dc
// SIZE 0x6410
class ImaginaryBrush0x6410 : public ImaginaryTool0x368 {
public:
	ImaginaryBrush0x6410();

	void VTable0x10(undefined4) override;                                              // vtable+0x10
	void VTable0x38(undefined4) override;                                              // vtable+0x38
	void VTable0x44(undefined4) override;                                              // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~ImaginaryBrush0x6410() override;                                                  // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x80() override;                                                        // vtable+0x80
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x88() override;                                                  // vtable+0x88
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047e3e0
	// ImaginaryBrush0x6410::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x6410 - 0x368]; // 0x0368
};

#endif // IMAGINARYBRUSH0X6410
