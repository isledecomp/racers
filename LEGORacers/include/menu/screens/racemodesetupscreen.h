#ifndef RACEMODESETUPSCREEN_H
#define RACEMODESETUPSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/singleraceselectbase.h"
#include "menu/widgets/obscureanchor0x5c.h"

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
	ObscureAnchor0x5c m_unk0x1908;          // 0x1908
	undefined m_unk0x1964[0x2e60 - 0x1964]; // 0x1964
};

#endif // RACEMODESETUPSCREEN_H
