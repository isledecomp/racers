#ifndef MENUCAROUSEL_H
#define MENUCAROUSEL_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menustyletable.h"
#include "menu/widgets/menustaticwidget.h"

class SoundGroupBinding;

// VTABLE: LEGORACERS 0x004b23f0
// SIZE 0x78
class MenuCarousel : public MenuStaticWidget {
public:
	// SIZE 0x38
	class CreateParams : public MenuWidget::CreateParams {};

	MenuCarousel();
	void Reset() override;                                                            // vtable+0x00
	~MenuCarousel() override;                                                         // vtable+0x04
	void VTable0x14(VisualStateColor*) override;                                      // vtable+0x14
	MenuWidget* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	virtual void VTable0x40() = 0;                                                    // vtable+0x40
	virtual void VTable0x44(undefined4) = 0;                                          // vtable+0x44
	virtual void VTable0x48(VisualStateColor*, VisualStateColor*);                    // vtable+0x48
	virtual void VTable0x4c(VisualStateColor*, VisualStateColor*);                    // vtable+0x4c
	virtual void VTable0x50(undefined4) = 0;                                          // vtable+0x50
	virtual LegoS32 VTable0x54() = 0;                                                 // vtable+0x54
	virtual LegoS32 VTable0x58() = 0;                                                 // vtable+0x58

	LegoBool32 FUN_0046c970(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry);
	LegoS32 FUN_0046c9a0(LegoS32 p_index);
	LegoU32 GetUnk0x6c() const { return m_unk0x6c; }

	// SYNTHETIC: LEGORACERS 0x0046c8d0
	// MenuCarousel::`scalar deleting destructor'

protected:
	MenuStyleTable::CarouselStyle* m_unk0x58; // 0x58
	SoundGroupBinding* m_unk0x5c;             // 0x5c
	LegoS32 m_unk0x60;                        // 0x60
	undefined4 m_unk0x64;                     // 0x64
	LegoS32 m_unk0x68;                        // 0x68
	LegoS32 m_unk0x6c;                        // 0x6c
	LegoS32 m_unk0x70;                        // 0x70
	LegoS32 m_unk0x74;                        // 0x74
};

// VTABLE: LEGORACERS 0x004b24b4
// SIZE 0x94
class MenuScrollCarousel : public MenuCarousel {
public:
	MenuScrollCarousel();
	void Reset() override;                    // vtable+0x00
	~MenuScrollCarousel() override;           // vtable+0x04
	void VTable0x40() override;               // vtable+0x40
	void VTable0x50(undefined4) override;     // vtable+0x50
	virtual void VTable0x5c(MenuWidget*) = 0; // vtable+0x5c

	void FUN_0046d920(MenuWidget* p_child);
	void FUN_0046d9c0(MenuWidget* p_unk0x04);
	void FUN_0046da00(MenuWidget* p_child);
	MenuWidget* FUN_0046da40(LegoS32 p_index);
	void FUN_0046da60();
	MenuWidget* GetUnk0x78() const { return m_unk0x78; }

	// SYNTHETIC: LEGORACERS 0x0046d870
	// MenuScrollCarousel::`scalar deleting destructor'

protected:
	MenuWidget* m_unk0x78;            // 0x78
	undefined m_unk0x7c[0x8c - 0x7c]; // 0x7c
	LegoFloat m_unk0x8c;              // 0x8c
	LegoFloat m_unk0x90;              // 0x90
};

// VTABLE: LEGORACERS 0x004b2bac
// SIZE 0x94
class MenuCarouselNavigator : public MenuScrollCarousel {
public:
	// FUNCTION: LEGORACERS 0x00488dd0
	MenuCarouselNavigator() {}

	MenuWidget* VTable0x38(Rect*, Rect*) override; // vtable+0x38
	undefined4 VTable0x3c(undefined4) override;    // vtable+0x3c
	void VTable0x44(undefined4) override;          // vtable+0x44
	LegoS32 VTable0x54() override;                 // vtable+0x54
	LegoS32 VTable0x58() override;                 // vtable+0x58
	void VTable0x5c(MenuWidget*) override;         // vtable+0x5c

	// SYNTHETIC: LEGORACERS 0x0046c870
	// MenuCarouselNavigator::~MenuCarouselNavigator

	// SYNTHETIC: LEGORACERS 0x00475610
	// MenuCarouselNavigator::`scalar deleting destructor'
};

#endif // MENUCAROUSEL_H
