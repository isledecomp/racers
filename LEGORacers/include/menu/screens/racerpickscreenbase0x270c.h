#ifndef RACERPICKSCREENBASE0X270C_H
#define RACERPICKSCREENBASE0X270C_H

#include "cmbmodelpart0x34.h"
#include "compat.h"
#include "decomp.h"
#include "golmodelentity.h"
#include "menu/screens/awardcinematicscreen.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/racerpickmodelslot0xa0.h"
#include "menu/screens/racerpickmodelstate0x28.h"
#include "menu/widgets/obscurerune0x4d8.h"
#include "util/opalhaven0xf4.h"

class GolModelBase;
class GolSceneNode;

// VTABLE: LEGORACERS 0x004b3c78
// SIZE 0x270c
class RacerPickScreenBase0x270c : public ImaginaryTool0x368 {
public:
	RacerPickScreenBase0x270c();

	void VTable0x4c() override;                                                                    // vtable+0x4c
	void Reset() override;                                                                         // vtable+0x54
	~RacerPickScreenBase0x270c() override;                                                         // vtable+0x68
	LegoBool32 Destroy() override;                                                                 // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                                    // vtable+0x78
	void VTable0x80() override;                                                                    // vtable+0x80
	LegoBool32 VTable0x88() override;                                                              // vtable+0x88
	virtual void VTable0x98();                                                                     // vtable+0x98
	virtual void VTable0x9c();                                                                     // vtable+0x9c
	virtual LegoBool32 VTable0xa0(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*, undefined4*); // vtable+0xa0

	// SYNTHETIC: LEGORACERS 0x004859e0
	// RacerPickScreenBase0x270c::`scalar deleting destructor'

protected:
	void FUN_00486250(LegoS32 p_index);
	void FUN_00486400(LegoS32 p_index);
	void FUN_004864a0(LegoS32 p_index);
	void FUN_004864f0(LegoS32 p_index);
	void FUN_004866e0(LegoS32 p_index);

	CmbModelPart0x34 m_modelParts;                    // 0x0368
	AwardCinematicScreen::FieldAt0x658 m_unk0x39c[4]; // 0x039c
	GolSceneNode* m_unk0x4dc[4];                      // 0x04dc
	GolModelBase* m_unk0x4ec[4];                      // 0x04ec
	GolModelEntity m_unk0x4fc[4];                     // 0x04fc
	GolModelBase* m_unk0x73c[4];                      // 0x073c
	LegoFloat m_unk0x74c;                             // 0x074c
	undefined4 m_unk0x750;                            // 0x0750
	undefined4 m_unk0x754;                            // 0x0754
	undefined4 m_unk0x758;                            // 0x0758
	undefined4 m_unk0x75c;                            // 0x075c
	LegoFloat m_unk0x760;                             // 0x0760
	undefined4 m_unk0x764;                            // 0x0764
	undefined4 m_unk0x768;                            // 0x0768
	LegoBool32 m_unk0x76c[2];                         // 0x076c
	LegoBool32 m_unk0x774[2];                         // 0x0774
	LegoS32 m_unk0x77c;                               // 0x077c
	LegoS32 m_unk0x780[2];                            // 0x0780
	undefined m_unk0x788[0x98c - 0x788];              // 0x0788
	ObscureRune0x4d8 m_unk0x98c[4];                   // 0x098c
	MainMenuScreenFieldAt0x420 m_unk0x1cec[2];        // 0x1cec
	RacerPickModelSlot0xa0 m_unk0x1ddc[4];            // 0x1ddc
	RacerPickModelSlot0xa0 m_unk0x205c[4];            // 0x205c
	RacerPickModelState0x28 m_unk0x22dc[2];           // 0x22dc
	OpalHaven0xf4 m_unk0x232c[4];                     // 0x232c
	LegoS32 m_unk0x26fc;                              // 0x26fc
	LegoS32 m_unk0x2700;                              // 0x2700
	undefined4 m_unk0x2704[2];                        // 0x2704
};

#endif // RACERPICKSCREENBASE0X270C_H
