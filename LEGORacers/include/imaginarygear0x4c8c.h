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

	void VTable0x4c(undefined4) override{}; // vtable+0x4c
	~ImaginaryGear0x4c8c() override;        // vtable+0x68
	void VTable0x84() override {}           // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x00484cc0
	// ImaginaryGear0x4c8c::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x4c8c - 0x368]; // 0x0368
};

#endif // IMAGINARYGEAR0X4C8C
