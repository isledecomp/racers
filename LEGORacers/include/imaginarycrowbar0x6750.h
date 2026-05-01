#ifndef IMAGINARYCROWBAR0X6750
#define IMAGINARYCROWBAR0X6750

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b2b04
// SIZE 0x6750
class ImaginaryCrowbar0x6750 : public ImaginaryTool0x368 {
public:
	ImaginaryCrowbar0x6750();

	void VTable0x4c(undefined4) override{}; // vtable+0x4c
	~ImaginaryCrowbar0x6750() override;     // vtable+0x68
	void VTable0x84() override {}           // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x004755f0
	// ImaginaryCrowbar0x6750::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x6750 - 0x368]; // 0x0368
};

#endif // IMAGINARYCROWBAR0X6750
