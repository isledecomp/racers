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

	undefined4 VTable0x18(
		ObscureIcon0x1a8*,
		OnyxCircularBuffer0x1c::Item*,
		undefined4,
		undefined4
	) override;                                                                  // vtable+0x18
	void VTable0x4c(undefined4) override;                                        // vtable+0x4c
	void VTable0x54() override;                                                  // vtable+0x54
	~ImaginarySpool0x2cc4() override;                                            // vtable+0x68
	void VTable0x74() override;                                                  // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                  // vtable+0x78
	void VTable0x80() override;                                                  // vtable+0x80
	void VTable0x84() override;                                                  // vtable+0x84
	void VTable0x88() override;                                                  // vtable+0x88
	void VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x004816f0
	// ImaginarySpool0x2cc4::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x2cc4 - 0x368]; // 0x0368
};

#endif // IMAGINARYSPOOL0X2CC4
