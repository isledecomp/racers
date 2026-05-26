#ifndef PICKMEMORYCARDSCREEN_H
#define PICKMEMORYCARDSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"

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
	undefined m_unk0x368[0x2548 - 0x368]; // 0x0368
};

#endif // PICKMEMORYCARDSCREEN_H
