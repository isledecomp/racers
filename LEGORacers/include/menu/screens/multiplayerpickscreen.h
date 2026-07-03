#ifndef MULTIPLAYERPICKSCREEN_H
#define MULTIPLAYERPICKSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/racermodelscreenbase.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextlabel.h"
#include "save/inputbindingstate.h"

class InputDevice;

// VTABLE: LEGORACERS 0x004b3774
// SIZE 0x2cc4
class MultiplayerPickScreen : public RacerModelScreenBase {
public:
	MultiplayerPickScreen();

	LegoBool32 HandleKeyDown(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	void CreateWidgets() override;                                                                   // vtable+0x4c
	void Reset() override;                                                                           // vtable+0x54
	~MultiplayerPickScreen() override;                                                               // vtable+0x68
	LegoBool32 Update(undefined4) override;                                                          // vtable+0x78
	void Navigate() override;                                                                        // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override;                       // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x004816f0
	// MultiplayerPickScreen::`scalar deleting destructor'

protected:
	InputDevice* ResolveInputDevice(LegoU32 p_deviceType, LegoU32 p_deviceId);
	void RefreshPlayerDevices();
	void UpdateNameLabel(LegoS32 p_index);
	void DimSlotLighting(LegoS32 p_index);
	void RestoreSlotLighting(LegoS32 p_index);

	MenuImage m_photoImage;                     // 0x270c
	MenuImage m_promptImages[6];                // 0x2768
	MenuTextLabel m_player1Label;               // 0x2990
	MenuTextLabel m_player2Label;               // 0x2a08
	MenuTextLabel m_selectHintLabel;            // 0x2a80
	MenuTextLabel m_backHintLabel;              // 0x2af8
	InputDevice* m_playerDevices[2];            // 0x2b70
	InputBindingState::Entry* m_bindingEntries; // 0x2b78
	GolString m_nameStrings[2];                 // 0x2b7c
	undefined2 m_nameBuffers[2][16];            // 0x2b94
	MenuTextLabel m_nameLabels[2];              // 0x2bd4
};

#endif // MULTIPLAYERPICKSCREEN_H
