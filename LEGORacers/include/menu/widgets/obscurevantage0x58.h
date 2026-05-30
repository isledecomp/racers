#ifndef OBSCUREVANTAGE0X58_H
#define OBSCUREVANTAGE0X58_H

#include "compat.h"
#include "decomp.h"
#include "golname.h"
#include "input/inputeventqueue.h"
#include "menu/screens/imaginaryinterface.h"
#include "render/rectangle.h"
#include "surface/color.h"
#include "surface/silverdune0x30.h"
#include "text/coppercrest0x40.h"
#include "types.h"
#include "util/visualstate0x4.h"

class GolD3DRenderDevice;
class GolFontBase0x40;
class GolExport;
class GolString;
class ObscureVantage0x58;
class SoundGroupBinding;
class UtopianPan0xa4;

typedef LegoBool32 ObscureVantageEventResult;

union ObscureVantageEventResultValue {
	ObscureVantage0x58* m_widget;
	ObscureVantageEventResult m_result;
};

// VTABLE: LEGORACERS 0x004b29b4
// SIZE 0x58
class ObscureVantage0x58 {
public:
	// SIZE 0x38
	class CreateParams0x38 {
	public:
		GolExport* m_golExport;                 // 0x00
		GolD3DRenderDevice* m_renderer;         // 0x04
		SoundGroupBinding* m_soundGroupBinding; // 0x08
		ImaginaryInterface* m_eventHandler;     // 0x0c
		Rect m_rect;                            // 0x10
		undefined2 m_unk0x20;                   // 0x20
		VisualState0x4 m_unk0x22;               // 0x22
		undefined2 m_unk0x26;                   // 0x26
		ObscureVantage0x58* m_parent;           // 0x28
		LegoU8 m_flags;                         // 0x2c
		GolName m_name;                         // 0x2d
		undefined m_unk0x35[0x38 - 0x35];       // 0x35
	};

	ObscureVantage0x58();
	virtual void Reset();                                                                          // vtable+0x00
	virtual ~ObscureVantage0x58();                                                                 // vtable+0x04
	virtual LegoBool32 VTable0x08();                                                               // vtable+0x08
	virtual void SetParent(ObscureVantage0x58*);                                                   // vtable+0x0c
	virtual void VTable0x10(Rect*);                                                                // vtable+0x10
	virtual void VTable0x14(VisualState0x4*);                                                      // vtable+0x14
	virtual LegoBool32 VTable0x18(undefined4);                                                     // vtable+0x18
	virtual undefined4 VTable0x1c(Rect*, Rect*);                                                   // vtable+0x1c
	virtual LegoBool32 VTable0x20(CopperCrest0x40::Helper0x44*, undefined4, undefined4);           // vtable+0x20
	virtual ObscureVantageEventResult VTable0x24(InputEventQueue::Event*, undefined4, undefined4); // vtable+0x24
	virtual ObscureVantageEventResult VTable0x28(InputEventQueue::Event*, undefined4, undefined4); // vtable+0x28
	virtual ObscureVantage0x58* VTable0x2c(void*, undefined4, undefined4);                         // vtable+0x2c
	virtual ObscureVantage0x58* VTable0x30(InputEventQueue::Event*, undefined4, undefined4);       // vtable+0x30
	virtual ObscureVantage0x58* VTable0x34(InputEventQueue::Event*, undefined4, undefined4);       // vtable+0x34
	virtual ObscureVantage0x58* VTable0x38(Rect*, Rect*);                                          // vtable+0x38
	virtual undefined4 VTable0x3c(undefined4);                                                     // vtable+0x3c

	void RemoveFromParent();
	undefined4 FUN_00472c40(LegoS32, LegoS32);
	ObscureVantage0x58* FindRoot();
	ObscureVantage0x58* FUN_00472e60();
	ObscureVantage0x58* FUN_00472ef0(LegoS32 p_unk0x04);
	ObscureVantage0x58* FUN_00472f10(undefined2);
	ObscureVantage0x58* GetParent() { return m_parent; }
	ObscureVantage0x58* GetFirstChild() { return m_firstChild; }
	ObscureVantage0x58* GetNextSibling() { return m_nextSibling; }
	ObscureVantage0x58* GetPrevSibling() { return m_prevSibling; }
	Rect* GetGlobalRect();
	Rect* GetRect() { return &m_unk0x34; }
	LegoBool32 ClipRect(Rect*, Rect*);
	Rect* FUN_00472c80(Rect*, Rect*);
	Rect* FUN_00472d00(GolFontBase0x40*, GolString*, Rect*, Rect*, LegoS32);
	void FUN_00472d70(Rect*, Rect*, UtopianPan0xa4*);
	undefined2 FUN_00472da0(Rect*, Rect*, GolFontBase0x40*, GolString*, LegoS32, LegoS32);
	Rect* FUN_00473160(Rect*);
	LegoBool32 FUN_00473a20(Rect*, LegoS32, LegoS32);
	void FUN_004731b0(undefined4&, undefined4&);
	void FUN_00472fd0(Rect*, Rect*);
	void FUN_00473050(Rect*, Rect*);
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
	GolD3DRenderDevice* m_renderer;    // 0x24
	ImaginaryInterface* m_unk0x28;     // 0x28
	union {
		ColorRGBA m_color;            // 0x2c
		LegoU32 m_colorPacked;        // 0x2c
		VisualState0x4 m_visualState; // 0x2c
	};
	undefined2 m_unk0x30; // 0x30
	Rect m_unk0x34;       // 0x34
	LegoFloat m_unk0x44;  // 0x44
	LegoFloat m_unk0x48;  // 0x48
	LegoS32 m_unk0x4c;    // 0x4c
	LegoS32 m_unk0x50;    // 0x50
	undefined m_unk0x54;  // 0x54

protected:
	LegoBool32 FUN_00472a60(CreateParams0x38* p_createParams);
	void FUN_00472bc0();
	void FUN_00472c10();
};

#endif // OBSCUREVANTAGE0X58_H
