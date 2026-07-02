#ifndef OBSCURESIGIL0XDC
#define OBSCURESIGIL0XDC

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
// SIZE: 0xdc
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
		undefined4 m_unk0x70;              // 0x70
		LegoBool32 m_hasBlendedWorld;      // 0x74
		undefined4 m_unk0x78;              // 0x78
		undefined4 m_unk0x7c;              // 0x7c
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
	LegoBool32 Create(CreateParams* p_createParams, undefined4 p_unk0x08);
	MenuSceneElement* AddElement(MenuSceneElement* p_unk0x04);
	void SetCameraLookAt(GolVec3* p_unk0x04, GolVec3* p_unk0x08);
	void GetEntityScreenRect(GolWorldEntity* p_entity, Rect* p_rect);
	GolWorldDatabase* GetWorld() const { return m_world; }
	GolWorldDatabase** GetWorldAddress() { return &m_world; }
	GolWorldDatabase* GetBlendedWorld() const { return m_blendedWorld; }
	GolCamera* GetCamera() const { return m_camera; }
	void SetUnk0x6c(undefined4 p_unk0x6c) { m_unk0x6c = p_unk0x6c; }

	// SYNTHETIC: LEGORACERS 0x00465730
	// MenuSceneView::`scalar deleting destructor'

protected:
	void LoadWorlds(CreateParams* p_createParams, undefined4 p_unk0x08);
	void SetupCamera(CreateParams* p_createParams);
	void UpdateElements(undefined4 p_elapsedMs);
	void ClampToScreen(Rect* p_rect);
	void FUN_00465ea0();

	MenuSceneElement* m_elements;     // 0x58
	GolWorldDatabase* m_world;        // 0x5c
	GolWorldDatabase* m_blendedWorld; // 0x60
	GolCamera* m_camera;              // 0x64
	GolCamera* m_savedCamera;         // 0x68
	undefined4 m_unk0x6c;             // 0x6c
	GolVec3 m_cameraEye;              // 0x70
	GolVec3 m_cameraTarget;           // 0x7c
	undefined4 m_unk0x88;             // 0x88
	LegoFloat m_worldScale;           // 0x8c
	GolVec3 m_unk0x90;                // 0x90
	GolVec3 m_unk0x9c;                // 0x9c
	GolVec3 m_unk0xa8;                // 0xa8
	LegoFloat m_unk0xb4;              // 0xb4
	LegoFloat m_unk0xb8;              // 0xb8
	LegoFloat m_unk0xbc;              // 0xbc
	LegoFloat m_unk0xc0;              // 0xc0
	LegoFloat m_unk0xc4;              // 0xc4
	LegoFloat m_unk0xc8;              // 0xc8
	LegoFloat m_unk0xcc;              // 0xcc
	LegoFloat m_unk0xd0;              // 0xd0
	LegoFloat m_unk0xd4;              // 0xd4
	LegoFloat m_unk0xd8;              // 0xd8
};

#endif // OBSCURESIGIL0XDC
