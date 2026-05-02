#ifndef CMBMODELPART0X34_H
#define CMBMODELPART0X34_H

#include "cmbmodelpartdata0x18.h"
#include "decomp.h"
#include "golnametable.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004af224
// SIZE 0x34
class CmbModelPart0x34 : public GolNameTable {
public:
	CmbModelPart0x34();
	~CmbModelPart0x34() override; // vtable+0x00
	void Clear() override;        // vtable+0x08

	// SYNTHETIC: LEGORACERS 0x0041e1b0
	// CmbModelPart0x34::`vector deleting destructor'

private:
	CmbModelPartData0x18 m_data; // 0x0c
	undefined4* m_unk0x24;       // 0x24
	LegoU32 m_unk0x28;           // 0x28
	undefined4* m_unk0x2c;       // 0x2c
	LegoU32 m_unk0x30;           // 0x30
};

#endif // CMBMODELPART0X34_H
