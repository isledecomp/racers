#ifndef GOLDP_GOLSTATE_H
#define GOLDP_GOLSTATE_H

#include "azureridge0x38.h"
#include "compat.h"
#include "decomp.h"
#include "types.h"

#include <windows.h>

// VTABLE: GOLDP 0x10056d6c
// SIZE 0x18
class GolDrawState {
protected:
	GolDrawState();

public:
	enum {
		c_flagBit0 = 1 << 0,
		c_flagBit1 = 1 << 1,
		c_flagBit3 = 1 << 3,
		c_flagBit9 = 1 << 9,
		c_flagBit10 = 1 << 10,
		c_flagBit11 = 1 << 11,
		c_flagBit12 = 1 << 12,
		c_flagBit13 = 1 << 13,
		c_flagBit14 = 1 << 14,
		c_flagBit15 = 1 << 15,
		c_flagBit16 = 1 << 16,
		c_flagBit17 = 1 << 17,
		c_flagBit18 = 1 << 18,
		c_flagBit19 = 1 << 19,
	};

	virtual LegoS32 VTable0x00() = 0;                                                         // vtable+0x00
	virtual ~GolDrawState() {}                                                                // vtable+04
	virtual void VTable0x08(HWND p_hWnd) = 0;                                                 // vtable+08
	virtual void VTable0x0c(const char* p_driverName, const char* p_deviceName);              // vtable+0c
	virtual LegoU32 VTable0x10();                                                             // vtable+10
	virtual const LegoChar* VTable0x14(LegoU32 p_index);                                      // vtable+14
	virtual const LegoChar* VTable0x18(LegoU32 p_index);                                      // vtable+18
	virtual LegoU32 VTable0x1c(LegoU32 p_index);                                              // vtable+1c
	virtual const LegoChar* VTable0x20(LegoU32 p_driverIndex, LegoU32 p_deviceIndex);         // vtable+20
	virtual const LegoChar* VTable0x24(LegoU32 p_driverIndex, LegoU32 p_deviceIndex);         // vtable+24
	virtual undefined4 VTable0x28(undefined4, undefined4);                                    // vtable+28
	virtual void VTable0x2c(LegoU32 p_flags, LegoU32* p_driverIndex, LegoU32* p_deviceIndex); // vtable+2c
	virtual void VTable0x30(LegoU32 p_driverIndex, GUID* p_guid);                             // vtable+30
	virtual void VTable0x34(LegoU32 p_driverIndex, LegoU32 p_deviceIndex, GUID* p_guid);      // vtable+34
	virtual GUID* VTable0x38() const;                                                         // vtable+38
	virtual void VTable0x3c();                                                                // vtable+3c
	virtual void VTable0x40();                                                                // vtable+40
	virtual LegoS32 VTable0x44(LegoU32 p_width, LegoU32 p_height, LegoU32 p_bpp,
							   LegoU32 p_flags);                             // vtable+44
	virtual void VTable0x48();                                               // vtable+48
	virtual void VTable0x4c();                                               // vtable+4c
	virtual void VTable0x50();                                               // vtable+50
	virtual void VTable0x54(undefined4, undefined4, undefined4, undefined4); // vtable+54

	// SYNTHETIC: GOLDP 0x1001d590
	// GolDrawState::`scalar deleting destructor'

protected:
	undefined4 m_width;        // 0x04
	undefined4 m_height;       // 0x08
	undefined4 m_bpp;          // 0x0c
	LegoU32 m_flags;           // 0x10
	AzureRidge0x38* m_unk0x14; // 0x14
};

#endif // GOLDP_GOLSTATE_H
