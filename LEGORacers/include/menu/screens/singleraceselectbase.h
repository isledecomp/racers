#ifndef SINGLERACESELECTBASE_H
#define SINGLERACESELECTBASE_H

#include "golstringtable.h"
#include "menu/screens/imaginarychisel0x658.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"
#include "menu/widgets/obscuretome0x3fc.h"
#include "race/data/racedefinitionlist.h"
#include "util/opalhaven0xf4.h"

// VTABLE: LEGORACERS 0x004b3f00
// SIZE 0x1908
class SingleRaceSelectBase : public ImaginaryChisel0x658 {
public:
	SingleRaceSelectBase();

	void VTable0x4c() override;                                                        // vtable+0x4c
	~SingleRaceSelectBase() override;                                                  // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00488820
	// SingleRaceSelectBase::`scalar deleting destructor'

protected:
	void FUN_00488b40(const LegoChar* p_name);
	void FUN_00488cb0(LegoS32 p_index);

	LegoChar m_unk0x658[8];                          // 0x0658
	OpalHaven0xf4 m_unk0x660;                        // 0x0660
	undefined4 m_unk0x754;                           // 0x0754
	ObscureTome0x3fc m_unk0x758;                     // 0x0758
	ObscureCarouselNavigator0x94 m_unk0xb54;         // 0x0b54
	ObscureBanner0x9f4 m_unk0xbe8;                   // 0x0be8
	ObscureAnchor0x5c m_unk0x15dc[7];                // 0x15dc
	ObscureZebra0xa4 m_unk0x1860;                    // 0x1860
	RaceDefinitionList::RaceDefinition* m_unk0x1904; // 0x1904
};

#endif // SINGLERACESELECTBASE_H
