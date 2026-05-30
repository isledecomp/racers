#ifndef PICKLANGUAGESCREEN_H
#define PICKLANGUAGESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"

// VTABLE: LEGORACERS 0x004b3a38
// SIZE 0x15ec
class PickLanguageScreen : public ImaginaryTool0x368 {
public:
	PickLanguageScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	~PickLanguageScreen() override;                                                    // vtable+0x68
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484430
	// PickLanguageScreen::`scalar deleting destructor'

protected:
	ObscureAnchor0x5c m_unk0x368;             // 0x0368
	MainMenuScreenFieldAt0x420 m_unk0x3c4;    // 0x03c4
	ObscureBanner0x9f4 m_unk0x43c;            // 0x043c
	ObscureCarouselNavigator0x94 m_unk0xe30;  // 0x0e30
	MainMenuScreenFieldAt0x420 m_unk0xec4[9]; // 0x0ec4
	MainMenuScreenFieldAt0x498 m_unk0x12fc;   // 0x12fc
};

#endif // PICKLANGUAGESCREEN_H
