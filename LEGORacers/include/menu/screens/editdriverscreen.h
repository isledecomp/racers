#ifndef EDITDRIVERSCREEN_H
#define EDITDRIVERSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b332c
// SIZE 0x4774
class EditDriverScreen : public ImaginaryTool0x368 {
public:
	EditDriverScreen();

	undefined4 VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override;                                        // vtable+0x18
	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~EditDriverScreen() override;                                                      // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x88() override;                                                  // vtable+0x88
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047cf70
	// EditDriverScreen::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x4774 - 0x368]; // 0x0368
};

#endif // EDITDRIVERSCREEN_H
