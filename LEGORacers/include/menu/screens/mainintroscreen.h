#ifndef MAININTROSCREEN_H
#define MAININTROSCREEN_H

#include "compat.h"
#include "decomp.h"
#include "menu/screens/menuscenescreen.h"

// VTABLE: LEGORACERS 0x004b3640
// SIZE 0x658
class MainIntroScreen : public MenuSceneScreen {
public:
	MainIntroScreen();

	void CreateWidgets() override;                                             // vtable+0x4c
	~MainIntroScreen() override;                                               // vtable+0x68
	LegoBool32 Destroy() override;                                             // vtable+0x74
	LegoBool32 Update(undefined4) override;                                    // vtable+0x78
	void Navigate() override;                                                  // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*, MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x004809d0
	// MainIntroScreen::`scalar deleting destructor'
};

#endif // MAININTROSCREEN_H
