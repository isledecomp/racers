#ifndef GARAGESCREEN_H
#define GARAGESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/racerpickscreenbase.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menutextbutton.h"

// VTABLE: LEGORACERS 0x004b33dc
// SIZE 0x6410
class GarageScreen : public RacerPickScreenBase {
public:
	GarageScreen();

	void VTable0x38(MenuWidget*) override;                                     // vtable+0x38
	void VTable0x4c() override;                                                // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~GarageScreen() override;                                                  // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                // vtable+0x78
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047e3e0
	// GarageScreen::`scalar deleting destructor'

protected:
	void FUN_0047e550();
	void FUN_0047e600();
	void FUN_0047e740();
	void FUN_0047e900();
	void FUN_0047e950();
	void FUN_0047e9c0();
	void FUN_0047e9f0(MenuGameContext* p_context);
	void FUN_0047ea50();
	void FUN_0047eb20();
	void FUN_0047efe0();

	MenuImage m_unk0x3ff4;      // 0x3ff4
	MenuTextLabel m_unk0x4050;  // 0x4050
	MenuTextButton m_unk0x40c8; // 0x40c8
	MenuTextButton m_unk0x43b8; // 0x43b8
	MenuTextButton m_unk0x46a8; // 0x46a8
	MenuTextButton m_unk0x4998; // 0x4998
	MenuTextButton m_unk0x4c88; // 0x4c88
	MenuTextButton m_unk0x4f78; // 0x4f78
	MenuTextButton m_unk0x5268; // 0x5268
	MenuTextButton m_unk0x5558; // 0x5558
	MenuTextButton m_unk0x5848; // 0x5848
	MenuTextButton m_unk0x5b38; // 0x5b38
	MenuTextButton m_unk0x5e28; // 0x5e28
	MenuTextButton m_unk0x6118; // 0x6118
	undefined4 m_unk0x6408;     // 0x6408
	undefined4 m_unk0x640c;     // 0x640c
};

#endif // GARAGESCREEN_H
