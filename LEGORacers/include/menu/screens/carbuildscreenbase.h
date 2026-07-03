#ifndef CARBUILDSCREENBASE_H
#define CARBUILDSCREENBASE_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuicon.h"
#include "render/rectangle.h"

class GolFont;
class GolString;
class MenuWidget;

// VTABLE: LEGORACERS 0x004b2dc0
// SIZE 0x3b4
class CarBuildScreenBase : public MenuGameScreen {
public:
	// SIZE 0x40
	struct EventItem {
		undefined m_unk0x00[0x30]; // 0x00
		Rect m_rect;               // 0x30
	};

	// FUNCTION: LEGORACERS 0x00476e80
	// CarBuildScreenBase::~CarBuildScreenBase

	undefined4 OnWidgetKeyUp(MenuWidget*, void*, undefined4, undefined4) override;                   // vtable+0x14
	LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x1c
	void Reset() override;                                                                           // vtable+0x54
	LegoBool32 Update(undefined4) override;                                                          // vtable+0x78
	LegoBool32 Draw(Rect*, Rect*) override;                                                          // vtable+0x7c
	virtual GolString* GetHelpString(undefined4) = 0;                                                // vtable+0x98
	virtual GolFont* GetHelpFont(undefined4) = 0;                                                    // vtable+0x9c
	virtual void GetTooltipLayout(LegoS32*, LegoS32*, LegoS32*, LegoS32*) = 0;                       // vtable+0xa0

	// SYNTHETIC: LEGORACERS 0x00476ed0
	// CarBuildScreenBase::`scalar deleting destructor'

protected:
	void ResetTooltip();
	void ShowTooltip(MenuIcon* p_icon);
	void HideTooltip();
	void SuppressTooltip();

	LegoS32 m_hoverMs;            // 0x368
	LegoS32 m_tooltipMs;          // 0x36c
	LegoS32 m_quickShowMs;        // 0x370
	MenuIcon* m_hoverIcon;        // 0x374
	MenuIcon* m_tooltipIcon;      // 0x378
	LegoU8 m_wasVisible;          // 0x37c
	LegoU8 m_layoutDirty;         // 0x37d
	LegoU16 m_tooltipStringId;    // 0x37e
	Rect m_tooltipRect;           // 0x380
	LegoS32 m_tooltipX;           // 0x390
	LegoS32 m_tooltipY;           // 0x394
	LegoS32 m_tooltipWrapWidth;   // 0x398
	LegoS32 m_tooltipLineSpacing; // 0x39c
	GolString* m_tooltipString;   // 0x3a0
	GolFont* m_tooltipFont;       // 0x3a4
	GolString m_tooltipText;      // 0x3a8
};

#endif // CARBUILDSCREENBASE_H
