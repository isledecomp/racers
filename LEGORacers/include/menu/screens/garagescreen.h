#ifndef GARAGESCREEN_H
#define GARAGESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/screens/racerpickscreenbase0x3ff4.h"
#include "menu/widgets/obscureanchor0x5c.h"

// VTABLE: LEGORACERS 0x004b33dc
// SIZE 0x6410
class GarageScreen : public RacerPickScreenBase0x3ff4 {
public:
	GarageScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~GarageScreen() override;                                                          // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047e3e0
	// GarageScreen::`scalar deleting destructor'

protected:
	void FUN_0047e550();
	void FUN_0047e600();
	void FUN_0047e740();
	void FUN_0047e900();
	void FUN_0047e950();
	void FUN_0047e9c0();
	void FUN_0047e9f0(MenuToolContext0x4bc8* p_context);
	void FUN_0047ea50();
	void FUN_0047eb20();
	void FUN_0047efe0();

	ObscureAnchor0x5c m_unk0x3ff4;          // 0x3ff4
	MainMenuScreenFieldAt0x420 m_unk0x4050; // 0x4050
	MainMenuScreenFieldAt0x498 m_unk0x40c8; // 0x40c8
	MainMenuScreenFieldAt0x498 m_unk0x43b8; // 0x43b8
	MainMenuScreenFieldAt0x498 m_unk0x46a8; // 0x46a8
	MainMenuScreenFieldAt0x498 m_unk0x4998; // 0x4998
	MainMenuScreenFieldAt0x498 m_unk0x4c88; // 0x4c88
	MainMenuScreenFieldAt0x498 m_unk0x4f78; // 0x4f78
	MainMenuScreenFieldAt0x498 m_unk0x5268; // 0x5268
	MainMenuScreenFieldAt0x498 m_unk0x5558; // 0x5558
	MainMenuScreenFieldAt0x498 m_unk0x5848; // 0x5848
	MainMenuScreenFieldAt0x498 m_unk0x5b38; // 0x5b38
	MainMenuScreenFieldAt0x498 m_unk0x5e28; // 0x5e28
	MainMenuScreenFieldAt0x498 m_unk0x6118; // 0x6118
	undefined4 m_unk0x6408;                 // 0x6408
	undefined4 m_unk0x640c;                 // 0x640c
};

#endif // GARAGESCREEN_H
