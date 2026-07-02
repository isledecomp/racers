#ifndef DRIVERLICENSESCREEN_H
#define DRIVERLICENSESCREEN_H

#include "app/cheatflags.h"
#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/mainmenumodelslot.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuclippedimage.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menuframedsceneview.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextentry.h"
#include "menu/widgets/menutextlabel.h"
#include "racer/drivercosmetics.h"

// VTABLE: LEGORACERS 0x004b31f8
// SIZE 0x23bc
class DriverLicenseScreen : public MenuGameScreen {
public:
	DriverLicenseScreen();

	void OnIconUnfocused(MenuWidget*) override;                                // vtable+0x38
	void OnIconSelected(MenuIcon*) override;                                   // vtable+0x3c
	void OnIconDeselected(MenuIcon*) override;                                 // vtable+0x40
	void OnWidgetValueChanged(MenuWidget*) override;                           // vtable+0x44
	void CreateWidgets() override;                                             // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~DriverLicenseScreen() override;                                           // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c
	void OnChar(undefined4) override;                                          // vtable+0x90
	void VTable0x94(undefined4) override;                                      // vtable+0x94

	void ApplyCheatCode();

	// SYNTHETIC: LEGORACERS 0x0047b070
	// DriverLicenseScreen::`scalar deleting destructor'

protected:
	void CreateDriverScene();
	LegoBool32 HasUnsavedChanges();
	void LoadLicenseData();
	void SaveLicenseData();
	undefined2* GetNameBuffer() { return m_nameEntry.GetEntryBuffer(); }
	DriverCosmetics& GetCosmetics() { return *m_nameEntry.GetCosmetics(); }

	enum {
		c_cheatBufferLength = 14,
		c_cheatBufferStorageLength = c_cheatBufferLength + 1
	};

	MenuClippedImage m_photoImage;     // 0x0368
	MenuImage m_licenseImage;          // 0x03e4
	MenuImage m_trophyImages[8];       // 0x0440
	MenuTextLabel m_infoLabel;         // 0x0720
	MenuTextButton m_expressionButton; // 0x0798
	MenuTextButton m_backButton;       // 0x0a88
	MenuTextButton m_doneButton;       // 0x0d78
	MenuTextButton m_confirmYesButton; // 0x1068
	MenuTextButton m_confirmNoButton;  // 0x1358
	MenuFramedSceneView m_sceneView;   // 0x1648
	MenuFrame m_nameFieldFrame;        // 0x1b20
	MenuTextEntry m_nameEntry;         // 0x1f1c
	MainMenuModelSlot m_modelSlot;     // 0x224c
	GolString m_nameString;            // 0x23a8
	LegoBool32 m_unk0x23b4;            // 0x23b4
	LegoBool32 m_savePending;          // 0x23b8
};

#endif // DRIVERLICENSESCREEN_H
