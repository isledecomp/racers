#ifndef BRONZEDUNE0X4C_H
#define BRONZEDUNE0X4C_H

#include "bronzedunebag0xc.h"
#include "compat.h"
#include "golddune0x38.h"

// SIZE 0x4c
// VTABLE: GOLDP 0x10056300
class BronzeDune0x4c : public GoldDune0x38 {
public:
	BronzeDune0x4c();
	~BronzeDune0x4c() override;                         // vtable+0x00
	IPalette0x4* GetPalette() override;                 // vtable+0x1c
	void VTable0x30(undefined4*, undefined4*) override; // vtable+0x30
	void VTable0x34() override;                         // vtable+0x34
	void VTable0x38() override;                         // vtable+0x38

	// SYNTHETIC: GOLDP 0x10004450
	// BronzeDune0x4c::`scalar deleting destructor'

protected:
	undefined m_unk0x38[0x40 - 0x38];
	BronzeDuneBag0xc m_unk0x40;
};

#endif // BRONZEDUNE0X4C_H
