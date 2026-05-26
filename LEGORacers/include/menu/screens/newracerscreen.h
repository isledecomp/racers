#ifndef NEWRACERSCREEN_H
#define NEWRACERSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"

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
	undefined m_unk0x368[0x770 - 0x368]; // 0x368
};

#endif // NEWRACERSCREEN_H
