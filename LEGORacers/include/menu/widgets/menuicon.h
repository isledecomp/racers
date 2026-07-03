#ifndef MENUICON_H
#define MENUICON_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuwidget.h"
#include "render/rectangle.h"
#include "types.h"

class GolD3DRenderDevice;
class GolExport;
class SoundGroupBinding;

// VTABLE: LEGORACERS 0x004b2944
// SIZE 0x1a8
class MenuIcon : public MenuWidget {
public:
	// Visual-state index into the per-state image/rect/color arrays. Grounded in
	// CARBUILD.MIB glyph image order [G,G,U,A,S,A]: G=disabled, U=normal/up,
	// A=pressed/active, S=focused/selected. Computed in RefreshVisualState as
	// (enabled ? 2 : 0) + (focused ? +2) + (highlighted ? +1).
	enum VisualState {
		c_stateDisabled = 0,
		c_stateDisabledPressed = 1,
		c_stateNormal = 2,
		c_statePressed = 3,
		c_stateFocused = 4,
		c_stateFocusedPressed = 5,
	};

	// SIZE 0x04
	class SoundIdPair {
	public:
		LegoU16 m_first;  // 0x00
		LegoU16 m_second; // 0x02
	};

	// SIZE 0x84
	class CreateParams : public MenuWidget::CreateParams {
	public:
		LegoBool m_startEnabled;                 // 0x38
		undefined m_unk0x39[0x3c - 0x39];        // 0x39
		undefined4 m_unk0x3c;                    // 0x3c
		undefined2 m_helpStringId;               // 0x40
		undefined m_unk0x42[0x44 - 0x42];        // 0x42
		MenuIcon* m_parent;                      // 0x44
		undefined2 m_parentId;                   // 0x48
		LegoU8 m_resolveParentByName;            // 0x4a
		undefined m_unk0x4b[0x52 - 0x4b];        // 0x4b
		VisualStateColor m_iconStateColors[6];   // 0x52
		undefined2 m_soundIds[5];                // 0x6a
		LegoBool32 m_attachToParent;             // 0x74
		LegoBool32 m_hasStateColors;             // 0x78
		LegoBool32 m_hasSoundIds;                // 0x7c
		MenuScreenInterface* m_iconEventHandler; // 0x80
	};

	// SIZE 0x90
	class CreateState {
	public:
		VisualStateColor m_iconStateColors[6]; // 0x00
		undefined2 m_iconSoundIds[5];          // 0x18
		undefined2 m_unk0x22;                  // 0x22
		Rect m_stateRects[6];                  // 0x24
		LegoU32 m_transitionDurationMs;        // 0x84
		LegoBool32 m_hasStateColors;           // 0x88
		LegoBool32 m_hasSoundIds;              // 0x8c
	};

	enum {
		c_flagEnabled = 1 << 0,  // Enable sets / Disable clears
		c_flagSelected = 1 << 1, // SetSelected sets / ClearSelected clears
		c_flagFocused = 1 << 2,  // Focus sets / Unfocus clears
	};

	MenuIcon();
	void Reset() override;                                                           // vtable+0x00
	~MenuIcon() override;                                                            // vtable+0x04
	LegoBool32 Destroy() override;                                                   // vtable+0x08
	void SetRect(Rect*) override;                                                    // vtable+0x10
	MenuWidget* OnCursorEvent(void*, undefined4, undefined4) override;               // vtable+0x2c
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x34
	MenuWidget* DrawSelf(Rect*, Rect*) override;                                     // vtable+0x38
	undefined4 OnEvent(undefined4) override;                                         // vtable+0x3c
	virtual void SetIconEventHandler(MenuScreenInterface*);
	virtual void Enable(undefined4);
	virtual void Disable(undefined4);
	virtual void Select(undefined4);
	virtual void Deselect(undefined4);
	virtual void Focus(undefined4);
	virtual void Unfocus(undefined4);
	virtual LegoBool32 IsEnabled();
	virtual MenuIcon* SelectNext();
	virtual MenuIcon* SelectPrevious();
	virtual MenuIcon* SelectFirst();
	virtual MenuIcon* SelectLast();

	LegoBool32 Create(CreateParams* p_createParams, const CreateState* p_createState);
	void AttachToParent(MenuIcon* p_parent);
	void DetachFromParent();
	MenuIcon* GetFirstChild() { return m_firstChild; }
	LegoU8 GetStateFlags() const { return m_stateFlags; }
	undefined2 GetHelpStringId() const { return m_helpStringId; }
	MenuIcon* FindSelectedLeaf();

	// SYNTHETIC: LEGORACERS 0x00471c80
	// MenuIcon::`scalar deleting destructor'

protected:
	void InitializeFromParams(CreateParams* p_createParams, const CreateState* p_createState);
	MenuIcon* FindRoot();
	void SetSelected(undefined4 p_flags);
	void ClearSelected(undefined4 p_flags);
	void RefreshVisualState();
	void BeginRectTransition();

	MenuIcon* m_parent;                     // 0x058
	MenuIcon* m_prevSibling;                // 0x05c
	MenuIcon* m_nextSibling;                // 0x060
	MenuIcon* m_firstChild;                 // 0x064
	MenuIcon* m_lastChild;                  // 0x068
	Rect m_stateRects[6];                   // 0x06c
	Rect m_stateTargetRects[6];             // 0x0cc
	LegoU8 m_stateFlags;                    // 0x12c
	LegoBool m_attached;                    // 0x12d
	undefined m_unk0x12e[0x130 - 0x12e];    // 0x12e
	LegoS32 m_transitionDurationMs;         // 0x130
	LegoS32 m_transitionRemainingMs;        // 0x134
	LegoFloat m_rectDeltaTop;               // 0x138
	LegoFloat m_rectDeltaBottom;            // 0x13c
	LegoFloat m_rectDeltaLeft;              // 0x140
	LegoFloat m_rectDeltaRight;             // 0x144
	LegoFloat m_rectTopF;                   // 0x148
	LegoFloat m_rectBottomF;                // 0x14c
	LegoFloat m_rectLeftF;                  // 0x150
	LegoFloat m_rectRightF;                 // 0x154
	undefined4 m_unk0x158[4];               // 0x158
	undefined2 m_helpStringId;              // 0x168
	SoundGroupBinding* m_soundGroupBinding; // 0x16c
	MenuScreenInterface* m_eventHandler;    // 0x170
	VisualStateColor m_stateColors[6];      // 0x174
	LegoU16 m_soundIds[5];                  // 0x18c
	undefined m_unk0x196[0x198 - 0x196];    // 0x196
	MenuIcon* m_selectedChild;              // 0x198
	LegoU8 m_visualStateIndex;              // 0x19c
	undefined m_unk0x19d[0x1a0 - 0x19d];    // 0x19d
	LegoU32 m_activeKeyCode;                // 0x1a0
	undefined4 m_unk0x1a4;                  // 0x1a4
};

#endif // MENUICON_H
