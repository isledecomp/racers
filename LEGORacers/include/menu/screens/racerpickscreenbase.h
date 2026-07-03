#ifndef RACERPICKSCREENBASE_H
#define RACERPICKSCREENBASE_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/racermodelscreenbase.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menuselector.h"
#include "menu/widgets/menutextlabel.h"

// VTABLE: LEGORACERS 0x004b3f98
// SIZE 0x3ff4
class RacerPickScreenBase : public RacerModelScreenBase {
public:
	RacerPickScreenBase();

	void OnCarouselSettled(MenuWidget*) override;                                           // vtable+0x10
	void OnWidgetValueChanged(MenuWidget*) override;                                        // vtable+0x44
	void CreateWidgets() override;                                                          // vtable+0x4c
	void Reset() override;                                                                  // vtable+0x54
	~RacerPickScreenBase() override;                                                        // vtable+0x68
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*, undefined4*) override; // vtable+0xa0

	// SYNTHETIC: LEGORACERS 0x00488db0
	// RacerPickScreenBase::`scalar deleting destructor'

protected:
	void RefreshNameLabels(LegoS32 p_index);
	void RebuildNameCarousel(LegoS32 p_index);
	void ActivateNameSelectors(LegoS32 p_index);
	void EnableNameSelectors(LegoS32 p_index);
	void DisableNameSelectors(LegoS32 p_index);

	MenuCarouselNavigator m_nameCarousels[2]; // 0x270c
	MenuTextLabel m_nameLabels[6];            // 0x2834
	GolString m_nameStrings[6];               // 0x2b04
	undefined2 m_nameBuffers[6][0x10];        // 0x2b4c
	MenuSelector m_nameSelectors[2];          // 0x2c0c
};

#endif // RACERPICKSCREENBASE_H
