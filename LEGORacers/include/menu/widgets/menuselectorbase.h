#ifndef MENUSELECTORBASE_H
#define MENUSELECTORBASE_H

#include "compat.h"
#include "decomp.h"
#include "menu/style/menustyletable.h"
#include "menu/widgets/menubutton.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuframe.h"

// VTABLE: LEGORACERS 0x004b1fa0
// SIZE 0x5ec
class MenuSelectorBase : public MenuIcon {
public:
	// SIZE 0x8c
	class CreateParams : public MenuIcon::CreateParams {
	public:
		MenuButton::CreateParams* m_prevButtonParams; // 0x84
		MenuButton::CreateParams* m_nextButtonParams; // 0x88
	};

	// SIZE 0x90
	class CreateParamsWithCarousel : public CreateParams {
	public:
		MenuFrame::CreateParams* m_frameParams; // 0x8c
	};

	MenuSelectorBase();
	void Reset() override;                                                                         // vtable+0x00
	~MenuSelectorBase() override;                                                                  // vtable+0x04
	LegoBool32 DispatchCursorEvent(MenuInputDispatcher::Cursor*, undefined4, undefined4) override; // vtable+0x20
	LegoBool32 DispatchKeyDown(InputEventQueue::Event*, undefined4, undefined4) override;          // vtable+0x24
	LegoBool32 DispatchKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;            // vtable+0x28
	void Enable(undefined4) override;                                                              // vtable+0x44
	void Disable(undefined4) override;                                                             // vtable+0x48
	void Select(undefined4) override;                                                              // vtable+0x4c
	void Deselect(undefined4) override;                                                            // vtable+0x50
	void Unfocus(undefined4) override;                                                             // vtable+0x58
	virtual undefined4 MapCursorToNavigation(undefined4, undefined4, undefined4);                  // vtable+0x70
	virtual undefined4 TranslateNavigationEvent(undefined4) = 0;                                   // vtable+0x74
	virtual void StepPrevious() = 0;                                                               // vtable+0x78
	virtual void StepNext() = 0;                                                                   // vtable+0x7c
	MenuButton& GetPrevButton() { return m_prevButton; }
	MenuButton& GetNextButton() { return m_nextButton; }
	undefined4 GetStepDirection() const { return m_stepDirection; }
	void OnPreviousPressed(undefined4 p_param);
	void OnNextPressed(undefined4 p_param);

	// SYNTHETIC: LEGORACERS 0x00466fd0
	// MenuSelectorBase::`scalar deleting destructor'

protected:
	LegoBool32 Create(CreateParams* p_createParams, const MenuStyleTable::SelectorStyleBase* p_styleEntry);
	LegoBool32 CreateDefault(CreateParams* p_createParams, const MenuStyleTable::SelectorStyleBase* p_styleEntry);
	LegoBool32 CreateWithFrame(CreateParamsWithCarousel* p_createParams);
	LegoBool32 HandleNavigationKeyDown(InputEventQueue::Event* p_event, undefined4 p_result);
	LegoBool32 HandleNavigationKeyUp(InputEventQueue::Event* p_event, undefined4 p_result);

	undefined4 m_unk0x1a8;                           // 0x1a8
	MenuButton m_prevButton;                         // 0x1ac
	MenuButton m_nextButton;                         // 0x3c8
	undefined4 m_stepDirection;                      // 0x5e4
	MenuStyleTable::SelectorStyleBase* m_styleEntry; // 0x5e8
};

#endif // MENUSELECTORBASE_H
