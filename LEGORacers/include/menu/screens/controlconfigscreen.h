#ifndef CONTROLCONFIGSCREEN_H
#define CONTROLCONFIGSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"

class InputDevice;

// VTABLE: LEGORACERS 0x004b3160
// SIZE 0x3360
class ControlConfigScreen : public MenuGameScreen {
public:
	ControlConfigScreen();

	LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	LegoBool32 HandleKeyUp(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x1c
	void OnIconFocused(MenuIcon*) override;                                                          // vtable+0x34
	void OnIconUnfocused(MenuWidget*) override;                                                      // vtable+0x38
	void OnWidgetValueChanged(MenuWidget*) override;                                                 // vtable+0x44
	void CreateWidgets() override;                                                                   // vtable+0x4c
	void Reset() override;                                                                           // vtable+0x54
	~ControlConfigScreen() override;                                                                 // vtable+0x68
	LegoBool32 Update(undefined4) override;                                                          // vtable+0x78
	void Navigate() override;                                                                        // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override;                       // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047a690
	// ControlConfigScreen::`scalar deleting destructor'

protected:
	void PopulateDeviceCarousel();
	void RefreshEventTexts();

	InputDevice* m_devices[5];              // 0x0368
	LegoS32 m_bindingIndices[5];            // 0x037c
	MenuIcon* m_awaitingButton;             // 0x0390
	undefined2* m_savedButtonMapping;       // 0x0394
	undefined2* m_savedAxisMapping;         // 0x0398
	LegoU32 m_deviceCount;                  // 0x039c
	LegoS32 m_selectedDevice;               // 0x03a0
	LegoU32 m_playerIndex;                  // 0x03a4
	MenuImage m_photoImage;                 // 0x03a8
	MenuTextLabel m_infoLabel;              // 0x0404
	MenuTextButton m_backButton;            // 0x047c
	undefined2 m_ellipsisText[9];           // 0x076c
	undefined m_unk0x77e[0x780 - 0x77e];    // 0x077e
	MenuCarouselNavigator m_deviceCarousel; // 0x0780
	MenuSelector m_deviceSelector;          // 0x0814
	MenuImage m_deviceIcons[5];             // 0x1208
	MenuTextLabel m_deviceLabel;            // 0x13d4
	MenuTextButton m_eventButtons[9];       // 0x144c
	MenuTextLabel m_eventLabels[9];         // 0x2ebc
	GolString m_eventTexts[9];              // 0x32f4
};

#endif // CONTROLCONFIGSCREEN_H
