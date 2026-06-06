#ifndef PICKRACERSCREEN_H
#define PICKRACERSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/screens/racerpickscreenbase0x3ff4.h"
#include "menu/widgets/obscureanchor0x5c.h"

// VTABLE: LEGORACERS 0x004b3b68
// SIZE 0x4c8c
class PickRacerScreen : public RacerPickScreenBase0x3ff4 {
public:
	PickRacerScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	~PickRacerScreen() override;                                                       // vtable+0x68
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484cc0
	// PickRacerScreen::`scalar deleting destructor'

protected:
	ObscureAnchor0x5c m_unk0x3ff4;          // 0x3ff4
	MainMenuScreenFieldAt0x420 m_unk0x4050; // 0x4050
	MainMenuScreenFieldAt0x498 m_unk0x40c8; // 0x40c8
	MainMenuScreenFieldAt0x498 m_unk0x43b8; // 0x43b8
	MainMenuScreenFieldAt0x498 m_unk0x46a8; // 0x46a8
	MainMenuScreenFieldAt0x498 m_unk0x4998; // 0x4998
	undefined4 m_unk0x4c88;                 // 0x4c88
};

#endif // PICKRACERSCREEN_H
