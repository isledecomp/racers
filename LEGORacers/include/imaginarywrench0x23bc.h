#ifndef IMAGINARYWRENCH0X23BC_H
#define IMAGINARYWRENCH0X23BC_H

#include "compat.h"
#include "crimsonray0x20.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b31f8
// SIZE 0x23bc
class ImaginaryWrench0x23bc : public ImaginaryTool0x368 {
public:
	ImaginaryWrench0x23bc();

	void VTable0x38(undefined4) override; // vtable+0x38
	void VTable0x3c(undefined4) override; // vtable+0x3c
	void VTable0x40(undefined4) override; // vtable+0x40
	void VTable0x44(undefined4) override; // vtable+0x44
	void VTable0x4c(undefined4) override; // vtable+0x4c
	void VTable0x54() override;           // vtable+0x54
	void VTable0x68() override;           // vtable+0x68
	void VTable0x74() override;           // vtable+0x74
	void VTable0x84() override;           // vtable+0x84
	void VTable0x8c() override;           // vtable+0x8c
	void VTable0x90(undefined4) override; // vtable+0x90
	void VTable0x94(undefined4) override; // vtable+0x94

	void FUN_0047ba00();

protected:
	undefined m_unk0x04[0x23bc - 0x368]; // 0x04
};

#endif // IMAGINARYWRENCH0X23BC_H
