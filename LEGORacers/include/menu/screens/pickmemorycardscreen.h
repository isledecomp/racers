#ifndef PICKMEMORYCARDSCREEN_H
#define PICKMEMORYCARDSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x420.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/widgets/obscureanchor0x5c.h"

// VTABLE: LEGORACERS 0x004b3ad0
// SIZE 0x2548
class PickMemoryCardScreen : public ImaginaryTool0x368 {
public:
	PickMemoryCardScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x4c() override;                                                        // vtable+0x4c
	~PickMemoryCardScreen() override;                                                  // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00484800
	// PickMemoryCardScreen::`scalar deleting destructor'

protected:
	ObscureAnchor0x5c m_unk0x368;           // 0x0368
	ObscureAnchor0x5c m_unk0x3c4;           // 0x03c4
	ObscureAnchor0x5c m_unk0x420;           // 0x0420
	MainMenuScreenFieldAt0x420 m_unk0x47c;  // 0x047c
	MainMenuScreenFieldAt0x498 m_unk0x4f4;  // 0x04f4
	MainMenuScreenFieldAt0x498 m_unk0x7e4;  // 0x07e4
	MainMenuScreenFieldAt0x498 m_unk0xad4;  // 0x0ad4
	MainMenuScreenFieldAt0x498 m_unk0xdc4;  // 0x0dc4
	MainMenuScreenFieldAt0x498 m_unk0x10b4; // 0x10b4
	MainMenuScreenFieldAt0x498 m_unk0x13a4; // 0x13a4
	MainMenuScreenFieldAt0x498 m_unk0x1694; // 0x1694
	MainMenuScreenFieldAt0x498 m_unk0x1984; // 0x1984
	MainMenuScreenFieldAt0x498 m_unk0x1c74; // 0x1c74
	MainMenuScreenFieldAt0x498 m_unk0x1f64; // 0x1f64
	MainMenuScreenFieldAt0x498 m_unk0x2254; // 0x2254
	undefined4 m_unk0x2544;                 // 0x2544
};

#endif // PICKMEMORYCARDSCREEN_H
