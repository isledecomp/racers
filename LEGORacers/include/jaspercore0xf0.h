#ifndef JASPERCORE0XF0_H
#define JASPERCORE0XF0_H

#include "decomp.h"
#include "jasperauxinterface.h"
#include "types.h"

#include <dinput.h>

// VTABLE: LEGORACERS 0x004b0f00
// SIZE 0xf0
class JasperCore0xf0 {
public:
	JasperCore0xf0();
	virtual LegoS32 Reset();                 // vtable+0x00
	virtual ~JasperCore0xf0();               // vtable+0x04
	virtual LegoS32 Shutdown() = 0;          // vtable+0x08
	virtual LegoS32 Init() = 0;              // vtable+0x0c
	virtual LegoS32 VTable0x10(LegoS32) = 0; // vtable+0x10
	virtual LegoS32 VTable0x14() = 0;        // vtable+0x14
	virtual LegoS32 VTable0x18();            // vtable+0x18
	virtual LegoS32 VTable0x1c();            // vtable+0x1c
	virtual LegoS32 VTable0x20();            // vtable+0x20
	virtual void VTable0x24();               // vtable+0x24

	// SYNTHETIC: LEGORACERS 0x0044bf40
	// JasperCore0xf0::`scalar deleting destructor'

	JasperAuxInterface* GetUnk0xa0() { return m_unk0xa0; }

protected:
	undefined m_unk0x04[0x40];     // 0x04
	undefined4 m_unk0x44;          // 0x44
	undefined4 m_unk0x48;          // 0x48
	undefined m_unk0x4c[0x40];     // 0x4c
	undefined4 m_unk0x8c;          // 0x8c
	undefined4 m_unk0x90;          // 0x90
	undefined4 m_unk0x94;          // 0x94
	undefined4 m_unk0x98;          // 0x98
	undefined4 m_unk0x9c;          // 0x9c
	JasperAuxInterface* m_unk0xa0; // 0xa0

protected:
	undefined m_unk0xa4[0x40];        // 0xa4
	LPDIRECTINPUT m_directInput;      // 0xe4
	undefined m_unk0xe8[0xec - 0xe8]; // 0xe8
	undefined4 m_unk0xec;             // 0xec
};

#endif // JASPERCORE0XF0_H
