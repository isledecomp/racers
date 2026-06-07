#ifndef MENUCOLORBOX_H
#define MENUCOLORBOX_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menutriangle.h"

// VTABLE: LEGORACERS 0x004b20a0
// SIZE 0xc0
class MenuColorBox : public MenuTriangle {
public:
	// SIZE 0x44
	class CreateParams : public MenuWidget::CreateParams {
	public:
		undefined4 m_unk0x38; // 0x38
		undefined4 m_unk0x3c; // 0x3c
		undefined4 m_unk0x40; // 0x40
	};

	MenuColorBox();

	void Reset() override;                         // vtable+0x00
	~MenuColorBox() override;                      // vtable+0x04
	void VTable0x10(Rect*) override;               // vtable+0x10
	MenuWidget* VTable0x38(Rect*, Rect*) override; // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;    // vtable+0x3c

	LegoBool32 FUN_00467f70(CreateParams* p_createParams);
	void FUN_00467fc0(LegoS32 p_x, LegoS32 p_y);
	void FUN_00468000(LegoS32 p_width);
	void FUN_00468040(LegoS32 p_height);

	// SYNTHETIC: LEGORACERS 0x00467ec0
	// MenuColorBox::`scalar deleting destructor'

protected:
	undefined4 m_unk0xa4; // 0xa4
	undefined4 m_unk0xa8; // 0xa8
	undefined4 m_unk0xac; // 0xac
	undefined4 m_unk0xb0; // 0xb0
	undefined4 m_unk0xb4; // 0xb4
	undefined4 m_unk0xb8; // 0xb8
	undefined4 m_unk0xbc; // 0xbc
};

#endif // MENUCOLORBOX_H
