#ifndef OBSCUREICON0X1A8_H
#define OBSCUREICON0X1A8_H

#include "compat.h"
#include "decomp.h"
#include "obscurevantage0x58.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b2944
// SIZE 0x1a8
class ObscureIcon0x1a8 : public ObscureVantage0x58 {
public:
	ObscureIcon0x1a8();
	void VTable0x00() override; // vtable+0x00
	~ObscureIcon0x1a8() override;
	void VTable0x08() override;                                         // vtable+0x08
	void VTable0x10(undefined4) override;                               // vtable+0x10
	undefined4 VTable0x2c(undefined4, undefined4, undefined4) override; // vtable+0x2c
	undefined4 VTable0x30(undefined4, undefined4, undefined4) override; // vtable+0x30
	undefined4 VTable0x34(undefined4, undefined4, undefined4) override; // vtable+0x34
	undefined4 VTable0x38(undefined4, undefined4) override;             // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;                         // vtable+0x3c

	// SYNTHETIC: LEGORACERS 0x00471c80
	// ObscureIcon0x1a8::`scalar deleting destructor'

protected:
	undefined m_unk0x58[0x1a8 - 0x58]; // 0x58
};

#endif // OBSCUREICON0X1A8_H
