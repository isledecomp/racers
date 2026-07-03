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
		~TextLine() override;                         // vtable+0x04
		MenuWidget* DrawSelf(Rect*, Rect*) override;  // vtable+0x38
		void SetString(GolString*, LegoS32) override; // vtable+0x40

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
			undefined4 m_type;                      // 0x0c
			undefined2 m_notifyId;                  // 0x10
			undefined4 m_defaultYes;                // 0x14
		};

		DialogScreen();
		~DialogScreen() override; // vtable+0x68
		LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4,
								 undefined4) override; // vtable+0x18
		LegoBool32 HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4,
							   undefined4) override;            // vtable+0x1c
		void OnIconUnfocused(MenuWidget*) override;             // vtable+0x38
		void CreateWidgets() override;                          // vtable+0x4c
		undefined4 ShouldLoadResources() override;              // vtable+0x50
		void Reset() override;                                  // vtable+0x54
		MenuStyleTable* GetMenuStyles() override;               // vtable+0x5c
		MenuInputBindingTable* GetMenuInputBindings() override; // vtable+0x64
		LegoBool32 Update(undefined4 p_elapsedMs) override;     // vtable+0x78
		LegoBool32 Draw(Rect* p_arg1, Rect* p_arg2) override;   // vtable+0x7c

		// SYNTHETIC: LEGORACERS 0x00468bf0
		// MenuDialog::DialogScreen::`vector deleting destructor'

		LegoBool32 Initialize(CreateParams* p_createParams);
		void Open();
		void BeginClose();
		undefined4 GetResult() const;
		void SetPopupIcon(MenuIcon* p_popupIcon) { m_popupIcon = p_popupIcon; }
		void SetYesIcon(MenuIcon* p_yesIcon) { m_yesIcon = p_yesIcon; }
		void SetNoIcon(MenuIcon* p_noIcon) { m_noIcon = p_noIcon; }

	private:
		void AttachPopupIcon();
		void AttachYesIcon();
		void AttachNoIcon();
		void EnableWidgets();
		void DisableWidgets();

		MenuDialog* m_owner;                 // 0x290
		MenuStyleTable* m_menuStyles;        // 0x294
		MenuScreen* m_eventHandler;          // 0x298
		LegoS32 m_centerX;                   // 0x29c
		LegoS32 m_centerY;                   // 0x2a0
		LegoFloat m_halfWidth;               // 0x2a4
		LegoFloat m_halfHeight;              // 0x2a8
		undefined2 m_notifyId;               // 0x2ac
		undefined m_unk0x2ae[0x2b0 - 0x2ae]; // 0x2ae
		LegoU32 m_ageMs;                     // 0x2b0
		LegoS32 m_animMs;                    // 0x2b4
		undefined4 m_type;                   // 0x2b8
		undefined4 m_state;                  // 0x2bc
		undefined4 m_result;                 // 0x2c0
		undefined4 m_closed;                 // 0x2c4
		undefined4 m_defaultYes;             // 0x2c8
		MenuFrame m_frame;                   // 0x2cc
		TextLine m_messageLabel;             // 0x6c8
		MenuIcon* m_popupIcon;               // 0x740
		MenuIcon* m_yesIcon;                 // 0x744
		MenuIcon* m_noIcon;                  // 0x748
	};

	MenuDialog();
	~MenuDialog();

	LegoS32 Reset();
	LegoS32 Destroy();
	DialogScreen* OpenDialog(
		undefined4 p_type,
		undefined2 p_notifyId,
		MenuScreen* p_eventHandler,
		undefined4 p_defaultYes
	);
	void DismissTop();
	void Update(LegoU32 p_elapsedMs);
	void DrawCursors();
	LegoBool32 Initialize(
		MenuScreenCreateParams* p_createParams,
		LegoS32 p_count,
		MenuInputDispatcher* p_inputDispatcher
	);
	LegoU32 GetOpenCount() const { return m_openCount; }

private:
	void CloseTop();

	MenuInputBindingTable m_bindingTable;   // 0x00
	MenuScreenCreateParams m_createParams;  // 0x5c
	DialogScreen* m_entries;                // 0x8c
	MenuInputDispatcher* m_inputDispatcher; // 0x90
	MenuScreen* m_previousScreen;           // 0x94
	LegoS32 m_count;                        // 0x98
	LegoU32 m_openCount;                    // 0x9c
	undefined4 m_lastResult;                // 0xa0
};

#endif // MENUDIALOG_H
