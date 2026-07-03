#ifndef SAVELOADSCREEN_H
#define SAVELOADSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/menudialog.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextbutton.h"

class SaveSystem;

// VTABLE: LEGORACERS 0x004b3d1c
// SIZE 0x1d7c
class SaveLoadScreen : public MenuGameScreen {
public:
	SaveLoadScreen();

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void CreateWidgets() override;                                             // vtable+0x4c
	~SaveLoadScreen() override;                                                // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	LegoBool32 Update(undefined4) override;                                    // vtable+0x78
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00486c80
	// SaveLoadScreen::`scalar deleting destructor'

protected:
	void ExecuteOperation(SaveSystem* p_source);

	LegoS32 m_status;                   // 0x0368
	LegoU32 m_requestMenuId;            // 0x036c
	LegoS32 m_saveIndex;                // 0x0370
	LegoBool32 m_widgetsDirty;          // 0x0374
	LegoBool32 m_skipFirstStatus;       // 0x0378
	MenuImage m_photoImage;             // 0x037c
	MenuImage m_statusPanelImage;       // 0x03d8
	MenuImage m_statusIconImage;        // 0x0434
	MenuDialog::TextLine m_statusLine1; // 0x0490
	MenuDialog::TextLine m_statusLine2; // 0x0508
	MenuDialog::TextLine m_statusLine3; // 0x0580
	MenuTextButton m_slot0Button;       // 0x05f8
	MenuTextButton m_slot1Button;       // 0x08e8
	MenuTextButton m_slot2Button;       // 0x0bd8
	MenuTextButton m_slot3Button;       // 0x0ec8
	MenuTextButton m_cancelButton;      // 0x11b8
	MenuTextButton m_yesButton;         // 0x14a8
	MenuTextButton m_noButton;          // 0x1798
	MenuTextButton m_okButton;          // 0x1a88
	undefined4 m_unk0x1d78;             // 0x1d78
};

#endif // SAVELOADSCREEN_H
