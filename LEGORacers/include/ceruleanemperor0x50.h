#ifndef CERULEANEMPEROR0X50_H
#define CERULEANEMPEROR0X50_H

#include "ceruleanknight0x20.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b27cc
// SIZE 0x50
class CeruleanEmperor0x50 : public CeruleanKnight0x20 {
public:
	CeruleanEmperor0x50();
	~CeruleanEmperor0x50() override;      // vtable+0x00
	void VTable0x08() override;           // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0046faa0
	// CeruleanEmperor0x50::`scalar deleting destructor'

protected:
	undefined4 m_unk0x20;   // 0x20
	undefined4 m_unk0x24;   // 0x24
	undefined4 m_unk0x28;   // 0x28
	undefined4 m_unk0x2c;   // 0x2c
	undefined4 m_unk0x30;   // 0x30
	undefined4 m_unk0x34;   // 0x34
	undefined4 m_unk0x38;   // 0x38
	undefined4 m_unk0x3c;   // 0x3c
	undefined4 m_unk0x40;   // 0x40
	undefined4 m_unk0x44;   // 0x44
	undefined4 m_unk0x48;   // 0x48
	undefined m_unk0x4c[4]; // 0x4c ?
};

#endif // CERULEANEMPEROR0X50_H
