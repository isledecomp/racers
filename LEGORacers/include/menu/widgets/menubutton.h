#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "compat.h"
#include "decomp.h"
#include "menu/widgets/menuicon.h"
#include "menu/widgets/menuimage.h"

// VTABLE: LEGORACERS 0x004b1e80
// SIZE 0x21c
class MenuButton : public MenuIcon {
public:
	// SIZE 0x9c
	class CreateParams : public MenuIcon::CreateParams {
	public:
		UtopianPan0xa4* m_images[6]; // 0x84
	};

	MenuButton();
	void Reset() override;                         // vtable+0x00
	~MenuButton() override;                        // vtable+0x04
	LegoBool32 VTable0x08() override;              // vtable+0x08
	MenuWidget* VTable0x38(Rect*, Rect*) override; // vtable+0x38

	LegoBool32 FUN_004663d0(CreateParams* p_createParams, const MenuIcon::CreateState* p_createState);

	// SYNTHETIC: LEGORACERS 0x004662c0
	// MenuButton::`scalar deleting destructor'

protected:
	LegoBool32 FUN_00466370(MenuImage* p_unk0x04, CreateParams* p_createParams);

	UtopianPan0xa4* m_unk0x1a8[6]; // 0x1a8
	MenuImage m_unk0x1c0;          // 0x1c0
};

#endif // MENUBUTTON_H
