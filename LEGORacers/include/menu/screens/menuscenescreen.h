#ifndef MENUSCENESCREEN_H
#define MENUSCENESCREEN_H

#include "compat.h"
#include "decomp.h"
#include "golstringtable.h"
#include "menu/runtime/cutscenedefinition.h"
#include "menu/runtime/cutsceneplayer.h"
#include "menu/screens/menugamescreen.h"
#include "menu/widgets/menuwidget.h"
#include "types.h"

class GolCamera;
class GolD3DRenderDevice;
class MenuGameContext;
class MenuScreenCreateParams;

// VTABLE: LEGORACERS 0x004b2f98
// SIZE 0x658
class MenuSceneScreen : public MenuGameScreen {
public:
	// VTABLE: LEGORACERS 0x004b1f60
	// SIZE 0x2d0
	class SceneWidget : public MenuWidget {
	public:
		SceneWidget();
		~SceneWidget() override; // vtable+0x04

		LegoBool32 VTable0x08() override;                                                 // vtable+0x08
		MenuWidget* VTable0x2c(void*, undefined4, undefined4) override;                   // vtable+0x2c
		MenuWidget* VTable0x30(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
		MenuWidget* VTable0x34(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x34
		MenuWidget* VTable0x38(Rect*, Rect*) override;                                    // vtable+0x38
		undefined4 VTable0x3c(undefined4) override;                                       // vtable+0x3c

		// SYNTHETIC: LEGORACERS 0x00466a80
		// MenuSceneScreen::SceneWidget::`scalar deleting destructor'

		undefined4 FUN_00466b50(MenuScreen::SceneRefBinding* p_createParams, undefined4 p_unk0x08);
		void FUN_00466b10();
		void FUN_00466b90();
		void FUN_00466bf0(MenuScreen::SceneRefBinding* p_createParams, undefined4 p_unk0x08);
		void FUN_00466d00(CutsceneDefinition::Frame* p_frame);

		CutsceneDefinition m_unk0x58;          // 0x058
		CutscenePlayer m_unk0x84;              // 0x084
		LegoU32 m_unk0x2ac;                    // 0x2ac
		CutsceneDefinition::Frame* m_unk0x2b0; // 0x2b0
		Rect m_unk0x2b4;                       // 0x2b4
		undefined4 m_unk0x2c4;                 // 0x2c4
		LegoBool32 m_unk0x2c8;                 // 0x2c8
		LegoBool32 m_unk0x2cc;                 // 0x2cc
	};

	MenuSceneScreen();
	~MenuSceneScreen() override;                // vtable+0x68
	LegoBool32 Destroy() override;              // vtable+0x74
	LegoBool32 VTable0x78(undefined4) override; // vtable+0x78
	void VTable0x84() override;                 // vtable+0x84
	LegoBool32 VTable0x8c(MenuGameContext*,
						  MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00479710
	// MenuSceneScreen::`scalar deleting destructor'

protected:
	SceneWidget m_unk0x368;         // 0x368
	GolStringTable m_unk0x638;      // 0x638
	GolD3DRenderDevice* m_renderer; // 0x64c
	GolCamera* m_unk0x650;          // 0x650
	undefined4 m_unk0x654;          // 0x654
};

#endif // MENUSCENESCREEN_H
