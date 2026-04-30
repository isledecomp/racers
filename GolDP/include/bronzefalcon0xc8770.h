#ifndef BRONZEFALCON0XC8770_H
#define BRONZEFALCON0XC8770_H

#include "bronzebabyfalcon.h"
#include "decomp.h"
#include "types.h"

class GolCommonDrawState;
class AmberLens0x344;
class GolNameTable;

// VTABLE: GOLDP 0x100565b8
// SIZE 0xc8770
class BronzeFalcon0xc8770 : public BronzeBabyFalcon {
public:
	BronzeFalcon0xc8770();
	~BronzeFalcon0xc8770();

	// TODO: why is override not accepted?
	void VTable0x04();                                   // vtable+0x04
	void VTable0x0c(undefined4, undefined4, undefined4); // vtable+0x0c
	GolCommonDrawState* GetDrawState();                  // vtable+0x10
	void VTable0x14();                                   // vtable+0x14
	void VTable0x18();                                   // vtable+0x18
	void VTable0x1c(JasperRipple0x4*);                   // vtable+0x1c
	void VTable0x20(AmberLens0x344*);                    // vtable+0x20
	void VTable0x28();                                   // vtable+0x28
	void VTable0x2c(undefined4);                         // vtable+0x2c
	void VTable0x30(undefined4);                         // vtable+0x30
	void VTable0x38();                                   // vtable+0x38
	void VTable0x3c(undefined4);                         // vtable+0x3c
	void VTable0x40();                                   // vtable+0x40
	undefined4 VTable0x4c(undefined4, undefined4);       // vtable+0x4c
	void VTable0x50(undefined4);                         // vtable+0x50
	void VTable0x54(undefined4);                         // vtable+0x54
	void VTable0x58();                                   // vtable+0x58
	void VTable0x5c();                                   // vtable+0x5c
	void VTable0x60();                                   // vtable+0x60
	void VTable0x64();                                   // vtable+0x64
	void VTable0x68();                                   // vtable+0x68
	void VTable0x6c();                                   // vtable+0x6c
	void VTable0x70();                                   // vtable+0x70
	void VTable0x74();                                   // vtable+0x74
	void VTable0x78();                                   // vtable+0x78
	void VTable0x7c();                                   // vtable+0x7c
	void VTable0x80();                                   // vtable+0x80
	void VTable0x84();                                   // vtable+0x84
	void VTable0x88(undefined4, undefined4, undefined4); // vtable+0x88
	void VTable0x8c(undefined4, undefined4, undefined4); // vtable+0x8c
	void VTable0x90();                                   // vtable+0x90
	void VTable0x94();                                   // vtable+0x94
	void VTable0x98(undefined4, undefined4, undefined4); // vtable+0x98
	void VTable0x9c(undefined4, undefined4, undefined4); // vtable+0x9c
	void VTable0xa8();                                   // vtable+0xa8
	void VTable0xac(undefined4, undefined4);             // vtable+0xac
	void VTable0xb0(undefined4, undefined4);             // vtable+0xb0
	void VTable0xb4();                                   // vtable+0xb4
	void VTable0xb8();                                   // vtable+0xb8
	void VTable0xbc();                                   // vtable+0xbc
	void VTable0xc0();                                   // vtable+0xc0
	void VTable0xc4();                                   // vtable+0xc4
	void VTable0xc8();                                   // vtable+0xc8
	void VTable0xcc();                                   // vtable+0xcc
	void VTable0xd0();                                   // vtable+0xd0
	void VTable0xd4();                                   // vtable+0xd4
	void VTable0xd8();                                   // vtable+0xd8
	void VTable0xdc();                                   // vtable+0xdc
	void VTable0xe0();                                   // vtable+0xe0
	void VTable0xe4();                                   // vtable+0xe4
	void VTable0xe8(undefined4);                         // vtable+0xe8
	void VTable0xec(undefined4);                         // vtable+0xec
	void VTable0xf0();                                   // vtable+0xf0
	void VTable0xf4();                                   // vtable+0xf4
	void VTable0xf8();                                   // vtable+0xf8
	void VTable0xfc();                                   // vtable+0xfc
	void VTable0x100();                                  // vtable+0x100
	void VTable0x104();                                  // vtable+0x104
	void VTable0x108();                                  // vtable+0x108
	void VTable0x10c();                                  // vtable+0x10c
	LegoBool32 VTable0x110() const;                      // vtable+0x110

	void FUN_10028ad0(GolNameTable* p_param);
	void FUN_10028ae0(GolNameTable* p_param);
	undefined4* FUN_004131a0(const LegoChar* p_name);

	// SYNTHETIC: GOLDP 0x10007960
	// BronzeFalcon0xc8770::`scalar deleting destructor'

private:
	GolCommonDrawState* m_drawState;       // 0x140
	undefined m_unk0x144[0xc8770 - 0x144]; // 0x144
};

#endif // BRONZEFALCON0XC8770_H
