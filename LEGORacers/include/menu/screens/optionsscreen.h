#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarytool0x368.h"

class GameState;

// VTABLE: LEGORACERS 0x004b2b04
// SIZE 0x6750
class OptionsScreen : public ImaginaryTool0x368 {
public:
	OptionsScreen();

	void VTable0x38(ObscureVantage0x58*) override;                                     // vtable+0x38
	void VTable0x44(ObscureVantage0x58*) override;                                     // vtable+0x44
	void VTable0x4c() override;                                                        // vtable+0x4c
	void Reset() override;                                                             // vtable+0x54
	~OptionsScreen() override;                                                         // vtable+0x68
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x004755f0
	// OptionsScreen::`scalar deleting destructor'

protected:
	void FUN_00482de0();
	LegoBool32 FUN_004831d0(MenuToolContext0x4bc8* p_context, MenuToolCreateParams0x30* p_createParams);

	LegoBool m_unk0x368;                    // 0x0368
	LegoBool m_unk0x369;                    // 0x0369
	undefined m_unk0x36a[0x36c - 0x36a];    // 0x036a
	undefined4 m_unk0x36c;                  // 0x036c
	GameState* m_unk0x370;                  // 0x0370
	undefined m_unk0x374[0x51a8 - 0x374];   // 0x0374
	undefined4 m_unk0x51a8;                 // 0x51a8
	undefined m_unk0x51ac[0x646c - 0x51ac]; // 0x51ac
	undefined m_unk0x646c[0x1f4];           // 0x646c
	undefined m_unk0x6660[0x6750 - 0x6660]; // 0x6660
};

#endif // OPTIONSSCREEN_H
