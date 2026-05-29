#ifndef EDITCARSCREEN_H
#define EDITCARSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"

// VTABLE: LEGORACERS 0x004b3294
// SIZE 0x36c4
class EditCarScreen : public ImaginaryTool0x368 {
public:
	EditCarScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~EditCarScreen() override;                                                         // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	void VTable0x80() override;                                                        // vtable+0x80
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x0047bde0
	// EditCarScreen::`scalar deleting destructor'

protected:
	undefined m_unk0x368[0x36c4 - 0x368]; // 0x0368
};

#endif // EDITCARSCREEN_H
