#ifndef MAININTROSCREEN_H
#define MAININTROSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/imaginarychisel0x658.h"

// VTABLE: LEGORACERS 0x004b3640
// SIZE 0x658
class MainIntroScreen : public ImaginaryChisel0x658 {
public:
	MainIntroScreen();

	void VTable0x4c() override;                                                        // vtable+0x4c
	~MainIntroScreen() override;                                                       // vtable+0x68
	LegoBool32 Destroy() override;                                                     // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                        // vtable+0x78
	void VTable0x84() override;                                                        // vtable+0x84
	LegoBool32 VTable0x8c(MenuToolContext0x4bc8*, MenuToolCreateParams0x30*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x004809d0
	// MainIntroScreen::`scalar deleting destructor'
};

#endif // MAININTROSCREEN_H
