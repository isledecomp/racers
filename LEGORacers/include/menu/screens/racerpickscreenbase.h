#ifndef RACERPICKSCREENBASE_H
#define RACERPICKSCREENBASE_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/racermodelscreenbase.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b3f98
// SIZE 0x3ff4
class RacerPickScreenBase : public RacerModelScreenBase {
public:
	RacerPickScreenBase();

	void VTable0x10(MenuWidget*) override;                                                  // vtable+0x10
	void VTable0x44(MenuWidget*) override;                                                  // vtable+0x44
	void VTable0x4c() override;                                                             // vtable+0x4c
	void Reset() override;                                                                  // vtable+0x54
	~RacerPickScreenBase() override;                                                        // vtable+0x68
	LegoBool32 VTable0xa0(MenuGameContext*, MenuScreenCreateParams*, undefined4*) override; // vtable+0xa0

	// SYNTHETIC: LEGORACERS 0x00488db0
	// RacerPickScreenBase::`scalar deleting destructor'

protected:
	void FUN_00489050(LegoS32 p_index);
	void FUN_004890c0(LegoS32 p_index);
	void FUN_004891f0(LegoS32 p_index);
	void FUN_00489250(LegoS32 p_index);
	void FUN_00489320(LegoS32 p_index);

	MenuCarouselNavigator m_unk0x270c[2]; // 0x270c
	MenuTextLabel m_unk0x2834[6];         // 0x2834
	GolString m_unk0x2b04[6];             // 0x2b04
	undefined2 m_unk0x2b4c[6][0x10];      // 0x2b4c
	MenuSelector m_unk0x2c0c[2];          // 0x2c0c
};

#endif // RACERPICKSCREENBASE_H
