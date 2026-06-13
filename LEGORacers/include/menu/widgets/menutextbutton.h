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
class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b38b0
// SIZE 0x2f0
class MenuTextButton : public MenuIcon {
public:
	// SIZE 0xe0
	class CreateParams : public MenuIcon::CreateParams {
	public:
		GolFont* m_unk0x84[6];         // 0x84
		UtopianPan0xa4* m_unk0x9c[6];  // 0x9c
		VisualStateColor m_unk0xb4[6]; // 0xb4
		GolStringTable* m_unk0xcc;     // 0xcc
		undefined4 m_unk0xd0;          // 0xd0
		undefined2 m_unk0xd4;          // 0xd4
		undefined2 m_unk0xd6;          // 0xd6
		undefined4 m_unk0xd8;          // 0xd8
		undefined4 m_unk0xdc;          // 0xdc
	};

	MenuTextButton();
	void Reset() override;                                                            // vtable+0x00
	~MenuTextButton() override;                                                       // vtable+0x04
	LegoBool32 VTable0x08() override;                                                 // vtable+0x08
	void VTable0x10(Rect*) override;                                                  // vtable+0x10
	MenuWidget* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	MenuWidget* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
	void VTable0x40(MenuScreenInterface*) override;                                   // vtable+0x40
	void FUN_00482790(undefined4);
	void FUN_00482810(GolString* p_string);
	LegoBool32 FUN_004826c0(CreateParams* p_createParams, MenuStyleTable::TextButtonStyle* p_styleEntry);

	// SYNTHETIC: LEGORACERS 0x00482400
	// MenuTextButton::`scalar deleting destructor'

private:
	LegoBool32 FUN_004824d0(CreateParams* p_createParams);
	LegoBool32 FUN_00482540(CreateParams* p_createParams, MenuStyleTable::TextButtonStyle* p_styleEntry);

	MenuStyleTable::TextButtonStyle* m_unk0x1a8; // 0x1a8
	MenuStyleTable::TextStyle m_unk0x1ac;        // 0x1ac
	GolFont* m_unk0x1c0[6];                      // 0x1c0
	UtopianPan0xa4* m_unk0x1d8[6];               // 0x1d8
	VisualStateColor m_unk0x1f0[6];              // 0x1f0
	MenuImage m_unk0x208;                        // 0x208
	MenuTextLabel m_unk0x264;                    // 0x264
	LegoS32 m_unk0x2dc;                          // 0x2dc
	undefined4 m_unk0x2e0[4];                    // 0x2e0
};

#endif // MENUTEXTBUTTON_H
