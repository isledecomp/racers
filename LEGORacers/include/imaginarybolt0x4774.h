#ifndef IMAGINARYBOLT0X4774
#define IMAGINARYBOLT0X4774

#include "compat.h"
#include "decomp.h"
#include "imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b332c
// SIZE 0x4774
class ImaginaryBolt0x4774 : public ImaginaryTool0x368 {
public:
	ImaginaryBolt0x4774();

	void VTable0x4c(undefined4) override{}; // vtable+0x4c
	~ImaginaryBolt0x4774() override;        // vtable+0x68
	void VTable0x84() override {}           // vtable+0x84

	// SYNTHETIC: LEGORACERS 0x0047cf70
	// ImaginaryBolt0x4774::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x4774 - 0x368]; // 0x0368
};

#endif // IMAGINARYBOLT0X4774
