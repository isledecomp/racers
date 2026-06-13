#include "menu/widgets/menusceneview.h"

#include "camera/golcamera.h"
#include "camera/golcamerabase.h"
#include "core/gol.h"
#include "golerror.h"
#include "golworldentity.h"
#include "render/gold3drenderdevice.h"
#include "surface/slatepeak0x58.h"
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
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x004657a0
void MenuSceneView::Reset()
{
	m_unk0x88 = 5;
	m_unk0x5c = 0;
	m_unk0x64 = 0;
	m_unk0x60 = 0;
	m_unk0x68 = 0;
	m_unk0x58 = NULL;
	m_unk0x6c = 0;
	m_unk0xb4 = 0;
	m_unk0xb8 = 0;
	m_unk0xbc = 0;
	m_unk0xc0 = 0;
	m_unk0xc4 = 0;
	m_unk0xc8 = 0;
	m_unk0xcc = 0;
	m_unk0xd0 = 0;
	m_unk0xd4 = 0;
	m_unk0xd8 = 0;
	m_unk0x90.m_y = 0.0f;
	m_unk0x90.m_x = 0.0f;
	m_unk0x90.m_z = -1.0f;

	MenuWidget::Reset();
}

// FUNCTION: LEGORACERS 0x00465820
LegoBool32 MenuSceneView::FUN_00465820(CreateParams* p_createParams, undefined4 p_unk0x08)
{
	VTable0x08();
	m_unk0x88 = p_createParams->m_unk0x78;

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

	if (FUN_00472a60(p_createParams)) {
		FUN_00465900(p_createParams, p_unk0x08);
		FUN_004659b0(p_createParams);
	}

	return m_flags & 1;
}

// FUNCTION: LEGORACERS 0x00465890
LegoBool32 MenuSceneView::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (result & m_flags) {
		if (m_unk0x64 && m_unk0x5c && !m_unk0x5c->GetUnk0x7c()) {
			m_golExport->VTable0x54(m_unk0x64);
		}

		if (m_unk0x5c) {
			m_unk0x5c->VTable0x18();
			m_golExport->VTable0x3c(m_unk0x5c);
		}

		if (m_unk0x60) {
			m_unk0x60->VTable0x18();
			m_golExport->VTable0x3c(m_unk0x60);
		}

		result = MenuWidget::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00465900
void MenuSceneView::FUN_00465900(CreateParams* p_createParams, undefined4 p_binary)
{
	m_unk0x6c = p_createParams->m_unk0x70;
	m_unk0x8c = p_createParams->m_unk0x5c;

	m_unk0x5c = m_golExport->VTable0x08();
	if (!m_unk0x5c) {
		GOL_FATALERROR(c_golErrorOutOfMemory);
	}

	m_unk0x5c->VTable0x14(m_renderer, p_createParams->m_unk0x60, p_binary, m_unk0x8c);

	if (p_createParams->m_unk0x74) {
		m_unk0x60 = m_golExport->VTable0x08();
		if (!m_unk0x60) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		m_unk0x60->VTable0x14(m_renderer, "blended", p_binary, m_unk0x8c);
	}

	ColorRGBA color = {0, 0, 0, 0};
	m_renderer->VTable0x1c(color);
}

// FUNCTION: LEGORACERS 0x004659b0
void MenuSceneView::FUN_004659b0(CreateParams* p_createParams)
{
	if (m_unk0x5c->GetUnk0x7c()) {
		m_unk0x64 = static_cast<GolCamera*>(m_unk0x5c->VTable0x50(0));
	}
	else {
		GolVec3* cameraVectors = &p_createParams->m_unk0x38;
		m_unk0x64 = m_golExport->VTable0x20();
		if (!m_unk0x64) {
			GOL_FATALERROR(c_golErrorOutOfMemory);
		}

		LegoU32 dirtyFlag = GolCamera::c_flagBit1;
		GolCamera* lens = m_unk0x64;
		LegoFloat value = cameraVectors[2].m_x;
		lens->m_fov = value;
		lens->m_flags |= dirtyFlag;
		lens = m_unk0x64;
		value = cameraVectors[2].m_y;
		lens->m_nearClip = value;
		lens->m_flags |= dirtyFlag;
		lens = m_unk0x64;
		value = cameraVectors[2].m_z;
		lens->m_farClip = value;
		lens->m_flags |= dirtyFlag;

		FUN_00465ab0(cameraVectors, cameraVectors + 1);
	}

	Rect rect = *GetGlobalRect();
	FUN_00465e40(&rect);

	LegoS32 width = rect.m_right;
	width -= rect.m_left;
	LegoS32 height = rect.m_bottom;
	height -= rect.m_top;

	LegoFloat aspect = static_cast<LegoFloat>(width);
	LegoFloat divisor = static_cast<LegoFloat>(height);
	aspect /= divisor;
	aspect *= p_createParams->m_unk0x80;
	m_unk0x64->SetAspectRatio(aspect);
}

// FUNCTION: LEGORACERS 0x00465ab0
void MenuSceneView::FUN_00465ab0(GolVec3* p_unk0x04, GolVec3* p_unk0x08)
{
	GolVec3 up;
	up.m_y = 0.0f;
	up.m_x = 0.0f;
	up.m_z = 1.0f;

	if (p_unk0x04) {
		LegoFloat scale = m_unk0x8c;
		m_unk0x70.m_x = scale * p_unk0x04->m_x;
		LegoFloat y = p_unk0x04->m_y;
		m_unk0x70.m_y = y * scale;
		LegoFloat z = p_unk0x04->m_z;
		m_unk0x70.m_z = z * scale;
	}

	if (p_unk0x08) {
		LegoFloat scale = m_unk0x8c;
		m_unk0x7c.m_x = scale * p_unk0x08->m_x;
		LegoFloat y = p_unk0x08->m_y;
		m_unk0x7c.m_y = y * scale;
		LegoFloat z = p_unk0x08->m_z;
		m_unk0x7c.m_z = z * scale;
	}

	m_unk0x64->LookAt(&m_unk0x70, &m_unk0x7c, &up);
}

// FUNCTION: LEGORACERS 0x00465b40
MenuSceneElement* MenuSceneView::FUN_00465b40(MenuSceneElement* p_unk0x04)
{
	if (!m_unk0x58) {
		m_unk0x58 = p_unk0x04;
		return p_unk0x04;
	}

	return p_unk0x04->FUN_0046b350(m_unk0x58);
}

// FUNCTION: LEGORACERS 0x00465b60
void MenuSceneView::FUN_00465b60(GolWorldEntity* p_entity, Rect* p_rect)
{
	GolVec3 center;
	p_entity->FUN_100286d0(&center);

	LegoFloat radius = p_entity->FUN_10028710();
	GolVec4 bounds;
	if (m_unk0x64->VTable0x24(&center, radius, &bounds)) {
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
void MenuSceneView::FUN_00465c00(undefined4 p_elapsedMs)
{
	if (m_unk0x64->m_trackedEntity) {
		return;
	}

	m_unk0xc0 = (m_unk0xbc - m_unk0xc0) * 0.03f + m_unk0xc0;
	m_unk0xb8 = (m_unk0xb4 - m_unk0xb8) * 0.02f + m_unk0xb8;
	m_unk0xc4 = m_unk0xc8 * 0.1f + m_unk0xc4 * 0.9f;
	m_unk0xcc = m_unk0xd0 * 0.1f + m_unk0xcc * 0.9f;
	LegoFloat turn = m_unk0xd8 * 0.3f + m_unk0xd4 * 0.7f;
	m_unk0xd4 = turn;

	if (turn != 0.0f) {
		GolCamera* lens = m_unk0x64;
		LegoFloat value = lens->m_fov;
		LegoU32 flags = lens->m_flags;
		value += turn;
		lens->m_flags = flags | GolCamera::c_flagBit1;
		lens->m_fov = value;
	}

	GolVec3* forward = &m_unk0x90;
	GolVec3* right = &m_unk0x9c;
	m_unk0x64->GetTransform()->VTable0x1c(right, forward);

	GolVec3* axis = &m_unk0xa8;
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
	m_unk0x90.m_x = 0.0f;
	m_unk0x90.m_y = 0.0f;
	m_unk0x90.m_z = -1.0f;

	LegoFloat elapsed = static_cast<LegoFloat>(static_cast<LegoS32>(p_elapsedMs));
	GolVec3 rotatedRight;
	LegoFloat angle = m_unk0xc4;
	angle *= elapsed;
	GolMath::FUN_004496a0(right, &rotatedRight, axis, angle);
	angle = m_unk0xcc;
	angle *= elapsed;
	GolMath::FUN_004496a0(&rotatedRight, right, forward, angle);

	GolVec3 position;
	m_unk0x64->GetTransform()->GetPosition(&position);
	LegoFloat forwardDelta = -forward->m_x;
	forwardDelta *= m_unk0xb8;
	LegoFloat rightDelta = -right->m_x;
	rightDelta *= m_unk0xc0;
	position.m_x += (forwardDelta + rightDelta) * elapsed;
	GolCamera* lens = m_unk0x64;

	rightDelta = -m_unk0x9c.m_y;
	rightDelta *= m_unk0xc0;
	forwardDelta = -m_unk0x90.m_y;
	forwardDelta *= m_unk0xb8;
	position.m_y += (rightDelta + forwardDelta) * elapsed;

	rightDelta = -m_unk0x9c.m_z;
	rightDelta *= m_unk0xc0;
	forwardDelta = -m_unk0x90.m_z;
	forwardDelta *= m_unk0xb8;
	position.m_z += (rightDelta + forwardDelta) * elapsed;
	lens->GetTransform()->SetPosition(&position);

	lens->m_flags |= GolCamera::c_flagBit0;
	GolCamera* currentLens = m_unk0x64;
	currentLens->GetTransform()->VTable0x24(right, forward);
	currentLens->m_flags |= GolCamera::c_flagBit0;
}

// FUNCTION: LEGORACERS 0x00465e40
void MenuSceneView::FUN_00465e40(Rect* p_rect)
{
	const SlatePeak0x58* renderTarget = m_renderer->GetRenderTargetInfo();

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

	m_unk0x64->VTable0x0c(p_rect);
}

// FUNCTION: LEGORACERS 0x00465ea0
void MenuSceneView::FUN_00465ea0()
{
	if (m_unk0x5c->GetUnk0x84() || m_unk0x5c->GetUnk0x8c()) {
		m_renderer->VTable0x28();

		if (m_unk0x5c->GetUnk0x84()) {
			m_renderer->VTable0x2c(m_unk0x5c->GetUnk0xac());
		}

		for (LegoU32 i = 0; i < m_unk0x5c->GetUnk0x8c(); i++) {
			m_renderer->VTable0x30(&m_unk0x5c->GetUnk0xb0()[i]);
		}

		m_renderer->VTable0x60();
	}
}

// FUNCTION: LEGORACERS 0x00465f20
MenuWidget* MenuSceneView::VTable0x38(Rect*, Rect*)
{
	m_renderer->VTable0xe4();
	m_unk0x68 = m_renderer->GetUnk0x0c();
	m_renderer->VTable0x20(m_unk0x64);
	m_renderer->VTable0x5c();
	m_renderer->VTable0xec(m_unk0x88);
	FUN_00465ea0();

	if (m_unk0x6c || !m_unk0x58) {
		m_unk0x5c->FUN_00416040();
	}

	for (MenuSceneElement* link = m_unk0x58; link; link = link->GetNext()) {
		link->VTable0x0c();
	}

	if (m_unk0x6c && m_unk0x60) {
		m_unk0x60->FUN_00416040();
	}

	m_renderer->VTable0x20(m_unk0x68);
	m_renderer->VTable0x5c();
	m_renderer->VTable0xec(6);
	m_renderer->VTable0xe8(FALSE);

	return NULL;
}

// FUNCTION: LEGORACERS 0x00465fe0
MenuWidget* MenuSceneView::VTable0x30(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	if (m_unk0x28 && m_unk0x28->VTable0x18(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466010
MenuWidget* MenuSceneView::VTable0x34(InputEventQueue::Event* p_item, undefined4 p_x, undefined4 p_y)
{
	if (m_unk0x28 && m_unk0x28->VTable0x1c(this, p_item, p_x, p_y)) {
		return this;
	}

	return NULL;
}

// FUNCTION: LEGORACERS 0x00466040
undefined4 MenuSceneView::VTable0x3c(undefined4 p_elapsedMs)
{
	for (MenuSceneElement* link = m_unk0x58; link; link = link->GetNext()) {
		link->VTable0x10(p_elapsedMs);
	}

	if (m_unk0x6c) {
		m_unk0x5c->FUN_00416090(p_elapsedMs);

		if (m_unk0x60) {
			m_unk0x60->FUN_00416090(p_elapsedMs);
		}
	}

	FUN_00465c00(p_elapsedMs);
	return 0;
}

// Keep this fold pair out of the unrelated MenuWidget null-return fold group.
#pragma code_seg(".text$legoracers_00466090")
// FUNCTION: LEGORACERS 0x00466090 FOLDED
MenuWidget* MenuSceneView::VTable0x2c(void*, undefined4, undefined4)
{
	return NULL;
}
#pragma code_seg()
