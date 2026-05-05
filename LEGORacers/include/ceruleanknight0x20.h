#ifndef CERULEANKNIGHT0X20_H
#define CERULEANKNIGHT0X20_H

#include "compat.h"
#include "decomp.h"
#include "golfileparser.h"
#include "golnametable.h"
#include "types.h"

class BronzeFalcon0xc8770;

// VTABLE: LEGORACERS 0x004b2210
// SIZE 0x20
class CeruleanKnight0x20 : public GolNameTable {
public:
	CeruleanKnight0x20();
	~CeruleanKnight0x20() override;          // vtable+0x00
	void Clear() override;                   // vtable+0x08
	virtual void VTable0x0c();               // vtable+0x0c
	virtual void VTable0x10(undefined4) = 0; // vtable+0x10
	virtual void VTable0x14(undefined4) = 0; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0046b070
	// CeruleanKnight0x20::`scalar deleting destructor'

protected:
	LegoBool32 FUN_0046b100();
	LegoS32 FUN_0046b130();
	LegoS32 FUN_0046b170();
	void FUN_0046b1d0(LegoS32* p_ints);
	void FUN_0046b210(LegoS8* p_ints);
	void FUN_0046b250();

	LegoBool m_unk0x0c;             // 0x0c
	GolFileParser* m_unk0x10;       // 0x10
	BronzeFalcon0xc8770* m_unk0x14; // 0x14
	undefined4 m_unk0x18;           // 0x18
	undefined4 m_unk0x1c;           // 0x1c
};

#endif // CERULEANKNIGHT0X20_H
