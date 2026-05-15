#ifndef OBSCUREVANTAGE0X58_H
#define OBSCUREVANTAGE0X58_H

#include "color.h"
#include "compat.h"
#include "coppercrest0x40.h"
#include "decomp.h"
#include "imaginaryinterface.h"
#include "onyxcircularbuffer0x1c.h"
#include "rectangle.h"
#include "silverdune0x30.h"
#include "types.h"
#include "visualstate0x4.h"

class BronzeFalcon0xc8770;
class GolFontBase0x40;
class GolExport;
class GolString;
class SoundGroupBinding;

// VTABLE: LEGORACERS 0x004b29b4
// SIZE 0x58
class ObscureVantage0x58 {
public:
	// SIZE 0x30
	class CreateParams0x30 {
	public:
		GolExport* m_golExport;                 // 0x00
		BronzeFalcon0xc8770* m_renderer;        // 0x04
		SoundGroupBinding* m_soundGroupBinding; // 0x08
		ImaginaryInterface* m_eventHandler;     // 0x0c
		Rect m_rect;                            // 0x10
		undefined2 m_unk0x20;                   // 0x20
		VisualState0x4 m_unk0x22;               // 0x22
		undefined2 m_unk0x26;                   // 0x26
		ObscureVantage0x58* m_parent;           // 0x28
		undefined4 m_flags;                     // 0x2c
	};

	ObscureVantage0x58();
	virtual void Reset();                                                                 // vtable+0x00
	virtual ~ObscureVantage0x58();                                                        // vtable+0x04
	virtual undefined4 VTable0x08();                                                      // vtable+0x08
	virtual void SetParent(ObscureVantage0x58*);                                          // vtable+0x0c
	virtual void VTable0x10(Rect*);                                                       // vtable+0x10
	virtual void VTable0x14(VisualState0x4*);                                             // vtable+0x14
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
	Rect* GetRect() { return &m_unk0x34; }
	LegoBool32 ClipRect(Rect*, Rect*);
	Rect* FUN_00472c80(Rect*, Rect*);
	Rect* FUN_00472d00(GolFontBase0x40*, GolString*, Rect*, Rect*, LegoS32);
	undefined2 FUN_00472da0(Rect*, Rect*, GolFontBase0x40*, GolString*, LegoS32, LegoS32);
	Rect* FUN_00473160(Rect*);
	void FUN_004731b0(undefined4&, undefined4&);
	void SetEventHandler(ImaginaryInterface* p_eventHandler) { m_unk0x28 = p_eventHandler; }
	LegoU8 GetFlags() const { return m_flags; }
	LegoBool GetUnk0x54() const { return m_unk0x54; }
	void ClearFlags(LegoU8 p_flags) { m_flags &= ~p_flags; }
	void SetFlags(LegoU8 p_flags) { m_flags |= p_flags; }

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
	GolExport* m_golExport;            // 0x20
	BronzeFalcon0xc8770* m_renderer;   // 0x24
	ImaginaryInterface* m_unk0x28;     // 0x28
	union {
		ColorRGBA m_color;     // 0x2c
		LegoU32 m_colorPacked; // 0x2c
	};
	undefined2 m_unk0x30; // 0x30
	Rect m_unk0x34;       // 0x34
	LegoFloat m_unk0x44;  // 0x44
	LegoFloat m_unk0x48;  // 0x48
	LegoS32 m_unk0x4c;    // 0x4c
	LegoS32 m_unk0x50;    // 0x50
	undefined m_unk0x54;  // 0x54

protected:
	LegoBool32 FUN_00472a60(CreateParams0x30* p_createParams);
	void FUN_00472bc0();
	void FUN_00472c10();
};

#endif // OBSCUREVANTAGE0X58_H
