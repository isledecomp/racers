#ifndef EDITDRIVERSCREEN_H
#define EDITDRIVERSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x22dc.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/widgets/maroonatoll0x170.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurerune0x4d8.h"
#include "racer/turquoiseglowcolor.h"
#include "util/tealcrucible0x50.h"

// VTABLE: LEGORACERS 0x004b332c
// SIZE 0x4774
class EditDriverScreen : public ImaginaryTool0x368 {
public:
	EditDriverScreen();

	LegoBool32 VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x18
	void VTable0x38(ObscureVantage0x58*) override;                                                        // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                                        // vtable+0x44
	void VTable0x4c() override;                                                                           // vtable+0x4c
	void Reset() override;                                                                                // vtable+0x54
	~EditDriverScreen() override;                                                                         // vtable+0x68
	LegoBool32 Destroy() override;                                                                        // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                                           // vtable+0x78
	void VTable0x84() override;                                                                           // vtable+0x84
	LegoBool32 VTable0x88() override;                                                                     // vtable+0x88
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override;                    // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047cf70
	// EditDriverScreen::`scalar deleting destructor'

protected:
	void FUN_0047d100(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams);
	LegoBool32 FUN_0047d170(MaroonAtoll0x170* p_unk0x04, undefined2 p_unk0x08, undefined2 p_unk0x0c, LegoU32 p_unk0x10);
	void FUN_0047d230();
	LegoBool32 FUN_0047d560();
	LegoS32 FUN_0047d5d0();
	void FUN_0047d6f0();
	void FUN_0047d740();
	void FUN_0047d840();
	void FUN_0047d8e0();
	void FUN_0047d940();

	ObscureAnchor0x5c m_unk0x368;            // 0x0368
	ObscureAnchor0x5c m_unk0x3c4;            // 0x03c4
	MaroonAtoll0x170 m_unk0x420[4];          // 0x0420
	ObscureBanner0x9f4 m_unk0x9e0[4];        // 0x09e0
	ObscureRune0x4d8 m_unk0x31b0;            // 0x31b0
	MainMenuScreenFieldAt0x420 m_unk0x3688;  // 0x3688
	MainMenuScreenFieldAt0x498 m_unk0x3700;  // 0x3700
	MainMenuScreenFieldAt0x498 m_unk0x39f0;  // 0x39f0
	MainMenuScreenFieldAt0x498 m_unk0x3ce0;  // 0x3ce0
	MainMenuScreenFieldAt0x498 m_unk0x3fd0;  // 0x3fd0
	MainMenuScreenFieldAt0x498 m_unk0x42c0;  // 0x42c0
	TealCrucible0x50 m_unk0x45b0;            // 0x45b0
	MainMenuScreenFieldAt0x22dc m_unk0x4600; // 0x4600
	TurquoiseGlowColor m_driverColor;        // 0x475c
	undefined m_unk0x4761[0x4764 - 0x4761];  // 0x4761
	LegoU32 m_unk0x4764;                     // 0x4764
	LegoU16 m_unk0x4768;                     // 0x4768
	undefined m_unk0x476a[0x476c - 0x476a];  // 0x476a
	LegoU32 m_unk0x476c;                     // 0x476c
	LegoU32 m_unk0x4770;                     // 0x4770
};

#endif // EDITDRIVERSCREEN_H
