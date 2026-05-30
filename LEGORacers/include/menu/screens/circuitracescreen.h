#ifndef CIRCUITRACESCREEN_H
#define CIRCUITRACESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/singleraceselectbase.h"

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
	undefined m_unk0x1908[0x2228 - 0x1908]; // 0x1908
};

#endif // CIRCUITRACESCREEN_H
