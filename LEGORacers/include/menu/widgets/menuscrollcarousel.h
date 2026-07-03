#ifndef MENUSCROLLCAROUSEL_H
#define MENUSCROLLCAROUSEL_H

#include "menu/widgets/menucarousel.h"

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
	void AddItem(MenuWidget* p_item);
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

#endif // MENUSCROLLCAROUSEL_H
