#ifndef IMAGINARYRULER0X2E60
#define IMAGINARYRULER0X2E60

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3dc8
// SIZE 0x2e60
class ImaginaryRuler0x2e60 : public ImaginaryTool0x368 {
public:
	ImaginaryRuler0x2e60();

	void VTable0x38(undefined4) override;             // vtable+0x38
	void VTable0x3c(undefined4) override;             // vtable+0x3c
	void VTable0x44(undefined4) override;             // vtable+0x44
	void VTable0x4c(undefined4) override;             // vtable+0x4c
	void VTable0x54() override;                       // vtable+0x54
	~ImaginaryRuler0x2e60() override;                 // vtable+0x68
	void VTable0x74() override;                       // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;       // vtable+0x78
	void VTable0x84() override;                       // vtable+0x84
	void VTable0x8c(undefined4, undefined4) override; // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x00487990
	// ImaginaryRuler0x2e60::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x2e60 - 0x368]; // 0x368
};

#endif // IMAGINARYRULER0X2E60
