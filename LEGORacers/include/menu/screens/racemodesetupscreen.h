#ifndef RACEMODESETUPSCREEN_H
#define RACEMODESETUPSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/screens/singleraceselectbase.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"

// VTABLE: LEGORACERS 0x004b3dc8
// SIZE 0x2e60
class RaceModeSetupScreen : public SingleRaceSelectBase {
public:
	RaceModeSetupScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x3c(ObscureIcon0x1a8*) override;                                       // vtable+0x3c
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~RaceModeSetupScreen() override;                                                   // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00487990
	// RaceModeSetupScreen::`scalar deleting destructor'

protected:
	LegoU32 FUN_004246d0(LegoChar* p_buffer, LegoU32 p_time);
	void FUN_00488010();
	void FUN_004881a0();

	ObscureAnchor0x5c m_unk0x1908;                 // 0x1908
	MainMenuScreenFieldAt0x420 m_unk0x1964;        // 0x1964
	MainMenuScreenFieldAt0x498 m_unk0x19dc;        // 0x19dc
	MainMenuScreenFieldAt0x498 m_unk0x1ccc;        // 0x1ccc
	LegoU32 m_unk0x1fbc;                           // 0x1fbc
	ObscureCarouselNavigator0x94 m_unk0x1fc0;      // 0x1fc0
	ObscureBanner0x9f4 m_unk0x2054;                // 0x2054
	MainMenuScreenFieldAt0x420 m_unk0x2a48[4];     // 0x2a48
	MainMenuScreenFieldAt0x420 m_unk0x2c28;        // 0x2c28
	MainMenuScreenFieldAt0x420 m_unk0x2ca0;        // 0x2ca0
	MainMenuScreenFieldAt0x420 m_unk0x2d18;        // 0x2d18
	MainMenuScreenFieldAt0x420 m_unk0x2d90;        // 0x2d90
	LegoU32 m_unk0x2e08;                           // 0x2e08
	LegoU32 m_unk0x2e0c;                           // 0x2e0c
	LegoBool32 m_unk0x2e10;                        // 0x2e10
	undefined2 m_unk0x2e14[(0x2e32 - 0x2e14) / 2]; // 0x2e14
	undefined2 m_unk0x2e32[(0x2e46 - 0x2e32) / 2]; // 0x2e32
	GolString m_unk0x2e48;                         // 0x2e48
	GolString m_unk0x2e54;                         // 0x2e54
};

#endif // RACEMODESETUPSCREEN_H
