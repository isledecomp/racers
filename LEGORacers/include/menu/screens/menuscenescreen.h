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

		LegoBool32 Destroy() override;                                                   // vtable+0x08
		MenuWidget* OnCursorEvent(void*, undefined4, undefined4) override;               // vtable+0x2c
		MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
		MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x34
		MenuWidget* DrawSelf(Rect*, Rect*) override;                                     // vtable+0x38
		undefined4 OnEvent(undefined4) override;                                         // vtable+0x3c

		// SYNTHETIC: LEGORACERS 0x00466a80
		// MenuSceneScreen::SceneWidget::`scalar deleting destructor'

		undefined4 Create(SceneRefBinding* p_createParams, undefined4 p_binary);
		void ResetState();
		void ComputeViewportRect();
		void LoadCutscene(SceneRefBinding* p_createParams, undefined4 p_binary);
		void SetFrame(CutsceneDefinition::Frame* p_frame);

		CutsceneDefinition m_definition;    // 0x058
		CutscenePlayer m_player;            // 0x084
		LegoU32 m_frameIndex;               // 0x2ac
		CutsceneDefinition::Frame* m_frame; // 0x2b0
		Rect m_viewportRect;                // 0x2b4
		undefined4 m_autoAdvance;           // 0x2c4
		LegoBool32 m_finished;              // 0x2c8
		LegoBool32 m_skippable;             // 0x2cc
	};

	MenuSceneScreen();
	~MenuSceneScreen() override;            // vtable+0x68
	LegoBool32 Destroy() override;          // vtable+0x74
	LegoBool32 Update(undefined4) override; // vtable+0x78
	void Navigate() override;               // vtable+0x84
	LegoBool32 Initialize(MenuGameContext*,
						  MenuScreenCreateParams*) override; // vtable+0x8c

	// SYNTHETIC: LEGORACERS 0x00479710
	// MenuSceneScreen::`scalar deleting destructor'

protected:
	SceneWidget m_sceneWidget;        // 0x368
	GolStringTable m_languageStrings; // 0x638
	GolD3DRenderDevice* m_renderer;   // 0x64c
	GolCamera* m_savedCamera;         // 0x650
	LegoBool32 m_firstUpdate;         // 0x654
};

#endif // MENUSCENESCREEN_H
