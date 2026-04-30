#ifndef PORCELAINVEIL0X50_H
#define PORCELAINVEIL0X50_H

#include "ceruleanemperor0x4c.h"
#include "compat.h"
#include "decomp.h"

// VTABLE: LEGORACERS 0x004b35b0
// SIZE 0x50
class PorcelainVeil0x50 : public CeruleanEmperor0x4c {
public:
	PorcelainVeil0x50();
	~PorcelainVeil0x50() override;        // vtable+0x00
	void Clear() override;                // vtable+0x08
	void VTable0x0c() override;           // vtable+0x0c
	void VTable0x10(undefined4) override; // vtable+0x10
	void VTable0x14(undefined4) override; // vtable+0x14

	// SYNTHETIC: LEGORACERS 0x004805a0
	// PorcelainVeil0x50::`scalar deleting destructor'

private:
	undefined* m_unk0x4c; // 0x4c
};

#endif // PORCELAINVEIL0X50_H
