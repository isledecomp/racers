#ifndef MENUSCENEVIEW_H
#define MENUSCENEVIEW_H

#include "compat.h"
#include "decomp.h"
#include "golmath.h"
#include "menu/widgets/menusceneelement.h"
#include "menu/widgets/menuwidget.h"
#include "types.h"

class GolCamera;
class GolWorldEntity;
class GolWorldDatabase;

// VTABLE: LEGORACERS 0x004b1dfc
// SIZE 0xdc
class MenuSceneView : public MenuWidget {
public:
	// SIZE 0x84
	class CreateParams : public MenuWidget::CreateParams {
	public:
		GolVec3 m_cameraEye;               // 0x38
		GolVec3 m_cameraTarget;            // 0x44
		GolVec3 m_cameraSettings;          // 0x50
		LegoFloat m_worldScale;            // 0x5c
		LegoChar m_worldName[0x70 - 0x60]; // 0x60
		undefined4 m_drawWorld;            // 0x70
		LegoBool32 m_hasBlendedWorld;      // 0x74
		LegoU32 m_viewportClearMode;       // 0x78
		undefined4 m_eventCode;            // 0x7c
		LegoFloat m_aspectScale;           // 0x80
	};

	MenuSceneView();

	void Reset() override;                                                           // vtable+0x00
	~MenuSceneView() override;                                                       // vtable+0x04
	LegoBool32 Destroy() override;                                                   // vtable+0x08
	MenuWidget* OnCursorEvent(void*, undefined4, undefined4) override;               // vtable+0x2c
	MenuWidget* OnKeyDown(InputEventQueue::Event*, undefined4, undefined4) override; // vtable+0x30
	MenuWidget* OnKeyUp(InputEventQueue::Event*, undefined4, undefined4) override;   // vtable+0x34
	MenuWidget* DrawSelf(Rect*, Rect*) override;                                     // vtable+0x38
	undefined4 OnEvent(undefined4) override;                                         // vtable+0x3c
	LegoBool32 Create(CreateParams* p_createParams, undefined4 p_binary);
	MenuSceneElement* AddElement(MenuSceneElement* p_element);
	void SetCameraLookAt(GolVec3* p_eye, GolVec3* p_target);
	void GetEntityScreenRect(GolWorldEntity* p_entity, Rect* p_rect);
	GolWorldDatabase* GetWorld() const { return m_world; }
	GolWorldDatabase** GetWorldAddress() { return &m_world; }
	GolWorldDatabase* GetBlendedWorld() const { return m_blendedWorld; }
	GolCamera* GetCamera() const { return m_camera; }
	void SetDrawWorld(undefined4 p_drawWorld) { m_drawWorld = p_drawWorld; }

	// SYNTHETIC: LEGORACERS 0x00465730
	// MenuSceneView::`scalar deleting destructor'

protected:
	void LoadWorlds(CreateParams* p_createParams, undefined4 p_binary);
	void SetupCamera(CreateParams* p_createParams);
	void UpdateFreeCamera(undefined4 p_elapsedMs);
	void ClampToScreen(Rect* p_rect);
	void ApplySceneMaterials();

	MenuSceneElement* m_elements;     // 0x58
	GolWorldDatabase* m_world;        // 0x5c
	GolWorldDatabase* m_blendedWorld; // 0x60
	GolCamera* m_camera;              // 0x64
	GolCamera* m_savedCamera;         // 0x68
	undefined4 m_drawWorld;           // 0x6c
	GolVec3 m_cameraEye;              // 0x70
	GolVec3 m_cameraTarget;           // 0x7c
	LegoU32 m_viewportClearMode;      // 0x88
	LegoFloat m_worldScale;           // 0x8c
	GolVec3 m_forward;                // 0x90
	GolVec3 m_right;                  // 0x9c
	GolVec3 m_up;                     // 0xa8
	LegoFloat m_targetForwardSpeed;   // 0xb4
	LegoFloat m_forwardSpeed;         // 0xb8
	LegoFloat m_targetStrafeSpeed;    // 0xbc
	LegoFloat m_strafeSpeed;          // 0xc0
	LegoFloat m_yawRate;              // 0xc4
	LegoFloat m_targetYawRate;        // 0xc8
	LegoFloat m_pitchRate;            // 0xcc
	LegoFloat m_targetPitchRate;      // 0xd0
	LegoFloat m_zoomRate;             // 0xd4
	LegoFloat m_targetZoomRate;       // 0xd8
};

#endif // MENUSCENEVIEW_H
