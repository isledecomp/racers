#ifndef SINGLERACESELECTBASE_H
#define SINGLERACESELECTBASE_H

#include "golanimatedentity.h"
#include "golstringtable.h"
#include "menu/screens/menuscenescreen.h"
#include "menu/widgets/menucarousel.h"
#include "menu/widgets/menucarouselnavigator.h"
#include "menu/widgets/menuframe.h"
#include "menu/widgets/menuselector.h"
#include "race/data/circuitdefinitionlist.h"

class GolModelBase;

// VTABLE: LEGORACERS 0x004b3f00
// SIZE 0x1908
class SingleRaceSelectBase : public MenuSceneScreen {
public:
	SingleRaceSelectBase();

	void CreateWidgets() override;                                             // vtable+0x4c
	~SingleRaceSelectBase() override;                                          // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00488820
	// SingleRaceSelectBase::`scalar deleting destructor'

protected:
	void SetPreviewDriver(const LegoChar* p_name);
	void ApplyThemeColor(LegoS32 p_index);

	LegoChar m_driverName[8];                                 // 0x0658
	GolAnimatedEntity m_driverEntity;                         // 0x0660
	GolModelBase* m_driverModel;                              // 0x0754
	MenuFrame m_borderFrame;                                  // 0x0758
	MenuCarouselNavigator m_trackCarousel;                    // 0x0b54
	MenuSelector m_trackSelector;                             // 0x0be8
	MenuImage m_trackIcons[7];                                // 0x15dc
	MenuTriangle m_sceneOverlay;                              // 0x1860
	CircuitDefinitionList::CircuitDefinition* m_circuitEntry; // 0x1904
};

#endif // SINGLERACESELECTBASE_H
