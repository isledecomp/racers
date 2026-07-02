#ifndef MENUHOTSPOTBUTTON_H
#define MENUHOTSPOTBUTTON_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menustyletable.h"
#include "menu/widgets/menubutton.h"

class UtopianPan0xa4;

// VTABLE: LEGORACERS 0x004b1ef0
// SIZE 0x228
class MenuHotspotButton : public MenuButton {
public:
	// SIZE 0xa0
	class CreateParams : public MenuButton::CreateParams {
	public:
		UtopianPan0xa4* m_unk0x9c; // 0x9c
	};

	MenuHotspotButton();

	void Reset() override;                                                           // vtable+0x00
	~MenuHotspotButton() override;                                                   // vtable+0x04
	LegoBool32 Destroy() override;                                                   // vtable+0x08
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x34
	MenuWidget* DrawSelf(Rect*, Rect*) override;                                     // vtable+0x38
	void Unfocus(undefined4) override;                                               // vtable+0x58

	LegoBool32 Create(CreateParams* p_createParams, MenuStyleTable::HotspotStyle* p_styleEntry);
	LegoU32 GetHotspotIndex() const { return m_hotspotIndex; }

	// SYNTHETIC: LEGORACERS 0x00466560
	// MenuHotspotButton::`scalar deleting destructor'

protected:
	enum {
		// Synthetic keyCode source occupying the high nibble alongside InputDevice::c_source*
		// (keyboard/mouse/joystick). It tags hotspot-region selection messages with the region
		// id in the low 16 bits so they flow through the same keyCode path as real input. Only
		// ever produced and consumed inside this widget; no real input device emits it.
		c_sourceRegion = 0x50000000,
	};

	Rect* FUN_00466640(Rect* p_rect1, Rect* p_rect2, Rect* p_out);
	void FUN_00466690(LegoU32 p_code);
	MenuWidget* FUN_00466800(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y);

	MenuStyleTable::HotspotStyle* m_unk0x21c; // 0x21c
	UtopianPan0xa4* m_unk0x220;               // 0x220
	undefined4 m_hotspotIndex;                // 0x224
};

#endif // MENUHOTSPOTBUTTON_H
