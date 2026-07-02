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
	void Reset() override;                                                           // vtable+0x00
	~MenuCarousel() override;                                                        // vtable+0x04
	void SetColor(VisualStateColor*) override;                                       // vtable+0x14
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	virtual void SnapToSelection() = 0;                                              // vtable+0x40
	virtual void StartScroll(undefined4) = 0;                                        // vtable+0x44
	virtual void SetItemColors(VisualStateColor*, VisualStateColor*);                // vtable+0x48
	virtual void SetFocusedItemColors(VisualStateColor*, VisualStateColor*);         // vtable+0x4c
	virtual void SetSelection(undefined4) = 0;                                       // vtable+0x50
	virtual LegoS32 ScrollNext() = 0;                                                // vtable+0x54
	virtual LegoS32 ScrollPrevious() = 0;                                            // vtable+0x58

	LegoBool32 Create(CreateParams* p_createParams, MenuStyleTable::CarouselStyle* p_styleEntry);
	LegoS32 WrapIndex(LegoS32 p_index);
	LegoU32 GetSelectedIndex() const { return m_selectedIndex; }

	// SYNTHETIC: LEGORACERS 0x0046c8d0
	// MenuCarousel::`scalar deleting destructor'

protected:
	MenuStyleTable::CarouselStyle* m_style; // 0x58
	SoundGroupBinding* m_soundGroupBinding; // 0x5c
	LegoS32 m_slotCount;                    // 0x60
	undefined4 m_focusedSlot;               // 0x64
	LegoS32 m_itemCount;                    // 0x68
	LegoS32 m_selectedIndex;                // 0x6c
	LegoS32 m_scrolling;                    // 0x70
	LegoS32 m_scrollDurationMs;             // 0x74
};

// VTABLE: LEGORACERS 0x004b24b4
// SIZE 0x94
class MenuScrollCarousel : public MenuCarousel {
public:
	MenuScrollCarousel();
	void Reset() override;                    // vtable+0x00
	~MenuScrollCarousel() override;           // vtable+0x04
	void SnapToSelection() override;          // vtable+0x40
	void SetSelection(undefined4) override;   // vtable+0x50
	virtual void LayoutItem(MenuWidget*) = 0; // vtable+0x5c

	void SelectChild(MenuWidget* p_child);
	void AddItem(MenuWidget* p_unk0x04);
	void RemoveItem(MenuWidget* p_child);
	MenuWidget* RemoveItemByIndex(LegoS32 p_index);
	void RemoveAllItems();
	MenuWidget* GetSelectedChild() const { return m_selectedChild; }

	// SYNTHETIC: LEGORACERS 0x0046d870
	// MenuScrollCarousel::`scalar deleting destructor'

protected:
	MenuWidget* m_selectedChild;      // 0x78
	undefined m_unk0x7c[0x8c - 0x7c]; // 0x7c
	LegoFloat m_scrollSpeed;          // 0x8c
	LegoFloat m_scrollPosition;       // 0x90
};

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

#endif // MENUCAROUSEL_H
