#ifndef IMAGINARYFEATHER0X658
#define IMAGINARYFEATHER0X658

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3640
// SIZE 0x658
class ImaginaryFeather0x658 : public ImaginaryTool0x368 {
public:
	ImaginaryFeather0x658();

	void VTable0x4c(undefined4) override;             // vtable+0x4c
	~ImaginaryFeather0x658() override;                // vtable+0x68
	void VTable0x74() override;                       // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;       // vtable+0x78
	void VTable0x84() override;                       // vtable+0x84
	void VTable0x8c(undefined4, undefined4) override; // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x004809d0
	// ImaginaryFeather0x658::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x658 - 0x368]; // 0x368
};

#endif // IMAGINARYFEATHER0X658
