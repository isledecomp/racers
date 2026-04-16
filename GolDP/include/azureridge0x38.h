#ifndef GOLDP_AZURERIDGE0X38_H
#define GOLDP_AZURERIDGE0X38_H

#include "compat.h"
#include "silverdune0x30.h"

class GolDrawState;

// VTABLE: GOLDP 0x10056dc4
// SIZE 0x38
class AzureRidge0x38 : public SilverDune0x30 {
public:
	AzureRidge0x38();
	~AzureRidge0x38() override; // vtable+0x00

	virtual void VTable0x30(
		GolDrawState* p_drawState,
		undefined4 p_width,
		undefined4 p_height,
		undefined4 p_bpp
	);                                   // vtable+0x30
	virtual void VTable0x34();           // vtable+0x34
	virtual void VTable0x38(undefined4); // vtable+0x38
	virtual void VTable0x3c() = 0;       // vtable+0x3c

	// SYNTHETIC: GOLDP 0x1001d750
	// AzureRidge0x38::`scalar deleting destructor'

protected:
	undefined4 m_unk0x30; // 0x30
	undefined4 m_unk0x34; // 0x34
};

#endif // GOLDP_AZURERIDGE0X38_H
