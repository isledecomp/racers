#ifndef OPTIONSSCREENBASE0X51AC_H
#define OPTIONSSCREENBASE0X51AC_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/widgets/obscureanchor0x5c.h"
#include "menu/widgets/obscurebanner0x5ec.h"
#include "menu/widgets/obscurecarousel0x78.h"
#include "menu/widgets/optionsscreenfieldat0x4178.h"

class GameState;

// VTABLE: LEGORACERS 0x004b3920
// SIZE 0x51ac
class OptionsScreenBase0x51ac : public ImaginaryTool0x368 {
public:
	OptionsScreenBase0x51ac();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~OptionsScreenBase0x51ac() override;                                               // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c
	virtual void VTable0x98();                                                         // vtable+0x98
	virtual void VTable0x9c();                                                         // vtable+0x9c
	virtual void VTable0xa0();                                                         // vtable+0xa0
	virtual void VTable0xa4();                                                         // vtable+0xa4

	// SYNTHETIC: LEGORACERS 0x00482bc0
	// OptionsScreenBase0x51ac::`scalar deleting destructor'

protected:
	void FUN_00482e00();
	void FUN_00482e40();
	void FUN_00482ef0();
	void FUN_00483030();

	LegoBool m_unk0x368;                       // 0x0368
	LegoBool m_unk0x369;                       // 0x0369
	undefined m_unk0x36a[0x36c - 0x36a];       // 0x036a
	undefined4 m_unk0x36c;                     // 0x036c
	GameState* m_unk0x370;                     // 0x0370
	ObscureAnchor0x5c m_unk0x374;              // 0x0374
	MainMenuScreenFieldAt0x420 m_unk0x3d0;     // 0x03d0
	MainMenuScreenFieldAt0x498 m_unk0x448;     // 0x0448
	MainMenuScreenFieldAt0x498 m_unk0x738;     // 0x0738
	MainMenuScreenFieldAt0x498 m_unk0xa28;     // 0x0a28
	MainMenuScreenFieldAt0x498 m_unk0xd18;     // 0x0d18
	MainMenuScreenFieldAt0x498 m_unk0x1008;    // 0x1008
	MainMenuScreenFieldAt0x498 m_unk0x12f8;    // 0x12f8
	MainMenuScreenFieldAt0x498 m_unk0x15e8;    // 0x15e8
	MainMenuScreenFieldAt0x498 m_unk0x18d8;    // 0x18d8
	ObscureBanner0x9f4 m_unk0x1bc8;            // 0x1bc8
	ObscureBanner0x9f4 m_unk0x25bc;            // 0x25bc
	ObscureCarouselNavigator0x94 m_unk0x2fb0;  // 0x2fb0
	ObscureCarouselNavigator0x94 m_unk0x3044;  // 0x3044
	MainMenuScreenFieldAt0x420 m_unk0x30d8[6]; // 0x30d8
	MainMenuScreenFieldAt0x420 m_unk0x33a8[5]; // 0x33a8
	MainMenuScreenFieldAt0x420 m_unk0x3600[2]; // 0x3600
	ObscureBanner0x9f4 m_unk0x36f0;            // 0x36f0
	ObscureCarouselNavigator0x94 m_unk0x40e4;  // 0x40e4
	OptionsScreenFieldAt0x4178 m_unk0x4178;    // 0x4178
	OptionsScreenFieldAt0x4178 m_unk0x4864;    // 0x4864
	MainMenuScreenFieldAt0x420 m_unk0x4f50;    // 0x4f50
	MainMenuScreenFieldAt0x420 m_unk0x4fc8;    // 0x4fc8
	MainMenuScreenFieldAt0x420 m_unk0x5040[3]; // 0x5040
	undefined4 m_unk0x51a8;                    // 0x51a8
};

#endif // OPTIONSSCREENBASE0X51AC_H
