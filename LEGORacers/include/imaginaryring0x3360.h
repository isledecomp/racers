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

	void VTable0x4c(undefined4) override{}; // vtable+0x4c
	~ImaginaryRing0x3360() override;        // vtable+0x68
	void VTable0x84() override {}           // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x0047a690
	// ImaginaryRing0x3360::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x3360 - 0x368]; // 0x0368
};

#endif // IMAGINARYRING0X3360
