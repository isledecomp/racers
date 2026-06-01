#ifndef AWARDCINEMATICSCREEN_H
#define AWARDCINEMATICSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarychisel0x658.h"

// VTABLE: LEGORACERS 0x004b2c5c
// SIZE 0x7b0
class AwardCinematicScreen : public ImaginaryChisel0x658 {
public:
	AwardCinematicScreen();

	void VTable0x4c() override;                                                        // vtable+0x4c
	~AwardCinematicScreen() override;                                                  // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00475cb0
	// AwardCinematicScreen::`scalar deleting destructor'

protected:
	undefined m_unk0x658[0x7b0 - 0x658]; // 0x658
};

#endif // AWARDCINEMATICSCREEN_H
