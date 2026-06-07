#ifndef CIRCUITSELECTSCREEN_H
#define CIRCUITSELECTSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menuscenescreen.h"

// VTABLE: LEGORACERS 0x004b3030
// SIZE 0x658
class CircuitSelectScreen : public MenuSceneScreen {
public:
	CircuitSelectScreen();

	void VTable0x4c() override;                                                // vtable+0x4c
	~CircuitSelectScreen() override;                                           // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override;                                // vtable+0x78
	void VTable0x84() override;                                                // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00479aa0
	// CircuitSelectScreen::`scalar deleting destructor'
};

#endif // CIRCUITSELECTSCREEN_H
