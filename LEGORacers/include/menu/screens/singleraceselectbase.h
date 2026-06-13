#ifndef SINGLERACESELECTBASE_H
#define SINGLERACESELECTBASE_H

#include "golanimatedentity.h"
#include "golstringtable.h"
#include "menu/screens/menuscenescreen.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menuselector.h"
#include "race/data/circuitdefinitionlist.h"

class GolModelBase;

// VTABLE: LEGORACERS 0x004b3f00
// SIZE 0x1908
class SingleRaceSelectBase : public MenuSceneScreen {
public:
	SingleRaceSelectBase();

	void VTable0x4c() override;                                                // vtable+0x4c
	~SingleRaceSelectBase() override;                                          // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00488820
	// SingleRaceSelectBase::`scalar deleting destructor'

protected:
	void FUN_00488b40(const LegoChar* p_name);
	void FUN_00488cb0(LegoS32 p_index);

	LegoChar m_unk0x658[8];                                // 0x0658
	GolAnimatedEntity m_unk0x660;                          // 0x0660
	GolModelBase* m_unk0x754;                              // 0x0754
	MenuFrame m_unk0x758;                                  // 0x0758
	MenuCarouselNavigator m_unk0xb54;                      // 0x0b54
	MenuSelector m_unk0xbe8;                               // 0x0be8
	MenuImage m_unk0x15dc[7];                              // 0x15dc
	MenuTriangle m_unk0x1860;                              // 0x1860
	CircuitDefinitionList::CircuitDefinition* m_unk0x1904; // 0x1904
};

#endif // SINGLERACESELECTBASE_H
