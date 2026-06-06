#ifndef EDITCARSCREEN_H
#define EDITCARSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golname.h"
#include "menu/screens/awardcinematicscreen.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/screens/racerpickmodelslot0xa0.h"
#include "menu/screens/racerpickmodelstate0x28.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"
#include "menu/widgets/obscurerune0x4d8.h"
#include "save/peridottrace0x4e0.h"
#include "util/opalhaven0xf4.h"

class CmbModelPart0x34;
class GolModelBase;
class GolSceneNode;

// VTABLE: LEGORACERS 0x004b3294
// SIZE 0x36c4
class EditCarScreen : public ImaginaryTool0x368 {
public:
	EditCarScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~EditCarScreen() override;                                                         // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	void VTable0x80() override;                                                        // vtable+0x80
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047bde0
	// EditCarScreen::`scalar deleting destructor'

protected:
	void FUN_0047bfc0();
	void FUN_0047c080();
	void FUN_0047c320();
	void FUN_0047c400(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams);
	void FUN_0047c450();
	void FUN_0047c5a0();
	void FUN_0047c610();
	void FUN_0047c720();
	void FUN_0047c790();
	void FUN_0047c810();
	LegoBool32 FUN_0047c900();
	void FUN_0047cde0();

	ObscureAnchor0x5c m_unk0x368;                   // 0x0368
	MainMenuScreenFieldAt0x420 m_unk0x3c4;          // 0x03c4
	ObscureRune0x4d8 m_unk0x43c;                    // 0x043c
	MainMenuScreenFieldAt0x498 m_unk0x914;          // 0x0914
	MainMenuScreenFieldAt0x498 m_unk0xc04;          // 0x0c04
	MainMenuScreenFieldAt0x498 m_unk0xef4;          // 0x0ef4
	MainMenuScreenFieldAt0x498 m_unk0x11e4;         // 0x11e4
	MainMenuScreenFieldAt0x498 m_unk0x14d4;         // 0x14d4
	MainMenuScreenFieldAt0x498 m_unk0x17c4;         // 0x17c4
	MainMenuScreenFieldAt0x498 m_unk0x1ab4;         // 0x1ab4
	MainMenuScreenFieldAt0x498 m_unk0x1da4;         // 0x1da4
	MainMenuScreenFieldAt0x498 m_unk0x2094;         // 0x2094
	ObscureCarouselNavigator0x94 m_unk0x2384;       // 0x2384
	ObscureBanner0x9f4 m_unk0x2418;                 // 0x2418
	ObscureAnchor0x5c m_unk0x2e0c[12];              // 0x2e0c
	LegoU8 m_unk0x325c[0x202];                      // 0x325c
	undefined m_padding0x345e[0x3460 - 0x345e];     // 0x345e
	AwardCinematicScreen::FieldAt0x658 m_unk0x3460; // 0x3460
	OpalHaven0xf4 m_unk0x34b0;                      // 0x34b0
	GolModelBase* m_unk0x35a4;                      // 0x35a4
	GolSceneNode* m_unk0x35a8;                      // 0x35a8
	CmbModelPart0x34* m_unk0x35ac;                  // 0x35ac
	RacerPickModelSlot0xa0 m_unk0x35b0;             // 0x35b0
	RacerPickModelState0x28 m_unk0x3650;            // 0x3650
	PeridotTraceBuffer0x250* m_unk0x3678;           // 0x3678
	GolName m_unk0x367c;                            // 0x367c
	LegoU32 m_unk0x3684;                            // 0x3684
	LegoU32 m_unk0x3688[12];                        // 0x3688
	undefined m_padding0x36b8[0x36c0 - 0x36b8];     // 0x36b8
	LegoBool32 m_unk0x36c0;                         // 0x36c0
};

#endif // EDITCARSCREEN_H
