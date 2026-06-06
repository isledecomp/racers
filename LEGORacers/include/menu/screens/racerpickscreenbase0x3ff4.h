#ifndef RACERPICKSCREENBASE0X3FF4_H
#define RACERPICKSCREENBASE0X3FF4_H

#include "compat.h"
#include "decomp.h"
#include "golstring.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/racerpickscreenbase0x270c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"

// VTABLE: LEGORACERS 0x004b3f98
// SIZE 0x3ff4
class RacerPickScreenBase0x3ff4 : public RacerPickScreenBase0x270c {
public:
	RacerPickScreenBase0x3ff4();

	void VTable0x10(ObscureVantage0x58*) override;                                                  // vtable+0x10
	void VTable0x44(ObscureVantage0x58*) override;                                                  // vtable+0x44
	void VTable0x4c() override;                                                                     // vtable+0x4c
	void Reset() override;                                                                          // vtable+0x54
	~RacerPickScreenBase0x3ff4() override;                                                          // vtable+0x68
	LegoBool32 VTable0xa0(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*, undefined4*) override; // vtable+0xa0

	// SYNTHETIC: LEGORACERS 0x00488db0
	// RacerPickScreenBase0x3ff4::`scalar deleting destructor'

protected:
	void FUN_004890c0(undefined4 p_param);

	ObscureCarouselNavigator0x94 m_unk0x270c[2]; // 0x270c
	MainMenuScreenFieldAt0x420 m_unk0x2834[6];   // 0x2834
	GolString m_unk0x2b04[6];                    // 0x2b04
	undefined m_unk0x2b4c[0x2c0c - 0x2b4c];      // 0x2b4c
	ObscureBanner0x9f4 m_unk0x2c0c[2];           // 0x2c0c
};

#endif // RACERPICKSCREENBASE0X3FF4_H
