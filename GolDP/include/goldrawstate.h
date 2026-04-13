#ifndef GOLDP_GOLSTATE_H
#define GOLDP_GOLSTATE_H

#include "compat.h"
#include "decomp.h"

#include <windows.h>

// VTABLE: GOLDP 0x10056d6c
// SIZE 0x18
class GolDrawState {
protected:
	GolDrawState();

public:
	virtual int VTable0x00() = 0;                                  // vtable+0x00
	virtual ~GolDrawState() {}                                     // vtable+04
	virtual void VTable0x08(HWND p_hWnd) = 0;                      // vtable+08
	virtual void VTable0x0c(undefined4, undefined4);               // vtable+0c
	virtual undefined4 VTable0x10();                               // vtable+10
	virtual undefined4 VTable0x14(undefined4);                     // vtable+14
	virtual undefined4 VTable0x18(undefined4);                     // vtable+18
	virtual undefined4 VTable0x1c(undefined4);                     // vtable+1c
	virtual undefined4 VTable0x20(undefined4, undefined4);         // vtable+20
	virtual undefined4 VTable0x24(undefined4, undefined4);         // vtable+24
	virtual undefined4 VTable0x28(undefined4, undefined4);         // vtable+28
	virtual void VTable0x2c(undefined4, undefined4*, undefined4*); // vtable+2c
	virtual void VTable0x30(undefined4, undefined4*);              // vtable+30
	virtual void VTable0x34(undefined4, undefined4, undefined4*);  // vtable+34
	virtual undefined4 VTable0x38();                               // vtable+38
	virtual void VTable0x3c();                                     // vtable+3c
	virtual void VTable0x40();                                     // vtable+40
	virtual undefined4 VTable0x44(
		undefined4 p_width,
		undefined4 p_height,
		undefined4 p_bpp,
		undefined4 p_flags
	);                                                                       // vtable+44
	virtual void VTable0x48();                                               // vtable+48
	virtual void VTable0x4c();                                               // vtable+4c
	virtual void VTable0x50();                                               // vtable+50
	virtual void VTable0x54(undefined4, undefined4, undefined4, undefined4); // vtable+54

	// SYNTHETIC: GOLDP 0x1001d590
	// GolDrawState::`scalar deleting destructor'

private:
	undefined4 m_width;   // 0x04
	undefined4 m_height;  // 0x08
	undefined4 m_bpp;     // 0x0c
	undefined4 m_flags;   // 0x10
	undefined4 m_unk0x14; // 0x14
};

#endif // GOLDP_GOLSTATE_H
