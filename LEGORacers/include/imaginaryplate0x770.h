#ifndef IMAGINARYPLATE0X770
#define IMAGINARYPLATE0X770

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3818
// SIZE 0x770
class ImaginaryPlate0x770 : public ImaginaryTool0x368 {
public:
	ImaginaryPlate0x770();

	void VTable0x38(undefined4) override;                                        // vtable+0x38
	void VTable0x4c(undefined4) override;                                        // vtable+0x4c
	~ImaginaryPlate0x770() override;                                             // vtable+0x68
	void VTable0x74() override;                                                  // vtable+0x74
	void VTable0x84() override;                                                  // vtable+0x84
	void VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x00482070
	// ImaginaryPlate0x770::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x770 - 0x368]; // 0x368
};

#endif // IMAGINARYPLATE0X770
