#ifndef EDITCARSCREEN_H
#define EDITCARSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golanimatedentity.h"
#include "golname.h"
#include "menu/screens/awardcinematicscreen.h"
#include "menu/screens/menugamescreen.h"
#include "menu/screens/racermodelslot.h"
#include "menu/screens/racerunlockstate.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuframedsceneview.h"
#include "menu/widgets/menuimage.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextbutton.h"
#include "menu/widgets/menutextlabel.h"
#include "save/savegame.h"

class CmbModelPart0x34;
class GolModelBase;
class GolSceneNode;

// VTABLE: LEGORACERS 0x004b3294
// SIZE 0x36c4
class EditCarScreen : public MenuGameScreen {
public:
	EditCarScreen();

	void VTable0x38(MenuWidget*) override;                                     // vtable+0x38
	void VTable0x44(MenuWidget*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                // vtable+0x4c
	void Reset() override;                                                     // vtable+0x54
	~EditCarScreen() override;                                                 // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	void VTable0x80() override;                                                // vtable+0x80
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047bde0
	// EditCarScreen::`scalar deleting destructor'

protected:
	void FUN_0047bfc0();
	void FUN_0047c080();
	void FUN_0047c320();
	void FUN_0047c400(MenuGameContext* p_context, MenuScreenCreateParams* p_createParams);
	void FUN_0047c450();
	void FUN_0047c5a0();
	void FUN_0047c610();
	void FUN_0047c720();
	void FUN_0047c790();
	void FUN_0047c810();
	LegoBool32 FUN_0047c900();
	void FUN_0047cde0();

	MenuImage m_unk0x368;                               // 0x0368
	MenuTextLabel m_unk0x3c4;                           // 0x03c4
	MenuFramedSceneView m_unk0x43c;                     // 0x043c
	MenuTextButton m_unk0x914;                          // 0x0914
	MenuTextButton m_unk0xc04;                          // 0x0c04
	MenuTextButton m_unk0xef4;                          // 0x0ef4
	MenuTextButton m_unk0x11e4;                         // 0x11e4
	MenuTextButton m_unk0x14d4;                         // 0x14d4
	MenuTextButton m_unk0x17c4;                         // 0x17c4
	MenuTextButton m_unk0x1ab4;                         // 0x1ab4
	MenuTextButton m_unk0x1da4;                         // 0x1da4
	MenuTextButton m_unk0x2094;                         // 0x2094
	MenuCarouselNavigator m_unk0x2384;                  // 0x2384
	MenuSelector m_unk0x2418;                           // 0x2418
	MenuImage m_unk0x2e0c[12];                          // 0x2e0c
	LegoU8 m_unk0x325c[0x202];                          // 0x325c
	undefined m_padding0x345e[0x3460 - 0x345e];         // 0x345e
	AwardCinematicScreen::SceneEntityGroup m_unk0x3460; // 0x3460
	GolAnimatedEntity m_unk0x34b0;                      // 0x34b0
	GolModelBase* m_unk0x35a4;                          // 0x35a4
	GolSceneNode* m_unk0x35a8;                          // 0x35a8
	CmbModelPart0x34* m_unk0x35ac;                      // 0x35ac
	RacerModelSlot m_unk0x35b0;                         // 0x35b0
	RacerUnlockState m_unk0x3650;                       // 0x3650
	ActiveRecordBuffer* m_unk0x3678;                    // 0x3678
	GolName m_unk0x367c;                                // 0x367c
	LegoU32 m_unk0x3684;                                // 0x3684
	LegoU32 m_unk0x3688[12];                            // 0x3688
	undefined m_padding0x36b8[0x36c0 - 0x36b8];         // 0x36b8
	LegoBool32 m_unk0x36c0;                             // 0x36c0
};

#endif // EDITCARSCREEN_H
