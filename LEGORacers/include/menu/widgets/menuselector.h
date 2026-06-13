#ifndef MENUSELECTOR_H
#define MENUSELECTOR_H

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
		MenuButton::CreateParams* m_unk0x84; // 0x84
		MenuButton::CreateParams* m_unk0x88; // 0x88
	};

	// SIZE 0x90
	class CreateParamsWithCarousel : public CreateParams {
	public:
		MenuFrame::CreateParams* m_unk0x8c; // 0x8c
	};

	MenuSelectorBase();
	void Reset() override;                                                                // vtable+0x00
	~MenuSelectorBase() override;                                                         // vtable+0x04
	LegoBool32 VTable0x20(MenuInputDispatcher::Cursor*, undefined4, undefined4) override; // vtable+0x20
	LegoBool32 VTable0x24(InputEventQueue::Event*, undefined4, undefined4) override;      // vtable+0x24
	LegoBool32 VTable0x28(InputEventQueue::Event*, undefined4, undefined4) override;      // vtable+0x28
	void VTable0x44(undefined4) override;                                                 // vtable+0x44
	void VTable0x48(undefined4) override;                                                 // vtable+0x48
	void VTable0x4c(undefined4) override;                                                 // vtable+0x4c
	void VTable0x50(undefined4) override;                                                 // vtable+0x50
	void VTable0x58(undefined4) override;                                                 // vtable+0x58
	virtual undefined4 VTable0x70(undefined4, undefined4, undefined4);                    // vtable+0x70
	virtual undefined4 VTable0x74(undefined4) = 0;                                        // vtable+0x74
	virtual void VTable0x78() = 0;                                                        // vtable+0x78
	virtual void VTable0x7c() = 0;                                                        // vtable+0x7c
	MenuButton& GetUnk0x1ac() { return m_unk0x1ac; }
	MenuButton& GetUnk0x3c8() { return m_unk0x3c8; }
	undefined4 GetUnk0x5e4() const { return m_unk0x5e4; }
	void FUN_00467180(undefined4 p_param);
	void FUN_004671e0(undefined4 p_param);

	// SYNTHETIC: LEGORACERS 0x00466fd0
	// MenuSelectorBase::`scalar deleting destructor'

protected:
	LegoBool32 FUN_004670a0(CreateParams* p_createParams, const MenuStyleTable::SelectorStyleBase* p_styleEntry);
	LegoBool32 FUN_00467150(CreateParams* p_createParams, const MenuStyleTable::SelectorStyleBase* p_styleEntry);
	LegoBool32 FUN_004677e0(CreateParamsWithCarousel* p_createParams);
	LegoBool32 FUN_00467560(InputEventQueue::Event* p_event, undefined4 p_result);
	LegoBool32 FUN_00467670(InputEventQueue::Event* p_event, undefined4 p_result);

	undefined4 m_unk0x1a8;                           // 0x1a8
	MenuButton m_unk0x1ac;                           // 0x1ac
	MenuButton m_unk0x3c8;                           // 0x3c8
	undefined4 m_unk0x5e4;                           // 0x5e4
	MenuStyleTable::SelectorStyleBase* m_styleEntry; // 0x5e8
};

// VTABLE: LEGORACERS 0x004b2020
// SIZE 0x9f4
class MenuSelector : public MenuSelectorBase {
public:
	// SIZE 0x98
	class CreateParams : public MenuSelectorBase::CreateParamsWithCarousel {
	public:
		MenuCarousel* m_unk0x90; // 0x90
		undefined4 m_unk0x94;    // 0x94
	};

	MenuSelector();
	void Reset() override;                                                            // vtable+0x00
	~MenuSelector() override;                                                         // vtable+0x04
	LegoBool32 VTable0x08() override;                                                 // vtable+0x08
	void VTable0x14(VisualStateColor*) override;                                      // vtable+0x14
	LegoBool32 VTable0x24(InputEventQueue::Event*, undefined4, undefined4) override;  // vtable+0x24
	MenuWidget* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
	undefined4 VTable0x3c(undefined4) override;                                       // vtable+0x3c
	undefined4 VTable0x74(undefined4) override;                                       // vtable+0x74
	void VTable0x78() override;                                                       // vtable+0x78
	void VTable0x7c() override;                                                       // vtable+0x7c

	LegoBool32 FUN_00467800(CreateParams* p_createParams, MenuStyleTable::SelectorStyle* p_styleEntry);
	void SetUnk0x9ec(undefined4 p_unk0x9ec) { m_unk0x9ec = p_unk0x9ec; }

	// SYNTHETIC: LEGORACERS 0x00467730
	// MenuSelector::`scalar deleting destructor'

protected:
	MenuStyleTable::SelectorStyle* GetStyleEntry() { return static_cast<MenuStyleTable::SelectorStyle*>(m_styleEntry); }

	MenuFrame m_unk0x5ec;     // 0x5ec
	MenuCarousel* m_unk0x9e8; // 0x9e8
	undefined4 m_unk0x9ec;    // 0x9ec
	undefined4 m_unk0x9f0;    // 0x9f0
};

#endif // MENUSELECTOR_H
