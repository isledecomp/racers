#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include "compat.h"
#include "decomp.h"
#include "golname.h"
#include "golsurface.h"
#include "input/inputeventqueue.h"
#include "menu/menuinputdispatcher.h"
#include "menu/screens/menuscreeninterface.h"
#include "menu/widgets/visualstatecolor.h"
#include "render/rectangle.h"
#include "surface/color.h"
#include "types.h"

class GolD3DRenderDevice;
class GolFontBase;
class GolExport;
class GolString;
class SoundGroupBinding;
class GolImage;

// VTABLE: LEGORACERS 0x004b29b4
// SIZE 0x58
class MenuWidget {
public:
	// SIZE 0x38
	class CreateParams {
	public:
		GolExport* m_golExport;                 // 0x00
		GolD3DRenderDevice* m_renderer;         // 0x04
		SoundGroupBinding* m_soundGroupBinding; // 0x08
		MenuScreenInterface* m_eventHandler;    // 0x0c
		Rect m_rect;                            // 0x10
		undefined2 m_id;                        // 0x20
		VisualStateColor m_color;               // 0x22
		undefined2 m_parentId;                  // 0x26
		MenuWidget* m_parent;                   // 0x28
		LegoU8 m_flags;                         // 0x2c
		GolName m_name;                         // 0x2d
		undefined m_unk0x35[0x38 - 0x35];       // 0x35
	};

	MenuWidget();
	virtual void Reset();                                                                         // vtable+0x00
	virtual ~MenuWidget();                                                                        // vtable+0x04
	virtual LegoBool32 Destroy();                                                                 // vtable+0x08
	virtual void SetParent(MenuWidget*);                                                          // vtable+0x0c
	virtual void SetRect(Rect*);                                                                  // vtable+0x10
	virtual void SetColor(VisualStateColor*);                                                     // vtable+0x14
	virtual LegoBool32 BroadcastEvent(undefined4);                                                // vtable+0x18
	virtual undefined4 Draw(Rect*, Rect*);                                                        // vtable+0x1c
	virtual LegoBool32 DispatchCursorEvent(MenuInputDispatcher::Cursor*, undefined4, undefined4); // vtable+0x20
	virtual LegoBool32 DispatchKeyDown(InputEventQueue::Event*, undefined4, undefined4);          // vtable+0x24
	virtual LegoBool32 DispatchKeyUp(InputEventQueue::Event*, undefined4, undefined4);            // vtable+0x28
	virtual MenuWidget* OnCursorEvent(void*, undefined4, undefined4);                             // vtable+0x2c
	virtual MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4);               // vtable+0x30
	virtual MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4);                 // vtable+0x34
	virtual MenuWidget* DrawSelf(Rect*, Rect*);                                                   // vtable+0x38
	virtual undefined4 OnEvent(undefined4);                                                       // vtable+0x3c

	void RemoveFromParent();
	undefined4 HitTest(LegoS32, LegoS32);
	MenuWidget* FindRoot();
	MenuWidget* FindFocusedLeaf();
	void SetFocus();
	MenuWidget* GetChildByIndex(LegoS32 p_index);
	MenuWidget* FindChildById(undefined2);
	MenuWidget* GetParent() { return m_parent; }
	MenuWidget* GetFirstChild() { return m_firstChild; }
	MenuWidget* GetNextSibling() { return m_nextSibling; }
	MenuWidget* GetPrevSibling() { return m_prevSibling; }
	Rect* GetGlobalRect();
	Rect* GetRect() { return &m_rect; }
	LegoBool32 ClipRect(Rect*, Rect*);
	void CenterRectIn(const Rect*, Rect*) const;
	void MeasureText(GolFontBase*, GolString*, Rect*, Rect*, LegoS32);
	void DrawImage(Rect*, Rect*, GolImage*);
	void DrawString(Rect*, Rect*, GolFontBase*, GolString*, LegoS32 p_wrapWidth, LegoS32 p_centered);
	Rect* TranslateRectByOffset(Rect*);
	LegoBool32 PointInRect(Rect*, LegoS32, LegoS32);
	void ScreenToLocal(undefined4&, undefined4&);
	void ComputeScale(Rect*, Rect*);
	void ScaleRect(Rect*, Rect*);
	void SetEventHandler(MenuScreenInterface* p_eventHandler) { m_notifyHandler = p_eventHandler; }
	LegoU8 GetFlags() const { return m_flags; }
	undefined2 GetId() const { return m_id; }
	LegoBool GetAnimFlags() const { return m_animFlags; }
	void ClearFlags(LegoU8 p_flags) { m_flags &= ~p_flags; }
	void SetFlags(LegoU8 p_flags) { m_flags |= p_flags; }
	void ClearFocus();

	// SYNTHETIC: LEGORACERS 0x004729d0
	// MenuWidget::`scalar deleting destructor'

protected:
	MenuWidget* m_parent;                 // 0x04
	MenuWidget* m_firstChild;             // 0x08
	MenuWidget* m_lastChild;              // 0x0c
	MenuWidget* m_prevSibling;            // 0x10
	MenuWidget* m_nextSibling;            // 0x14
	MenuWidget* m_focusedChild;           // 0x18
	LegoU8 m_flags;                       // 0x1c
	GolExport* m_golExport;               // 0x20
	GolD3DRenderDevice* m_renderer;       // 0x24
	MenuScreenInterface* m_notifyHandler; // 0x28
	union {
		ColorRGBA m_color;              // 0x2c
		LegoU32 m_colorPacked;          // 0x2c
		VisualStateColor m_visualState; // 0x2c
	};
	undefined2 m_id;       // 0x30
	Rect m_rect;           // 0x34
	LegoFloat m_scaleX;    // 0x44
	LegoFloat m_scaleY;    // 0x48
	LegoS32 m_offsetX;     // 0x4c
	LegoS32 m_offsetY;     // 0x50
	undefined m_animFlags; // 0x54

protected:
	LegoBool32 CreateWidget(CreateParams* p_createParams);
};

#endif // MENUWIDGET_H
