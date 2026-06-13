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

	undefined4 VTable0x14(MenuWidget*, void*, undefined4, undefined4) override;                   // vtable+0x14
	LegoBool32 VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x1c
	void Reset() override;                                                                        // vtable+0x54
	LegoBool32 VTable0x78(undefined4) override;                                                   // vtable+0x78
	LegoBool32 VTable0x7c(Rect*, Rect*) override;                                                 // vtable+0x7c
	virtual GolString* VTable0x98(undefined4) = 0;                                                // vtable+0x98
	virtual GolFont* VTable0x9c(undefined4) = 0;                                                  // vtable+0x9c
	virtual void VTable0xa0(LegoS32*, LegoS32*, LegoS32*, LegoS32*) = 0;                          // vtable+0xa0

	// SYNTHETIC: LEGORACERS 0x00476ed0
	// CarBuildScreenBase::`scalar deleting destructor'

protected:
	void FUN_00474e40();
	void FUN_00474e70(MenuIcon* p_icon);
	void FUN_00474ef0();
	void FUN_00474f20();

	LegoS32 m_unk0x368;    // 0x368
	LegoS32 m_unk0x36c;    // 0x36c
	LegoS32 m_unk0x370;    // 0x370
	MenuIcon* m_unk0x374;  // 0x374
	MenuIcon* m_unk0x378;  // 0x378
	LegoU8 m_unk0x37c;     // 0x37c
	LegoU8 m_unk0x37d;     // 0x37d
	LegoU16 m_unk0x37e;    // 0x37e
	Rect m_unk0x380;       // 0x380
	LegoS32 m_unk0x390;    // 0x390
	LegoS32 m_unk0x394;    // 0x394
	LegoS32 m_unk0x398;    // 0x398
	LegoS32 m_unk0x39c;    // 0x39c
	GolString* m_unk0x3a0; // 0x3a0
	GolFont* m_unk0x3a4;   // 0x3a4
	GolString m_unk0x3a8;  // 0x3a8
};

#endif // CARBUILDSCREENBASE_H
