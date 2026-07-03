#ifndef MENUSELECTOR_H
#define MENUSELECTOR_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menustyletable.h"
#include "menu/widgets/menubutton.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menuselectorbase.h"

// VTABLE: LEGORACERS 0x004b2020
// SIZE 0x9f4
class MenuSelector : public MenuSelectorBase {
public:
	// SIZE 0x98
	class CreateParams : public MenuSelectorBase::CreateParamsWithCarousel {
	public:
		MenuCarousel* m_carouselWidget;    // 0x90
		undefined4 m_acceptUnfocusedInput; // 0x94
	};

	MenuSelector();
	void Reset() override;                                                                // vtable+0x00
	~MenuSelector() override;                                                             // vtable+0x04
	LegoBool32 Destroy() override;                                                        // vtable+0x08
	void SetColor(VisualStateColor*) override;                                            // vtable+0x14
	LegoBool32 DispatchKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x24
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override;      // vtable+0x30
	MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;        // vtable+0x34
	undefined4 OnEvent(undefined4) override;                                              // vtable+0x3c
	undefined4 TranslateNavigationEvent(undefined4) override;                             // vtable+0x74
	void StepPrevious() override;                                                         // vtable+0x78
	void StepNext() override;                                                             // vtable+0x7c

	LegoBool32 Create(CreateParams* p_createParams, MenuStyleTable::SelectorStyle* p_styleEntry);
	void SetAcceptUnfocusedInput(undefined4 p_accept) { m_acceptUnfocusedInput = p_accept; }

	// SYNTHETIC: LEGORACERS 0x00467730
	// MenuSelector::`scalar deleting destructor'

protected:
	MenuStyleTable::SelectorStyle* GetStyleEntry() { return static_cast<MenuStyleTable::SelectorStyle*>(m_styleEntry); }

	MenuFrame m_unk0x5ec;              // 0x5ec
	MenuCarousel* m_carousel;          // 0x9e8
	undefined4 m_acceptUnfocusedInput; // 0x9ec
	undefined4 m_scrollPending;        // 0x9f0
};

#endif // MENUSELECTOR_H
