#ifndef OBSCUREVANTAGE0X58_H
#define OBSCUREVANTAGE0X58_H

#include "compat.h"
#include "coppercrest0x40.h"
#include "decomp.h"
#include "imaginaryinterface.h"
#include "onyxcircularbuffer0x1c.h"
#include "rectangle.h"
#include "silverdune0x30.h"
#include "types.h"

// VTABLE: LEGORACERS 0x004b29b4
// SIZE 0x58
class ObscureVantage0x58 {
public:
	ObscureVantage0x58();
	virtual void Reset();                                                                 // vtable+0x00
	virtual ~ObscureVantage0x58();                                                        // vtable+0x04
	virtual undefined4 VTable0x08();                                                      // vtable+0x08
	virtual void SetParent(ObscureVantage0x58*);                                          // vtable+0x0c
	virtual void VTable0x10(Rect*);                                                       // vtable+0x10
	virtual void VTable0x14(Rect*);                                                       // vtable+0x14
	virtual undefined4 VTable0x18(undefined4);                                            // vtable+0x18
	virtual undefined4 VTable0x1c(Rect*, Rect*);                                          // vtable+0x1c
	virtual undefined4 VTable0x20(CopperCrest0x40::Helper0x44*, undefined4, undefined4);  // vtable+0x20
	virtual undefined4 VTable0x24(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4); // vtable+0x24
	virtual undefined4 VTable0x28(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4); // vtable+0x28
	virtual undefined4 VTable0x2c(void*, undefined4, undefined4);                         // vtable+0x2c
	virtual undefined4 VTable0x30(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4); // vtable+0x30
	virtual undefined4 VTable0x34(OnyxCircularBuffer0x1c::Item*, undefined4, undefined4); // vtable+0x34
	virtual undefined4 VTable0x38(Rect*, Rect*);                                          // vtable+0x38
	virtual undefined4 VTable0x3c(undefined4);                                            // vtable+0x3c

	void RemoveFromParent();
	undefined4 FUN_00472c40(LegoS32, LegoS32);
	ObscureVantage0x58* FindRoot();
	ObscureVantage0x58* FUN_00472e60();
	Rect* GetGlobalRect();
	LegoBool32 ClipRect(Rect*, Rect*);
	Rect* FUN_00473160(Rect*);
	void FUN_004731b0(undefined4&, undefined4&);
	LegoBool GetUnk0x54() const { return m_unk0x54; }

	// SYNTHETIC: LEGORACERS 0x004729d0
	// ObscureVantage0x58::`scalar deleting destructor'

protected:
	ObscureVantage0x58* m_parent;      // 0x04
	ObscureVantage0x58* m_firstChild;  // 0x08
	ObscureVantage0x58* m_lastChild;   // 0x0c
	ObscureVantage0x58* m_prevSibling; // 0x10
	ObscureVantage0x58* m_nextSibling; // 0x14
	ObscureVantage0x58* m_unk0x18;     // 0x18
	undefined m_flags;                 // 0x1c
	undefined4 m_unk0x20;              // 0x20
	undefined4 m_unk0x24;              // 0x24
	ImaginaryInterface* m_unk0x28;     // 0x28
	undefined4 m_unk0x2c;              // 0x2c
	undefined2 m_unk0x30;              // 0x30
	Rect m_unk0x34;                    // 0x34
	LegoFloat m_unk0x44;               // 0x44
	LegoFloat m_unk0x48;               // 0x48
	LegoS32 m_unk0x4c;                 // 0x4c
	LegoS32 m_unk0x50;                 // 0x50
	undefined m_unk0x54;               // 0x54
};

#endif // OBSCUREVANTAGE0X58_H
