#ifndef MENUGAMESCREEN_H
#define MENUGAMESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menuscreen.h"
#include "menu/style/sharedmenustyletable.h"
#include "render/golrenderdevice.h"

class MenuGameContext;
class MenuScreenCreateParams;
class MenuTextButton;
class MenuWidget;
class GolFont;
class GolImage;
class CarPartCarousel;

// VTABLE: LEGORACERS 0x004b3518
// SIZE 0x368
class MenuGameScreen : public MenuScreen {
public:
	// VTABLE: LEGORACERS 0x004b3480
	// SIZE 0x60
	class ButtonBindingTable : public MenuInputBindingTable {
	public:
		// VTABLE: LEGORACERS 0x004b3498
		// SIZE 0x1fc
		class MidTxtParser : public GolTxtParser {};

		ButtonBindingTable();
		~ButtonBindingTable() override;                  // vtable+0x00
		void Clear() override;                           // vtable+0x08
		void Reset() override;                           // vtable+0x0c
		void CreateParser(undefined4 p_binary) override; // vtable+0x10
		void ParseSection(undefined4 p_token) override;  // vtable+0x14

		// SIZE 0xe0
		class ButtonBinding : public MenuInputBindingTable::IconBinding {
		public:
			GolFont* m_stateFonts[6];          // 0x84
			GolImage* m_stateImages[6];        // 0x9c
			VisualStateColor m_stateColors[6]; // 0xb4
			undefined m_unk0xcc[0xd0 - 0xcc];  // 0xcc
			VisualStateColor m_unk0xd0;        // 0xd0
			undefined m_unk0xd4[0xd8 - 0xd4];  // 0xd4
			undefined4 m_maxTextWidth;         // 0xd8
			undefined4 m_hasMaxTextWidth;      // 0xdc
		};

		// SYNTHETIC: LEGORACERS 0x0047f0f0
		// MenuGameScreen::ButtonBindingTable::`scalar deleting destructor'

	private:
		void ParseButtonBinding(ButtonBinding* p_entry);
		void ParseButtonSection();

		ButtonBinding* m_entries; // 0x5c
	};

	MenuGameScreen();

	LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x1c
	void OnIconFocused(MenuIcon*) override;                                                          // vtable+0x34
	void OnIconSelected(MenuIcon*) override;                                                         // vtable+0x3c
	void OnIconDeselected(MenuIcon*) override;                                                       // vtable+0x40
	void Reset() override;                                                                           // vtable+0x54
	MenuStyleTable* GetMenuStyles() override;                                                        // vtable+0x5c
	MenuInputBindingTable* GetMenuInputBindings() override;                                          // vtable+0x64
	~MenuGameScreen() override;                                                                      // vtable+0x68
	LegoFloat GetAspectScale() override;                                                             // vtable+0x6c
	LegoBool32 Destroy() override;                                                                   // vtable+0x74
	LegoBool32 Update(undefined4) override;                                                          // vtable+0x78
	virtual void SetupLighting();                                                                    // vtable+0x80
	virtual void Navigate() = 0;                                                                     // vtable+0x84
	virtual LegoBool32 CanNavigate();                                                                // vtable+0x88
	virtual LegoBool32 Initialize(MenuGameContext*,
								  MenuScreenCreateParams*); // vtable+0x8c
	virtual void OnChar(undefined4);                        // vtable+0x90
	virtual void VTable0x94(undefined4);                    // vtable+0x94

	void StartMenuMusic(MenuGameContext* p_context, undefined4 p_unk0x08, undefined4 p_unk0x0c);

	// SYNTHETIC: LEGORACERS 0x0047fb60
	// MenuGameScreen::`scalar deleting destructor'

protected:
	void LoadPieceResources(MenuGameContext* p_context, undefined4 p_unk0x08);
	void DestroyPieceResources(MenuGameContext* p_context);
	void LoadChampionResources(LegoS32 p_entryCapacity);
	void DestroyChampionResources();
	void LoadPartResources(MenuGameContext* p_context, undefined4 p_unk0x08);
	void LoadCosmeticTable();
	void ClearCosmeticTable();

	ButtonBindingTable::ButtonBinding* GetButtonBinding(undefined2 p_id)
	{
		return static_cast<ButtonBindingTable::ButtonBinding*>(GetBindingEntry(p_id));
	}

	undefined4 CreatePartCarousel(CarPartCarousel* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c);
	undefined4 CreateTextButton(
		MenuTextButton* p_unk0x04,
		undefined2 p_unk0x08,
		undefined2 p_unk0x0c,
		undefined2 p_unk0x10
	);
	void SetLighting(const ColorRGBA* p_materialColor, const ColorRGBA* p_lightColor);
	void ReinitializeInputBindings();
	LegoBool32 IsMenuMusicPlaying(MenuGameContext* p_context);
	void StopMenuMusic(MenuGameContext* p_context);

	SharedMenuStyleTable m_sharedStyles;            // 0x290
	ButtonBindingTable m_buttonBindings;            // 0x2e0
	GolRenderDevice::Light m_light;                 // 0x340
	GolRenderDevice::MaterialColor m_materialColor; // 0x350
	MenuGameContext* m_context;                     // 0x354
	MenuIcon* m_selectedIcon;                       // 0x358
	MenuWidget* m_clickedWidget;                    // 0x35c
	LegoU16 m_nextMenuId;                           // 0x360
	LegoU16 m_menuId;                               // 0x362
	LegoBool32 m_navPending;                        // 0x364
};

#endif // MENUGAMESCREEN_H
