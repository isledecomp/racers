#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/menuinputdispatcher.h"
#include "menu/screens/menuscreeninterface.h"
#include "menu/style/menuinputbindingtable.h"
#include "menu/style/menustyletable.h"
#include "menu/style/scenerefbinding.h"
#include "menu/widgets/menuicon.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
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
class GolImageDefinitionList;

// VTABLE: LEGORACERS 0x004b2308
// SIZE 0x290
class MenuScreen : public MenuScreenInterface {
public:
	// SIZE 0x54
	MenuScreen();

	void OnWidgetCreated(MenuWidget*) override;                                                      // vtable+0x00
	void OnWidgetDestroyed(MenuWidget*) override;                                                    // vtable+0x04
	void OnWidgetMoved(MenuWidget*) override;                                                        // vtable+0x08
	void OnWidgetResized(MenuWidget*) override;                                                      // vtable+0x0c
	void OnCarouselSettled(MenuWidget*) override;                                                    // vtable+0x10
	undefined4 OnWidgetKeyUp(MenuWidget*, void*, undefined4, undefined4) override;                   // vtable+0x14
	LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x1c
	void OnWidgetFocused(MenuWidget*) override;                                                      // vtable+0x20
	void OnWidgetUnfocused(MenuWidget*) override;                                                    // vtable+0x24
	undefined4 OnWidgetKeyDown(MenuWidget*, void*, undefined4, undefined4) override;                 // vtable+0x28
	void OnIconEnabled(MenuIcon*) override;                                                          // vtable+0x2c
	void OnIconDisabled(MenuIcon*) override;                                                         // vtable+0x30
	void OnIconFocused(MenuIcon*) override;                                                          // vtable+0x34
	void OnIconUnfocused(MenuWidget*) override;                                                      // vtable+0x38
	void OnIconSelected(MenuIcon*) override;                                                         // vtable+0x3c
	void OnIconDeselected(MenuIcon*) override;                                                       // vtable+0x40
	void OnWidgetValueChanged(MenuWidget*) override;                                                 // vtable+0x44
	void OnSelectorSettled(MenuWidget*) override;                                                    // vtable+0x48
	virtual void CreateWidgets() = 0;                                                                // vtable+0x4c
	virtual undefined4 ShouldLoadResources();                                                        // vtable+0x50
	virtual void Reset();                                                                            // vtable+0x54
	virtual LegoBool32 LoadStylesAndBindings(MenuScreenCreateParams*);                               // vtable+0x58
	virtual MenuStyleTable* GetMenuStyles();                                                         // vtable+0x5c
	virtual MenuStyleTable* GetActiveStyles();                                                       // vtable+0x60
	virtual MenuInputBindingTable* GetMenuInputBindings();                                           // vtable+0x64
	virtual ~MenuScreen();                                                                           // vtable+0x68
	virtual LegoFloat GetAspectScale();                                                              // vtable+0x6c
	virtual LegoBool32 Initialize(MenuScreenCreateParams*);                                          // vtable+0x70
	virtual LegoBool32 Destroy();                                                                    // vtable+0x74
	virtual LegoBool32 Update(undefined4);                                                           // vtable+0x78
	virtual LegoBool32 Draw(Rect* p_arg1, Rect* p_arg2);                                             // vtable+0x7c

	LegoBool32 CreateRootIcon();
	LegoBool32 LoadImagesAndFonts(MenuScreenCreateParams*);
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
	LegoBool32 CreateButton(MenuButton* p_source, undefined2 p_event, undefined2 p_styleId);
	LegoBool32 CreateHotspotButton(MenuHotspotButton*, undefined2, undefined2);
	LegoBool32 CreateCarousel(MenuCarousel*, undefined2, undefined2);
	LegoBool32 CreateSelector(
		MenuSelector* p_widget,
		MenuCarousel* p_carousel,
		undefined2 p_cpId,
		undefined2 p_styleId
	);
	LegoBool32 CreateOptionsRow(OptionsRowBase*, undefined2, undefined2);
	LegoBool32 CreateSceneView(MenuSceneView* p_source, undefined4 p_event, undefined2 p_styleId);
	LegoBool32 CreateFramedSceneView(MenuFramedSceneView* p_source, undefined4 p_event, undefined2 p_styleId);
	undefined4 CreateRegion(MenuWidget*, undefined2);
	LegoBool32 CreateTextField(MenuTextField*, undefined2, undefined2, undefined2, GolString*);
	undefined4 ShowConfirmDialog(MenuIcon*, MenuIcon*, undefined2);
	undefined4 ShowPopupDialog(MenuIcon*, undefined2);
	void DetachAllWidgets();
	MenuIcon* GetRootIcon() { return &m_rootIcon; }

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
	LegoBool32 m_initialized;               // 0x004
	MenuStyleTable m_styleTable;            // 0x008
	SharedMenuStyleTable* m_menuStyles;     // 0x054
	MenuInputBindingTable m_bindingTable;   // 0x058
	GolExport* m_golExport;                 // 0x0b4
	GolD3DRenderDevice* m_renderer;         // 0x0b8
	GolImageDefinitionList* m_imageList;    // 0x0bc
	GolFontTable* m_fontTable;              // 0x0c0
	MenuInputDispatcher::Cursor* m_cursor;  // 0x0c4
	InputEventQueue* m_inputEvents;         // 0x0c8
	InputManager* m_inputManager;           // 0x0cc
	GolStringTable* m_menuNameStrings;      // 0x0d0
	GolStringTable* m_menuTextStrings;      // 0x0d4
	MenuIcon m_rootIcon;                    // 0x0d8
	SoundGroupBinding* m_soundGroupBinding; // 0x280
	MenuDialog* m_dialog;                   // 0x284
	undefined4 m_useBinaryFiles;            // 0x288
	undefined2 m_resourceMenuId;            // 0x28c
};

#endif // MENUSCREEN_H
