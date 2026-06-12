#ifndef MULTIPLAYERPICKSCREEN_H
#define MULTIPLAYERPICKSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/racermodelscreenbase.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextlabel.h"

class InputDevice;
struct InputBindingEntry;

// VTABLE: LEGORACERS 0x004b3774
// SIZE 0x2cc4
class MultiplayerPickScreen : public RacerModelScreenBase {
public:
	MultiplayerPickScreen();

	LegoBool32 VTable0x18(MenuWidget*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	void VTable0x4c() override;                                                                   // vtable+0x4c
	void Reset() override;                                                                        // vtable+0x54
	~MultiplayerPickScreen() override;                                                            // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                                   // vtable+0x78
	void VTable0x84() override;                                                                   // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override;                    // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x004816f0
	// MultiplayerPickScreen::`scalar deleting destructor'

protected:
	InputDevice* FUN_00481960(LegoU32 p_deviceType, LegoU32 p_deviceId);
	void FUN_004819b0();
	void FUN_00481b10(LegoS32 p_index);
	void FUN_00481b60(LegoS32 p_index);
	void FUN_00481bf0(LegoS32 p_index);

	MenuImage m_unk0x270c;          // 0x270c
	MenuImage m_unk0x2768[6];       // 0x2768
	MenuTextLabel m_unk0x2990;      // 0x2990
	MenuTextLabel m_unk0x2a08;      // 0x2a08
	MenuTextLabel m_unk0x2a80;      // 0x2a80
	MenuTextLabel m_unk0x2af8;      // 0x2af8
	InputDevice* m_unk0x2b70[2];    // 0x2b70
	InputBindingEntry* m_unk0x2b78; // 0x2b78
	GolString m_unk0x2b7c[2];       // 0x2b7c
	undefined2 m_unk0x2b94[2][16];  // 0x2b94
	MenuTextLabel m_unk0x2bd4[2];   // 0x2bd4
};

#endif // MULTIPLAYERPICKSCREEN_H
