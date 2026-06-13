#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include "decomp.h"
#include "menu/menuscreencreateparams.h"
#include "menu/screens/menuscreen.h"
#include "menu/style/menuinputbindingtable.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menutextlabel.h"
#include "types.h"

class MenuInputDispatcher;
class SharedMenuStyleTable;

// SIZE 0xa4
class MenuDialog {
public:
	// VTABLE: LEGORACERS 0x004b2784
	// SIZE 0x78
	class TextLine : public MenuTextLabel {
	public:
		TextLine();
		~TextLine() override;                          // vtable+0x04
		MenuWidget* VTable0x38(Rect*, Rect*) override; // vtable+0x38
		void VTable0x40(GolString*, LegoS32) override; // vtable+0x40

		// SYNTHETIC: LEGORACERS 0x0046f860
		// MenuDialog::TextLine::`scalar deleting destructor'
	};

	// VTABLE: LEGORACERS 0x004b20e0
	// SIZE 0x74c
	class DialogScreen : public MenuScreen {
	public:
		// SIZE 0x18
		class CreateParams {
		public:
			MenuScreenCreateParams* m_createParams; // 0x00
			MenuDialog* m_owner;                    // 0x04
			MenuScreen* m_eventHandler;             // 0x08
			undefined4 m_unk0x0c;                   // 0x0c
			undefined2 m_unk0x10;                   // 0x10
			undefined4 m_unk0x14;                   // 0x14
		};

		DialogScreen();
		~DialogScreen() override; // vtable+0x68
		LegoBool32 VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4,
							  undefined4) override; // vtable+0x18
		LegoBool32 VTable0x1c(MenuWidget*, InputEventQueue::Event*, undefined4,
							  undefined4) override;                 // vtable+0x1c
		void VTable0x38(MenuWidget*) override;                      // vtable+0x38
		void VTable0x4c() override;                                 // vtable+0x4c
		undefined4 VTable0x50() override;                           // vtable+0x50
		void Reset() override;                                      // vtable+0x54
		MenuStyleTable* GetMenuStyles() override;                   // vtable+0x5c
		MenuInputBindingTable* GetMenuInputBindings() override;     // vtable+0x64
		LegoBool32 VTable0x78(undefined4 p_elapsedMs) override;     // vtable+0x78
		LegoBool32 VTable0x7c(Rect* p_arg1, Rect* p_arg2) override; // vtable+0x7c

		// SYNTHETIC: LEGORACERS 0x00468bf0
		// MenuDialog::DialogScreen::`vector deleting destructor'

		LegoBool32 FUN_00468300(CreateParams* p_createParams);
		void FUN_00468590();
		void FUN_004687a0();
		undefined4 GetUnk0x2c0() const;
		void SetUnk0x740(MenuIcon* p_unk0x740) { m_unk0x740 = p_unk0x740; }
		void SetUnk0x744(MenuIcon* p_unk0x744) { m_unk0x744 = p_unk0x744; }
		void SetUnk0x748(MenuIcon* p_unk0x748) { m_unk0x748 = p_unk0x748; }

	private:
		void FUN_00468390();
		void FUN_00468430();
		void FUN_004684e0();
		void FUN_004686f0();
		void FUN_00468740();

		MenuDialog* m_unk0x290;              // 0x290
		MenuStyleTable* m_unk0x294;          // 0x294
		MenuScreen* m_unk0x298;              // 0x298
		LegoS32 m_unk0x29c;                  // 0x29c
		LegoS32 m_unk0x2a0;                  // 0x2a0
		LegoFloat m_unk0x2a4;                // 0x2a4
		LegoFloat m_unk0x2a8;                // 0x2a8
		undefined2 m_unk0x2ac;               // 0x2ac
		undefined m_unk0x2ae[0x2b0 - 0x2ae]; // 0x2ae
		LegoU32 m_unk0x2b0;                  // 0x2b0
		LegoS32 m_unk0x2b4;                  // 0x2b4
		undefined4 m_unk0x2b8;               // 0x2b8
		undefined4 m_unk0x2bc;               // 0x2bc
		undefined4 m_unk0x2c0;               // 0x2c0
		undefined4 m_unk0x2c4;               // 0x2c4
		undefined4 m_unk0x2c8;               // 0x2c8
		MenuFrame m_unk0x2cc;                // 0x2cc
		TextLine m_unk0x6c8;                 // 0x6c8
		MenuIcon* m_unk0x740;                // 0x740
		MenuIcon* m_unk0x744;                // 0x744
		MenuIcon* m_unk0x748;                // 0x748
	};

	MenuDialog();
	~MenuDialog();

	LegoS32 Reset();
	LegoS32 FUN_00468ab0();
	DialogScreen* FUN_00468c50(undefined4 p_unk0x04, undefined2 p_unk0x08, MenuScreen* p_unk0x0c, undefined4 p_unk0x10);
	void FUN_00468cf0();
	void FUN_00468da0(LegoU32 p_unk0x04);
	void FUN_00468e20();
	LegoBool32 FUN_00468af0(
		MenuScreenCreateParams* p_createParams,
		LegoS32 p_count,
		MenuInputDispatcher* p_inputDispatcher
	);
	LegoU32 GetUnk0x9c() const { return m_unk0x9c; }

private:
	void FUN_00468d20();

	MenuInputBindingTable m_unk0x00;        // 0x00
	MenuScreenCreateParams m_createParams;  // 0x5c
	DialogScreen* m_entries;                // 0x8c
	MenuInputDispatcher* m_inputDispatcher; // 0x90
	MenuScreen* m_previousScreen;           // 0x94
	LegoS32 m_count;                        // 0x98
	LegoU32 m_unk0x9c;                      // 0x9c
	undefined4 m_unk0xa0;                   // 0xa0
};

#endif // MENUDIALOG_H
