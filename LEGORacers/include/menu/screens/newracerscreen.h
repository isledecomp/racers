#ifndef NEWRACERSCREEN_H
#define NEWRACERSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"
#include "menu/screens/mainmenuscreenfieldat0x498.h"
#include "menu/widgets/obscureanchor0x5c.h"

// VTABLE: LEGORACERS 0x004b3818
// SIZE 0x770
class NewRacerScreen : public ImaginaryTool0x368 {
public:
	NewRacerScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x4c() override;                                                        // vtable+0x4c
	~NewRacerScreen() override;                                                        // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00482070
	// NewRacerScreen::`scalar deleting destructor'

protected:
	ObscureAnchor0x5c m_unk0x368;          // 0x368
	ObscureAnchor0x5c m_unk0x3c4;          // 0x3c4
	ObscureAnchor0x5c m_unk0x420;          // 0x420
	MainMenuScreenFieldAt0x498 m_unk0x47c; // 0x47c
	LegoU32 m_unk0x76c;                    // 0x76c
};

#endif // NEWRACERSCREEN_H
