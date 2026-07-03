#include "menu/widgets/menusceneview.h"

#include "camera/golcamera.h"
#include "core/gol.h"
#include "golcamerabase.h"
#include "golerror.h"
#include "golworldentity.h"
#include "render/gold3drenderdevice.h"
#include "surface/golrendertarget.h"
#include "world/golworlddatabase.h"

DECOMP_SIZE_ASSERT(MenuSceneView, 0xdc)
DECOMP_SIZE_ASSERT(MenuSceneView::CreateParams, 0x84)

// FUNCTION: LEGORACERS 0x004656e0
MenuSceneView::MenuSceneView()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00465750
MenuSceneView::~MenuSceneView()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x004657a0
void MenuSceneView::Reset()
{
	m_viewportClearMode = 5;
	m_world = 0;
	m_camera = 0;
	m_blendedWorld = 0;
	m_savedCamera = 0;
	m_elements = NULL;
	m_drawWorld = 0;
	m_targetForwardSpeed = 0;
	m_forwardSpeed = 0;
	m_targetStrafeSpeed = 0;
	m_strafeSpeed = 0;
	m_yawRate = 0;
	m_targetYawRate = 0;
	m_pitchRate = 0;
	m_targetPitchRate = 0;
	m_zoomRate = 0;
	m_targetZoomRate = 0;
	m_forward.m_y = 0.0f;
	m_forward.m_x = 0.0f;
	m_forward.m_z = -1.0f;

	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x00465820
LegoBool32 MenuSceneView::Create(CreateParams* p_createParams, undefined4 p_binary)
{
	Destroy();
	m_viewportClearMode = p_createParams->m_viewportClearMode;

	if (p_createParams->m_parent) {
		if (!p_createParams->m_rect.m_right) {
			p_createParams->m_rect.m_right =
				p_createParams->m_parent->GetRect()->m_right - p_createParams->m_parent->GetRect()->m_left;
		}

		if (!p_createParams->m_rect.m_bottom) {
			p_createParams->m_rect.m_bottom =
				p_createParams->m_parent->GetRect()->m_bottom - p_createParams->m_parent->GetRect()->m_top;
		}
	}

	if (CreateWidget(p_createParams)) {
		LoadWorlds(p_createParams, p_binary);
		SetupCamera(p_createParams);
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00465890
LegoBool32 MenuSceneView::Destroy()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		if (m_camera && m_world && !m_world->GetCameraCount()) {
			m_golExport->DestroyCamera(m_camera);
		}

		if (m_world) {
			m_world->Destroy();
			m_golExport->DestroyWorldDatabase(m_world);
		}

		if (m_blendedWorld) {
			m_blendedWorld->Destroy();
			m_golExport->DestroyWorldDatabase(m_blendedWorld);
		}

		result = MenuWidget::Destroy();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00465900
void MenuSceneView::LoadWorlds(CreateParams* p_createParams, undefined4 p_binary)
{
	m_drawWorld = p_createParams->m_drawWorld;
	m_worldScale = p_createParams->m_worldScale;

	m_world = m_golExport->CreateWorldDatabase();
	if (!m_world) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_world->Load(m_renderer, p_createParams->m_worldName, p_binary, m_worldScale);

	if (p_createParams->m_hasBlendedWorld) {
		m_blendedWorld = m_golExport->CreateWorldDatabase();
		if (!m_blendedWorld) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_blendedWorld->Load(m_renderer, "blended", p_binary, m_worldScale);
	}

	ColorRGBA color = {0, 0, 0, 0};
	m_renderer->SetClearColor(color);
}

// FUNCTION: LEGORACERS 0x004659b0
void MenuSceneView::SetupCamera(CreateParams* p_createParams)
{
	if (m_world->GetCameraCount()) {
		m_camera = static_cast<GolCamera*>(m_world->GetCamera(0));
	}
	else {
		GolVec3* cameraVectors = &p_createParams->m_cameraEye;
		m_camera = m_golExport->CreateCamera();
		if (!m_camera) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoU32 dirtyFlag = GolCamera::c_flagProjectionDirty;
		GolCamera* lens = m_camera;
		LegoFloat value = cameraVectors[2].m_x;
		lens->m_fov = value;
		lens->m_flags |= dirtyFlag;
		lens = m_camera;
		value = cameraVectors[2].m_y;
		lens->m_nearClip = value;
		lens->m_flags |= dirtyFlag;
		lens = m_camera;
		value = cameraVectors[2].m_z;
		lens->m_farClip = value;
		lens->m_flags |= dirtyFlag;

		SetCameraLookAt(cameraVectors, cameraVectors + 1);
	}

	Rect rect = *GetGlobalRect();
	ClampToScreen(&rect);

	LegoS32 width = rect.m_right;
	width -= rect.m_left;
	LegoS32 height = rect.m_bottom;
	height -= rect.m_top;

	LegoFloat aspect = static_cast<LegoFloat>(width);
	LegoFloat divisor = static_cast<LegoFloat>(height);
	aspect /= divisor;
	aspect *= p_createParams->m_aspectScale;
	m_camera->SetAspectRatio(aspect);
}

// FUNCTION: LEGORACERS 0x00465ab0
void MenuSceneView::SetCameraLookAt(GolVec3* p_eye, GolVec3* p_target)
{
	GolVec3 up;
	up.m_y = 0.0f;
	up.m_x = 0.0f;
	up.m_z = 1.0f;

	if (p_eye) {
		LegoFloat scale = m_worldScale;
		m_cameraEye.m_x = scale * p_eye->m_x;
		LegoFloat y = p_eye->m_y;
		m_cameraEye.m_y = y * scale;
		LegoFloat z = p_eye->m_z;
		m_cameraEye.m_z = z * scale;
	}

	if (p_target) {
		LegoFloat scale = m_worldScale;
		m_cameraTarget.m_x = scale * p_target->m_x;
		LegoFloat y = p_target->m_y;
		m_cameraTarget.m_y = y * scale;
		LegoFloat z = p_target->m_z;
		m_cameraTarget.m_z = z * scale;
	}

	m_camera->LookAt(&m_cameraEye, &m_cameraTarget, &up);
}

// FUNCTION: LEGORACERS 0x00465b40
MenuSceneElement* MenuSceneView::AddElement(MenuSceneElement* p_element)
{
	if (!m_elements) {
		m_elements = p_element;
		return p_element;
	}

	return p_element->Append(m_elements);
}

// FUNCTION: LEGORACERS 0x00465b60
void MenuSceneView::GetEntityScreenRect(GolWorldEntity* p_entity, Rect* p_rect)
{
	GolVec3 center;
	p_entity->GetBoundsCenter(&center);

	LegoFloat radius = p_entity->GetBoundsRadius();
	GolVec4 bounds;
	if (m_camera->ProjectSphere(&center, radius, &bounds)) {
		p_rect->m_top = static_cast<LegoS32>(bounds.m_y);
		p_rect->m_left = static_cast<LegoS32>(bounds.m_x);
		p_rect->m_right = static_cast<LegoS32>(bounds.m_z);
		p_rect->m_bottom = static_cast<LegoS32>(bounds.m_u);
	}
	else {
		p_rect->m_left = 0;
		p_rect->m_top = 0;
		p_rect->m_right = 0;
		p_rect->m_bottom = 0;
	}
}

// FUNCTION: LEGORACERS 0x00465c00
void MenuSceneView::UpdateFreeCamera(undefined4 p_elapsedMs)
{
	if (m_camera->m_trackedEntity) {
		return;
	}

	m_strafeSpeed = (m_targetStrafeSpeed - m_strafeSpeed) * 0.03f + m_strafeSpeed;
	m_forwardSpeed = (m_targetForwardSpeed - m_forwardSpeed) * 0.02f + m_forwardSpeed;
	m_yawRate = m_targetYawRate * 0.1f + m_yawRate * 0.9f;
	m_pitchRate = m_targetPitchRate * 0.1f + m_pitchRate * 0.9f;
	LegoFloat turn = m_targetZoomRate * 0.3f + m_zoomRate * 0.7f;
	m_zoomRate = turn;

	if (turn != 0.0f) {
		GolCamera* lens = m_camera;
		LegoFloat value = lens->m_fov;
		LegoU32 flags = lens->m_flags;
		value += turn;
		lens->m_flags = flags | GolCamera::c_flagProjectionDirty;
		lens->m_fov = value;
	}

	GolVec3* forward = &m_forward;
	GolVec3* right = &m_right;
	m_camera->GetTransform()->VTable0x1c(right, forward);

	GolVec3* axis = &m_up;
	LegoFloat axisX = right->m_y;
	axisX *= forward->m_z;
	axisX -= forward->m_y * right->m_z;
	axis->m_x = axisX;

	LegoFloat axisY = right->m_z;
	axisY *= forward->m_x;
	axisY -= right->m_x * forward->m_z;
	axis->m_y = axisY;

	LegoFloat axisZ = forward->m_y * right->m_x;
	LegoFloat side = right->m_y;
	side *= forward->m_x;
	axisZ -= side;
	axis->m_z = axisZ;
	m_forward.m_x = 0.0f;
	m_forward.m_y = 0.0f;
	m_forward.m_z = -1.0f;

	LegoFloat elapsed = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	GolVec3 rotatedRight;
	LegoFloat angle = m_yawRate;
	angle *= elapsed;
	GolMath::RotateAboutAxis(right, &rotatedRight, axis, angle);
	angle = m_pitchRate;
	angle *= elapsed;
	GolMath::RotateAboutAxis(&rotatedRight, right, forward, angle);

	GolVec3 position;
	m_camera->GetTransform()->GetPosition(&position);
	LegoFloat forwardDelta = -forward->m_x;
	forwardDelta *= m_forwardSpeed;
	LegoFloat rightDelta = -right->m_x;
	rightDelta *= m_strafeSpeed;
	position.m_x += (forwardDelta + rightDelta) * elapsed;
	GolCamera* lens = m_camera;

	rightDelta = -m_right.m_y;
	rightDelta *= m_strafeSpeed;
	forwardDelta = -m_forward.m_y;
	forwardDelta *= m_forwardSpeed;
	position.m_y += (rightDelta + forwardDelta) * elapsed;

	rightDelta = -m_right.m_z;
	rightDelta *= m_strafeSpeed;
	forwardDelta = -m_forward.m_z;
	forwardDelta *= m_forwardSpeed;
	position.m_z += (rightDelta + forwardDelta) * elapsed;
	lens->GetTransform()->SetPosition(&position);

	lens->m_flags |= GolCamera::c_flagViewDirty;
	GolCamera* currentLens = m_camera;
	currentLens->GetTransform()->VTable0x24(right, forward);
	currentLens->m_flags |= GolCamera::c_flagViewDirty;
}

// FUNCTION: LEGORACERS 0x00465e40
void MenuSceneView::ClampToScreen(Rect* p_rect)
{
	const GolRenderTarget* renderTarget = m_renderer->GetRenderTargetInfo();

	if (p_rect->m_left < 0) {
		p_rect->m_left = 0;
	}

	LegoS32 width = renderTarget->GetWidth();
	if (p_rect->m_right > width) {
		p_rect->m_right = width;
	}

	if (p_rect->m_top < 0) {
		p_rect->m_top = 0;
	}

	LegoS32 height = renderTarget->GetHeight();
	if (p_rect->m_bottom > height) {
		p_rect->m_bottom = height;
	}

	m_camera->SetViewport(p_rect);
}

// FUNCTION: LEGORACERS 0x00465ea0
void MenuSceneView::ApplySceneMaterials()
{
	if (m_world->GetAmbientLightCount() || m_world->GetLightCount()) {
		m_renderer->ClearLights();

		if (m_world->GetAmbientLightCount()) {
			m_renderer->SetAmbient(m_world->GetAmbientMaterial());
		}

		for (LegoU32 i = 0; i < m_world->GetLightCount(); i++) {
			m_renderer->AddLight(&m_world->GetLight()[i]);
		}

		m_renderer->ApplyLights();
	}
}

// FUNCTION: LEGORACERS 0x00465f20
MenuWidget* MenuSceneView::DrawSelf(Rect*, Rect*)
{
	m_renderer->EnableZBuffer();
	m_savedCamera = m_renderer->GetCurrentCamera();
	m_renderer->SetCamera(m_camera);
	m_renderer->ApplyCamera();
	m_renderer->SelectViewport(m_viewportClearMode);
	ApplySceneMaterials();

	if (m_drawWorld || !m_elements) {
		m_world->DrawWorld();
	}

	for (MenuSceneElement* link = m_elements; link; link = link->GetNext()) {
		link->Draw();
	}

	if (m_drawWorld && m_blendedWorld) {
		m_blendedWorld->DrawWorld();
	}

	m_renderer->SetCamera(m_savedCamera);
	m_renderer->ApplyCamera();
	m_renderer->SelectViewport(6);
	m_renderer->DisableZBuffer(FALSE);

	return NULL;
}

// FUNCTION: LEGORACERS 0x00465fe0
MenuWidget* MenuSceneView::OnKeyDown(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	if (m_notifyHandler && m_notifyHandler->HandleKeyDown(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466010
MenuWidget* MenuSceneView::OnKeyUp(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	if (m_notifyHandler && m_notifyHandler->HandleKeyUp(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466040
undefined4 MenuSceneView::OnEvent(undefined4 p_elapsedMs)
{
	for (MenuSceneElement* link = m_elements; link; link = link->GetNext()) {
		link->Update(p_elapsedMs);
	}

	if (m_drawWorld) {
		m_world->Update(p_elapsedMs);

		if (m_blendedWorld) {
			m_blendedWorld->Update(p_elapsedMs);
		}
	}

	UpdateFreeCamera(p_elapsedMs);
	return 0;
}

// Keep this fold pair out of the unrelated MenuWidget null-return fold group.
#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
MenuWidget* MenuSceneView::OnCursorEvent(void*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()
