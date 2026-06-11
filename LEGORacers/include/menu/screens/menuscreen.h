#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menuscreeninterface.h"
#include "menu/style/menuinputbindingtable.h"
#include "menu/style/menustyletable.h"
#include "menu/widgets/menuicon.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "text/coppercrest0x40.h"
#include "types.h"

class GolD3DRenderDevice;
class MenuDialog;
class GolExport;
class GolFontTable;
class GolString;
class GolStringTable;
class InputManager;
class MenuTextField;
class MenuTextLabel;
class MenuScreenCreateParams;
class MenuCarousel;
class MenuButton;
class MenuHotspotButton;
class MenuFramedSceneView;
class MenuFrame;
class MenuWidget;
class MenuSceneView;
class MenuTriangle;
class OptionsRowBase;
class SharedMenuStyleTable;
class SoundGroupBinding;
class AwakeKite0x20;

// VTABLE: LEGORACERS 0x004b2308
// SIZE 0x290
class MenuScreen : public MenuScreenInterface {
public:
	// SIZE 0x54
	class SceneRefBinding : public MenuWidget::CreateParams {
	public:
		LegoChar m_unk0x38[0x48 - 0x38]; // 0x38
		undefined4 m_unk0x48;            // 0x48
		LegoU32 m_unk0x4c;               // 0x4c
		LegoFloat m_unk0x50;             // 0x50
	};

	MenuScreen();

	void VTable0x00(MenuWidget*) override;                                                        // vtable+0x00
	void VTable0x04(MenuWidget*) override;                                                        // vtable+0x04
	void VTable0x08(MenuWidget*) override;                                                        // vtable+0x08
	void VTable0x0c(MenuWidget*) override;                                                        // vtable+0x0c
	void VTable0x10(MenuWidget*) override;                                                        // vtable+0x10
	undefined4 VTable0x14(MenuWidget*, void*, undefined4, undefined4) override;                   // vtable+0x14
	LegoBool32 VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x20(MenuWidget*) override;                                                        // vtable+0x20
	void VTable0x24(MenuWidget*) override;                                                        // vtable+0x24
	undefined4 VTable0x28(MenuWidget*, void*, undefined4, undefined4) override;                   // vtable+0x28
	void VTable0x2c(MenuIcon*) override;                                                          // vtable+0x2c
	void VTable0x30(MenuIcon*) override;                                                          // vtable+0x30
	void VTable0x34(MenuIcon*) override;                                                          // vtable+0x34
	void VTable0x38(MenuWidget*) override;                                                        // vtable+0x38
	void VTable0x3c(MenuIcon*) override;                                                          // vtable+0x3c
	void VTable0x40(MenuIcon*) override;                                                          // vtable+0x40
	void VTable0x44(MenuWidget*) override;                                                        // vtable+0x44
	void VTable0x48(MenuWidget*) override;                                                        // vtable+0x48
	virtual void VTable0x4c() = 0;                                                                // vtable+0x4c
	virtual undefined4 VTable0x50();                                                              // vtable+0x50
	virtual void Reset();                                                                         // vtable+0x54
	virtual LegoBool32 VTable0x58(MenuScreenCreateParams*);                                       // vtable+0x58
	virtual MenuStyleTable* GetMenuStyles();                                                      // vtable+0x5c
	virtual MenuStyleTable* VTable0x60();                                                         // vtable+0x60
	virtual MenuInputBindingTable* GetMenuInputBindings();                                        // vtable+0x64
	virtual ~MenuScreen();                                                                        // vtable+0x68
	virtual LegoFloat VTable0x6c();                                                               // vtable+0x6c
	virtual LegoBool32 Initialize(MenuScreenCreateParams*);                                       // vtable+0x70
	virtual LegoBool32 Destroy();                                                                 // vtable+0x74
	virtual LegoBool32 VTable0x78(undefined4);                                                    // vtable+0x78
	virtual LegoBool32 VTable0x7c(Rect* p_arg1, Rect* p_arg2);                                    // vtable+0x7c

	LegoBool32 FUN_0046b630();
	LegoBool32 FUN_0046b6e0(MenuScreenCreateParams*);
	void ApplyWidgetDefaults(MenuWidget::CreateParams*);
	void ApplyIconDefaults(MenuIcon::CreateParams*);
	void ApplySelectorDefaults(
		MenuSelectorBase::CreateParamsWithCarousel* p_createParams,
		MenuStyleTable::SelectorStyle* p_styleEntry
	);
	void ApplyCompositeDefaults(
		MenuInputBindingTable::CompositeBinding* p_createParams,
		MenuStyleTable::CompositeStyle* p_styleEntry
	);
	void* GetStyleEntry(undefined2);
	void* GetBindingEntry(undefined2);
	LegoBool32 CreateTriangle(MenuTriangle*, undefined2);
	LegoBool32 CreateImage(MenuImage*, undefined2, undefined2);
	LegoBool32 CreateTextLabel(MenuTextLabel*, undefined2, undefined2, undefined2);
	LegoBool32 CreateFrame(MenuFrame*, undefined2, undefined2);
	LegoBool32 CreateButton(MenuButton* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c);
	LegoBool32 CreateHotspotButton(MenuHotspotButton*, undefined2, undefined2);
	LegoBool32 CreateCarousel(MenuCarousel*, undefined2, undefined2);
	LegoBool32 CreateSelector(
		MenuSelector* p_widget,
		MenuCarousel* p_carousel,
		undefined2 p_cpId,
		undefined2 p_styleId
	);
	LegoBool32 CreateOptionsRow(OptionsRowBase*, undefined2, undefined2);
	LegoBool32 CreateSceneView(MenuSceneView* p_unk0x04, undefined4 p_unk0x08, undefined2 p_unk0x0c);
	LegoBool32 CreateFramedSceneView(MenuFramedSceneView* p_unk0x04, undefined4 p_unk0x08, undefined2 p_unk0x0c);
	undefined4 CreateRegion(MenuWidget*, undefined2);
	LegoBool32 CreateTextField(MenuTextField*, undefined2, undefined2, undefined2, GolString*);
	undefined4 FUN_0046c6f0(MenuIcon*, MenuIcon*, undefined2);
	undefined4 FUN_0046c730(MenuIcon*, undefined2);
	void FUN_0046c760();
	MenuIcon* GetUnk0xd8() { return &m_unk0xd8; }

	MenuStyleTable::ImageStyle* GetImageStyle(undefined2 p_id)
	{
		return static_cast<MenuStyleTable::ImageStyle*>(GetStyleEntry(p_id));
	}

	MenuStyleTable::TextButtonStyle* GetTextButtonStyle(undefined2 p_id)
	{
		return static_cast<MenuStyleTable::TextButtonStyle*>(GetStyleEntry(p_id));
	}

	MenuStyleTable::HotspotStyle* GetHotspotStyle(undefined2 p_id)
	{
		return static_cast<MenuStyleTable::HotspotStyle*>(GetStyleEntry(p_id));
	}

	MenuInputBindingTable::ImageBinding* GetImageBinding(undefined2 p_id)
	{
		return static_cast<MenuInputBindingTable::ImageBinding*>(GetBindingEntry(p_id));
	}

	MenuInputBindingTable::IconBinding* GetIconBinding(undefined2 p_id)
	{
		return static_cast<MenuInputBindingTable::IconBinding*>(GetBindingEntry(p_id));
	}

	SceneRefBinding* GetSceneRefBinding(undefined2 p_id)
	{
		return static_cast<SceneRefBinding*>(GetBindingEntry(p_id));
	}

	// SYNTHETIC: LEGORACERS 0x0046b3f0
	// MenuScreen::`scalar deleting destructor'

protected:
	LegoBool32 m_initialized;                    // 0x004
	MenuStyleTable m_unk0x08;                    // 0x008
	SharedMenuStyleTable* m_menuStyles;          // 0x054
	MenuInputBindingTable m_unk0x58;             // 0x058
	GolExport* m_golExport;                      // 0x0b4
	GolD3DRenderDevice* m_renderer;              // 0x0b8
	AwakeKite0x20* m_unk0xbc;                    // 0x0bc
	GolFontTable* m_fontTable;                   // 0x0c0
	CopperCrest0x40::Helper0x44* m_cursorHelper; // 0x0c4
	InputEventQueue* m_inputEvents;              // 0x0c8
	InputManager* m_inputManager;                // 0x0cc
	GolStringTable* m_menuNameStrings;           // 0x0d0
	GolStringTable* m_menuTextStrings;           // 0x0d4
	MenuIcon m_unk0xd8;                          // 0x0d8
	SoundGroupBinding* m_soundGroupBinding;      // 0x280
	MenuDialog* m_unk0x284;                      // 0x284
	undefined4 m_unk0x288;                       // 0x288
	undefined2 m_unk0x28c;                       // 0x28c
};

#endif // MENUSCREEN_H
