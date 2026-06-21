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
class UtopianPan0xa4;
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
		~ButtonBindingTable() override;       // vtable+0x00
		void Clear() override;                // vtable+0x08
		void VTable0x0c() override;           // vtable+0x0c
		void VTable0x10(undefined4) override; // vtable+0x10
		void VTable0x14(undefined4) override; // vtable+0x14

		// SIZE 0xe0
		class ButtonBinding : public MenuInputBindingTable::IconBinding {
		public:
			GolFont* m_unk0x84[6];            // 0x84
			UtopianPan0xa4* m_unk0x9c[6];     // 0x9c
			VisualStateColor m_unk0xb4[6];    // 0xb4
			undefined m_unk0xcc[0xd0 - 0xcc]; // 0xcc
			VisualStateColor m_unk0xd0;       // 0xd0
			undefined m_unk0xd4[0xd8 - 0xd4]; // 0xd4
			undefined4 m_unk0xd8;             // 0xd8
			undefined4 m_unk0xdc;             // 0xdc
		};

		// SYNTHETIC: LEGORACERS 0x0047f0f0
		// MenuGameScreen::ButtonBindingTable::`scalar deleting destructor'

	private:
		void FUN_0047f2b0(ButtonBinding* p_entry);
		void FUN_0047f410();

		ButtonBinding* m_unk0x5c; // 0x5c
	};

	MenuGameScreen();

	LegoBool32 VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x1c
	void VTable0x34(MenuIcon*) override;                                                          // vtable+0x34
	void VTable0x3c(MenuIcon*) override;                                                          // vtable+0x3c
	void VTable0x40(MenuIcon*) override;                                                          // vtable+0x40
	void Reset() override;                                                                        // vtable+0x54
	MenuStyleTable* GetMenuStyles() override;                                                     // vtable+0x5c
	MenuInputBindingTable* GetMenuInputBindings() override;                                       // vtable+0x64
	~MenuGameScreen() override;                                                                   // vtable+0x68
	LegoFloat VTable0x6c() override;                                                              // vtable+0x6c
	LegoBool32 Destroy() override;                                                                // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                                   // vtable+0x78
	virtual void VTable0x80();                                                                    // vtable+0x80
	virtual void VTable0x84() = 0;                                                                // vtable+0x84
	virtual LegoBool32 VTable0x88();                                                              // vtable+0x88
	virtual LegoBool32 VTable0x8c(MenuGameContext*,
								  MenuScreenCreateParams*); // vtable+0x8c
	virtual void VTable0x90(undefined4);                    // vtable+0x90
	virtual void VTable0x94(undefined4);                    // vtable+0x94

	void FUN_00480470(MenuGameContext* p_context, undefined4 p_unk0x08, undefined4 p_unk0x0c);

	// SYNTHETIC: LEGORACERS 0x0047fb60
	// MenuGameScreen::`scalar deleting destructor'

protected:
	void FUN_0047ff50(MenuGameContext* p_context, undefined4 p_unk0x08);
	void FUN_004800c0(MenuGameContext* p_context);
	void FUN_00480110(LegoS32 p_entryCapacity);
	void FUN_004801e0();
	void FUN_00480210(MenuGameContext* p_context, undefined4 p_unk0x08);
	void FUN_00480310();
	void FUN_004803a0();

	ButtonBindingTable::ButtonBinding* GetButtonBinding(undefined2 p_id)
	{
		return static_cast<ButtonBindingTable::ButtonBinding*>(GetBindingEntry(p_id));
	}

	undefined4 FUN_0047fcf0(CarPartCarousel* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c);
	undefined4 FUN_0047fdc0(
		MenuTextButton* p_unk0x04,
		undefined2 p_unk0x08,
		undefined2 p_unk0x0c,
		undefined2 p_unk0x10
	);
	void FUN_0047fec0(const ColorRGBA* p_materialColor, const ColorRGBA* p_lightColor);
	void FUN_004803d0();
	LegoBool32 FUN_00480440(MenuGameContext* p_context);
	void FUN_004804c0(MenuGameContext* p_context);

	SharedMenuStyleTable m_unk0x290;           // 0x290
	ButtonBindingTable m_unk0x2e0;             // 0x2e0
	GolRenderDevice::Light m_unk0x340;         // 0x340
	GolRenderDevice::MaterialColor m_unk0x350; // 0x350
	MenuGameContext* m_context;                // 0x354
	MenuIcon* m_unk0x358;                      // 0x358
	MenuWidget* m_unk0x35c;                    // 0x35c
	LegoU16 m_unk0x360;                        // 0x360
	LegoU16 m_menuId;                          // 0x362
	LegoBool32 m_unk0x364;                     // 0x364
};

#endif // MENUGAMESCREEN_H
