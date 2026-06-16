#include "camera/golcamera.h"
#include "decomp.h"
#include "race/racecameracontroller.h"
#include "race/racesession.h"

#include <math.h>

DECOMP_SIZE_ASSERT(RaceCameraController, 0x150)
DECOMP_SIZE_ASSERT(RaceCameraController::Profile, 0x18)

// GLOBAL: LEGORACERS 0x004b0328
const RaceCameraController::Profile g_unk0x004b0328[8] = {
	{1, {0, 0, 0}, 5.0f, 35.0f, 20.0f, 0.1f, 0.25f},
	{1, {0, 0, 0}, 8.0f, 25.0f, 30.0f, 0.1f, 0.25f},
	{1, {0, 0, 0}, 8.0f, 45.0f, 10.0f, 0.05f, 0.25f},
	{2, {0, 0, 0}, 0.0f, 0.0f, 0.0f, 0.1f, 0.25f},
	{3, {0, 0, 0}, 20.0f, 15.0f, 32.0f, 0.18f, 0.35f},
	{1, {0, 0, 0}, 8.0f, 20.0f, 22.0f, 0.1f, 0.25f},
	{1, {0, 0, 0}, 7.0f, 15.0f, 45.0f, 0.1f, 0.25f},
	{1, {0, 0, 0}, 4.0f, 30.0f, 15.0f, 0.05f, 0.25f},
};

// GLOBAL: LEGORACERS 0x004b03e8
extern const LegoFloat g_unk0x004b03e8 = 250.0f;

// GLOBAL: LEGORACERS 0x004b03ec
extern const LegoFloat g_unk0x004b03ec = 0.017453292f;

// FUNCTION: LEGORACERS 0x00427b70
void RaceCameraController::FUN_00427b70(LegoFloat p_unk0x04)
{
	m_unk0x0f8 = (1.0f - p_unk0x04) / (g_unk0x004b03e8 * p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00427b90
void RaceCameraController::FUN_00427b90(LegoFloat p_unk0x04)
{
	m_unk0x0fc = (1.0f - p_unk0x04) / (g_unk0x004b03e8 * p_unk0x04);
}

// FUNCTION: LEGORACERS 0x00427bb0
void RaceCameraController::FUN_00427bb0(LegoFloat p_unk0x04)
{
	GolMath::FUN_00449170(g_unk0x004b03ec * p_unk0x04, &m_unk0x110, &m_unk0x114);
}

// FUNCTION: LEGORACERS 0x00427be0
void RaceCameraController::FUN_00427be0(LegoFloat p_unk0x04)
{
	m_unk0x10c = static_cast<LegoFloat>(sin(g_unk0x004b03ec * p_unk0x04));
}

// FUNCTION: LEGORACERS 0x004281b0
void RaceCameraController::Reset()
{
	m_unk0x0d4 = 0;
	m_unk0x000 = TRUE;
	FUN_004283f0(0, FALSE);
	m_unk0x100 = 0.09f;
	m_unk0x104 = 0.0044444446f;
	m_unk0x108 = 0.016666668f;
	m_unk0x140 = 0;
	m_unk0x14c = 0;
	m_unk0x004 = FALSE;
	m_unk0x005 = FALSE;
}

// FUNCTION: LEGORACERS 0x00428200
RaceCameraController::RaceCameraController()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00428210
void RaceCameraController::FUN_00428210(GolCamera* p_camera, GolD3DRenderDevice* p_renderer)
{
	m_camera = p_camera;
	m_renderer = p_renderer;
	m_unk0x134 = p_camera->GetFov();
}

// FUNCTION: LEGORACERS 0x004282a0
void RaceCameraController::FUN_004282a0(GolVec3* p_unk0x04, GolVec3* p_unk0x08)
{
	FUN_004282d0(p_unk0x04, p_unk0x08, &m_unk0x048);
	m_unk0x088 = m_unk0x048;
}

// FUNCTION: LEGORACERS 0x004282d0
void RaceCameraController::FUN_004282d0(GolVec3* p_unk0x04, GolVec3* p_unk0x08, GolMatrix3* p_unk0x0c)
{
	GolVec3* source = p_unk0x04;
	GolVec3* up = &p_unk0x0c->m_rows[1];
	GolVec3* back = &p_unk0x0c->m_rows[2];

	GolMath::NormalizeVector3(*source, back);

	GolVec3 forward;
	GolMath::NormalizeVector3(*source, &forward);

	LegoFloat dot = p_unk0x08->m_z * forward.m_z;
	dot += p_unk0x08->m_y * forward.m_y;
	dot += forward.m_x * p_unk0x08->m_x;

	GolVec3 projection;
	projection.m_x = forward.m_x * dot;
	projection.m_y = forward.m_y * dot;
	projection.m_z = forward.m_z * dot;

	up->m_x = p_unk0x08->m_x - projection.m_x;
	up->m_y = p_unk0x08->m_y - projection.m_y;
	up->m_z = p_unk0x08->m_z - projection.m_z;

	GolMath::NormalizeVector3(*up, up);

	GolVec3* right = &p_unk0x0c->m_rows[0];
	right->m_x = up->m_y * back->m_z - up->m_z * back->m_y;
	right->m_y = up->m_z * back->m_x - back->m_z * up->m_x;
	right->m_z = back->m_y * up->m_x - up->m_y * back->m_x;
}

// FUNCTION: LEGORACERS 0x00428390
void RaceCameraController::FUN_00428390(GolVec3* p_unk0x04)
{
	m_unk0x0ac = *p_unk0x04;
	m_unk0x06c = *p_unk0x04;
}

// FUNCTION: LEGORACERS 0x004283d0
void RaceCameraController::FUN_004283d0(LegoU8 p_unk0x04)
{
	if (m_unk0x002 != p_unk0x04) {
		m_unk0x002 = p_unk0x04;
		m_unk0x0c8 = 0;
	}
}

// FUNCTION: LEGORACERS 0x004283f0
void RaceCameraController::FUN_004283f0(LegoS32 p_unk0x04, LegoBool32 p_unk0x08)
{
	LegoS32 profileIndex = p_unk0x04;
	m_unk0x005 = p_unk0x08;
	if (p_unk0x08 && profileIndex < 3) {
		profileIndex += 5;
	}

	FUN_004283d0(g_unk0x004b0328[profileIndex].m_unk0x00);

	if (m_unk0x002 == 3) {
		m_unk0x124 = m_unk0x10c;
		m_unk0x128 = m_unk0x110;
		m_unk0x12c = m_unk0x114;
		m_unk0x130 = m_unk0x118;
	}

	FUN_00427bb0(g_unk0x004b0328[profileIndex].m_unk0x04);
	FUN_00427be0(g_unk0x004b0328[profileIndex].m_unk0x08);
	m_unk0x118 = g_unk0x004b0328[profileIndex].GetUnk0x0c();
	FUN_00427b70(g_unk0x004b0328[profileIndex].m_unk0x10);
	FUN_00427b90(g_unk0x004b0328[profileIndex].m_unk0x14);

	if (m_unk0x002 == 3) {
		m_unk0x124 -= m_unk0x10c;
		m_unk0x128 -= m_unk0x110;
		m_unk0x12c -= m_unk0x114;
		m_unk0x130 -= m_unk0x118;
	}

	m_unk0x004 = FALSE;
}

// STUB: LEGORACERS 0x00428540
void RaceCameraController::FUN_00428540(LegoFloat)
{
	STUB(0x00428540);
}
