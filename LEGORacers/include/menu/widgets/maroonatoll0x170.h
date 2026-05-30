#ifndef MAROONATOLL0X170_H
#define MAROONATOLL0X170_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/violetshoal0xc0.h"

// VTABLE: LEGORACERS 0x004b39d4
// SIZE 0x170
class MaroonAtoll0x170 : public VioletShoal0xc0 {
public:
	MaroonAtoll0x170();

	void Reset() override;                // vtable+0x00
	~MaroonAtoll0x170() override;         // vtable+0x04
	LegoBool32 VTable0x08() override;     // vtable+0x08
	void VTable0x50(undefined4) override; // vtable+0x50
	LegoS32 VTable0x54() override;        // vtable+0x54
	LegoS32 VTable0x58() override;        // vtable+0x58
	virtual void VTable0x60();            // vtable+0x60

	// SYNTHETIC: LEGORACERS 0x004839c0
	// MaroonAtoll0x170::`scalar deleting destructor'

protected:
	undefined4 m_unk0xc0;              // 0xc0
	undefined m_unk0xc4[0xcc - 0xc4];  // 0xc4
	undefined4 m_unk0xcc;              // 0xcc
	undefined m_unk0xd0[0x170 - 0xd0]; // 0xd0
};

#endif // MAROONATOLL0X170_H
