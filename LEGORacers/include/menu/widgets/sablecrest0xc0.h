#ifndef SABLECREST0XC0_H
#define SABLECREST0XC0_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/obscurezebra0xa4.h"

// VTABLE: LEGORACERS 0x004b20a0
// SIZE 0xc0
class SableCrest0xc0 : public ObscureZebra0xa4 {
public:
	SableCrest0xc0();

	void Reset() override;                                 // vtable+0x00
	~SableCrest0xc0() override;                            // vtable+0x04
	void VTable0x10(Rect*) override;                       // vtable+0x10
	ObscureVantage0x58* VTable0x38(Rect*, Rect*) override; // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;            // vtable+0x3c

	// SYNTHETIC: LEGORACERS 0x00467ec0
	// SableCrest0xc0::`scalar deleting destructor'

protected:
	undefined4 m_unk0xa4; // 0xa4
	undefined4 m_unk0xa8; // 0xa8
	undefined4 m_unk0xac; // 0xac
	undefined4 m_unk0xb0; // 0xb0
	undefined4 m_unk0xb4; // 0xb4
	undefined4 m_unk0xb8; // 0xb8
	undefined4 m_unk0xbc; // 0xbc
};

#endif // SABLECREST0XC0_H
