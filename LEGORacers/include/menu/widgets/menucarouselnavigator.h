#ifndef MENUCAROUSELNAVIGATOR_H
#define MENUCAROUSELNAVIGATOR_H

#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuscrollcarousel.h"

// VTABLE: LEGORACERS 0x004b2bac
// SIZE 0x94
class MenuCarouselNavigator : public MenuScrollCarousel {
public:
	// FUNCTION: LEGORACERS 0x00488dd0
	MenuCarouselNavigator() {}

	MenuWidget* DrawSelf(Rect*, Rect*) override; // vtable+0x38
	undefined4 OnEvent(undefined4) override;     // vtable+0x3c
	void StartScroll(undefined4) override;       // vtable+0x44
	LegoS32 ScrollNext() override;               // vtable+0x54
	LegoS32 ScrollPrevious() override;           // vtable+0x58
	void LayoutItem(MenuWidget*) override;       // vtable+0x5c

	// SYNTHETIC: LEGORACERS 0x0046c870
	// MenuCarouselNavigator::~MenuCarouselNavigator

	// SYNTHETIC: LEGORACERS 0x00475610
	// MenuCarouselNavigator::`scalar deleting destructor'
};

#endif // MENUCAROUSELNAVIGATOR_H
