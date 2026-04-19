#ifndef CERULEANKNIGHT0X20_H
#define CERULEANKNIGHT0X20_H

#include "ceruleansubject0x0c.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b2210
// SIZE 0x20
class CeruleanKnight0x20 : public CeruleanSubject0x0c {
public:
	CeruleanKnight0x20();
	~CeruleanKnight0x20() override;          // vtable+0x00
	void VTable0x08() override;              // vtable+0x08
	virtual void VTable0x0c();               // vtable+0x0c
	virtual void VTable0x10(undefined4) = 0; // vtable+0x10
	virtual void VTable0x14(undefined4) = 0; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x0046b070
	// CeruleanKnight0x20::`scalar deleting destructor'

protected:
	undefined m_unk0x0c;  // 0x0c
	undefined4 m_unk0x10; // 0x10
	undefined4 m_unk0x14; // 0x10
	undefined4 m_unk0x18; // 0x10
	undefined4 m_unk0x1c; // 0x10
};

#endif // CERULEANKNIGHT0X20_H
