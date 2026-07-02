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

	void Reset() override;                       // vtable+0x00
	~MenuColorBox() override;                    // vtable+0x04
	void SetRect(Rect*) override;                // vtable+0x10
	MenuWidget* DrawSelf(Rect*, Rect*) override; // vtable+0x38
	undefined4 OnEvent(undefined4) override;     // vtable+0x3c

	LegoBool32 Create(CreateParams* p_createParams);
	void SetPosition(LegoS32 p_x, LegoS32 p_y);
	void SetWidth(LegoS32 p_width);
	void SetHeight(LegoS32 p_height);

	// SYNTHETIC: LEGORACERS 0x00467ec0
	// MenuColorBox::`scalar deleting destructor'

protected:
	undefined4 m_unk0xa4; // 0xa4
	undefined4 m_unk0xa8; // 0xa8
	undefined4 m_unk0xac; // 0xac
	undefined4 m_unk0xb0; // 0xb0
	undefined4 m_unk0xb4; // 0xb4
	undefined4 m_width;   // 0xb8
	undefined4 m_height;  // 0xbc
};

#endif // MENUCOLORBOX_H
