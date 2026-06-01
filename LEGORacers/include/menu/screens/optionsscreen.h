#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/crimsonsun0xa4.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/screens/optionsscreenbase0x51ac.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"

// VTABLE: LEGORACERS 0x004b2b04
// SIZE 0x6750
class OptionsScreen : public OptionsScreenBase0x51ac {
public:
	OptionsScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void Reset() override;                                                             // vtable+0x54
	~OptionsScreen() override;                                                         // vtable+0x68
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c
	void VTable0x98() override;                                                        // vtable+0x98
	void VTable0x9c() override;                                                        // vtable+0x9c
	void VTable0xa0() override;                                                        // vtable+0xa0
	void VTable0xa4() override;                                                        // vtable+0xa4

	// SYNTHETIC: LEGORACERS 0x004755f0
	// OptionsScreen::`scalar deleting destructor'

protected:
	MainMenuScreenFieldAt0x498 m_unk0x51ac;      // 0x51ac
	MainMenuScreenFieldAt0x498 m_unk0x549c;      // 0x549c
	ObscureCarouselNavigator0x94 m_unk0x578c;    // 0x578c
	ObscureBanner0x9f4 m_unk0x5820;              // 0x5820
	CrimsonSun0xa4::FieldAt0x6c8 m_unk0x6214[5]; // 0x6214
	undefined m_unk0x646c[0x1f4];                // 0x646c
	MainMenuScreenFieldAt0x420 m_unk0x6660[2];   // 0x6660
};

#endif // OPTIONSSCREEN_H
