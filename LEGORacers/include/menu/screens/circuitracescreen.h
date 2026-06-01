#ifndef CIRCUITRACESCREEN_H
#define CIRCUITRACESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/menuanimationlist.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/screens/singleraceselectbase.h"
#include "menu/widgets/obscureanchor0x5c.h"

// VTABLE: LEGORACERS 0x004b30c8
// SIZE 0x2228
class CircuitRaceScreen : public SingleRaceSelectBase {
public:
	CircuitRaceScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~CircuitRaceScreen() override;                                                     // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00479e50
	//  CircuitRaceScreen::`scalar deleting destructor'

protected:
	void FUN_0047a2b0();

	ObscureAnchor0x5c m_unk0x1908;          // 0x1908
	MainMenuScreenFieldAt0x420 m_unk0x1964; // 0x1964
	MainMenuScreenFieldAt0x420 m_unk0x19dc; // 0x19dc
	MainMenuScreenFieldAt0x420 m_unk0x1a54; // 0x1a54
	MainMenuScreenFieldAt0x420 m_unk0x1acc; // 0x1acc
	MainMenuScreenFieldAt0x420 m_unk0x1b44; // 0x1b44
	MainMenuScreenFieldAt0x420 m_unk0x1bbc; // 0x1bbc
	MainMenuScreenFieldAt0x498 m_unk0x1c34; // 0x1c34
	MainMenuScreenFieldAt0x498 m_unk0x1f24; // 0x1f24
	MenuAnimationList::Entry* m_unk0x2214;  // 0x2214
	LegoU32 m_unk0x2218;                    // 0x2218
	LegoU32 m_unk0x221c;                    // 0x221c
	LegoU32 m_unk0x2220;                    // 0x2220
	LegoBool32 m_unk0x2224;                 // 0x2224
};

#endif // CIRCUITRACESCREEN_H
