#ifndef MENUTEXTBUTTON_H
#define MENUTEXTBUTTON_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuicon.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextlabel.h"

class GolFont;
class GolString;
class GolStringTable;
class GolImage;

// VTABLE: LEGORACERS 0x004b38b0
// SIZE 0x2f0
class MenuTextButton : public MenuIcon {
public:
	// SIZE 0xe0
	class CreateParams : public MenuIcon::CreateParams {
	public:
		GolFont* m_stateFonts[6];          // 0x84
		GolImage* m_stateImages[6];        // 0x9c
		VisualStateColor m_stateColors[6]; // 0xb4
		GolStringTable* m_stringTable;     // 0xcc
		undefined4 m_unk0xd0;              // 0xd0
		undefined2 m_stringId;             // 0xd4
		undefined2 m_unk0xd6;              // 0xd6
		LegoU32 m_maxTextWidth;            // 0xd8
		LegoBool32 m_hasMaxTextWidth;      // 0xdc
	};

	MenuTextButton();
	void Reset() override;                                                         // vtable+0x00
	~MenuTextButton() override;                                                    // vtable+0x04
	LegoBool32 Destroy() override;                                                 // vtable+0x08
	void SetRect(Rect*) override;                                                  // vtable+0x10
	MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	MenuWidget* DrawSelf(Rect*, Rect*) override;                                   // vtable+0x38
	void SetIconEventHandler(MenuScreenInterface*) override;                       // vtable+0x40
	void SetTextByIndex(undefined4);
	void SetText(GolString* p_string);
	LegoBool32 Create(CreateParams* p_createParams, MenuStyleTable::TextButtonStyle* p_styleEntry);

	// SYNTHETIC: LEGORACERS 0x00482400
	// MenuTextButton::`scalar deleting destructor'

private:
	LegoBool32 CreateImage(CreateParams* p_createParams);
	LegoBool32 CreateLabel(CreateParams* p_createParams, MenuStyleTable::TextButtonStyle* p_styleEntry);

	MenuStyleTable::TextButtonStyle* m_styleEntry; // 0x1a8
	MenuStyleTable::TextStyle m_textStyle;         // 0x1ac
	GolFont* m_stateFonts[6];                      // 0x1c0
	GolImage* m_stateImages[6];                    // 0x1d8
	VisualStateColor m_stateImageColors[6];        // 0x1f0
	MenuImage m_image;                             // 0x208
	MenuTextLabel m_label;                         // 0x264
	LegoS32 m_maxTextWidth;                        // 0x2dc
	undefined4 m_unk0x2e0[4];                      // 0x2e0
};

#endif // MENUTEXTBUTTON_H
