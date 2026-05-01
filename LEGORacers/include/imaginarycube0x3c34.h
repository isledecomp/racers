#ifndef IMAGINARYCUBE0X3C34
#define IMAGINARYCUBE0X3C34

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b2a38
// SIZE 0x3c34
class ImaginaryCube0x3c34 : public ImaginaryTool0x368 {
public:
	ImaginaryCube0x3c34();

	void VTable0x4c(undefined4) override{}; // vtable+0x4c
	~ImaginaryCube0x3c34() override;        // vtable+0x68
	void VTable0x84() override {}           // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x00473790
	// ImaginaryCube0x3c34::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x3c34 - 0x368]; // 0x0368
};

#endif // IMAGINARYCUBE0X3C34
