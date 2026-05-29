#ifndef CONTROLCONFIGSCREEN_H
#define CONTROLCONFIGSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3160
// SIZE 0x3360
class ControlConfigScreen : public ImaginaryTool0x368 {
public:
	ControlConfigScreen();

	undefined4 VTable0x18(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override; // vtable+0x18
	undefined4 VTable0x1c(ObscureVantage0x58*, InputEventQueue::Event*, undefined4,
						  undefined4) override;                                        // vtable+0x1c
	void VTable0x34(ObscureIcon0x1a8*) override;                                       // vtable+0x34
	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~ControlConfigScreen() override;                                                   // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047a690
	// ControlConfigScreen::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x3360 - 0x368]; // 0x0368
};

#endif // CONTROLCONFIGSCREEN_H
