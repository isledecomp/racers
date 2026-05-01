#ifndef IMAGINARYSPOOL0X2CC4
#define IMAGINARYSPOOL0X2CC4

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3774
// SIZE 0x2cc4
class ImaginarySpool0x2cc4 : public ImaginaryTool0x368 {
public:
	ImaginarySpool0x2cc4();

	void VTable0x4c(undefined4) override{}; // vtable+0x4c
	~ImaginarySpool0x2cc4() override;       // vtable+0x68
	void VTable0x84() override {}           // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x004816f0
	// ImaginarySpool0x2cc4::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x2cc4 - 0x368]; // 0x0368
};

#endif // IMAGINARYSPOOL0X2CC4
