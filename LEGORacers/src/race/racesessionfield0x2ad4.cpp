#include "audio/soundnode.h"
#include "camera/golcamera.h"
#include "camera/goltransform.h"
#include "decomp.h"
#include "race/racecameracontroller.h"
#include "race/racesession.h"
#include "render/gold3drenderdevice.h"

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

// STUB: LEGORACERS 0x00427c00
undefined4 RaceCameraController::FUN_00427c00()
{
	if (m_unk0x14c == NULL || m_unk0x0d4 == NULL) {
		return 0;
	}

	GolAnimatedEntity* entity = m_unk0x0d4->m_unk0x018.m_unk0x044;
	m_unk0x14c->m_velocity.m_x = m_unk0x0d4->m_unk0x3e8.m_unk0x008.m_x;
	m_unk0x14c->m_velocity.m_y = m_unk0x0d4->m_unk0x3e8.m_unk0x008.m_y;
	m_unk0x14c->m_velocity.m_z = m_unk0x0d4->m_unk0x3e8.m_unk0x008.m_z;

	entity->VTable0x48(&m_unk0x14c->m_right, &m_unk0x14c->m_forward);
	m_unk0x14c->m_orientation.m_x =
		m_unk0x14c->m_forward.m_y * m_unk0x14c->m_right.m_z - m_unk0x14c->m_forward.m_z * m_unk0x14c->m_right.m_y;
	m_unk0x14c->m_orientation.m_y =
		m_unk0x14c->m_forward.m_z * m_unk0x14c->m_right.m_x - m_unk0x14c->m_forward.m_x * m_unk0x14c->m_right.m_z;
	m_unk0x14c->m_orientation.m_z =
		m_unk0x14c->m_right.m_y * m_unk0x14c->m_forward.m_x - m_unk0x14c->m_forward.m_y * m_unk0x14c->m_right.m_x;
	GolMath::NormalizeVector3(m_unk0x14c->m_orientation, &m_unk0x14c->m_orientation);
	m_unk0x14c->m_unk0x44 = TRUE;

	entity->VTable0x04(&m_unk0x14c->m_position);
	m_unk0x14c->m_unk0x44 = TRUE;

	return 0;
}

// STUB: LEGORACERS 0x00427d30
void RaceCameraController::FUN_00427d30()
{
	if (m_camera == NULL) {
		return;
	}

	GolTransform* transform = m_camera->GetTransform();
	if (m_unk0x002 == 1 && m_unk0x004) {
		GolVec3 position;
		position.m_x = m_unk0x0e4.m_x + m_unk0x0e4.m_x - m_unk0x06c.m_x;
		position.m_y = m_unk0x0e4.m_y + m_unk0x0e4.m_y - m_unk0x06c.m_y;
		position.m_z = m_unk0x06c.m_z;
		transform->SetPosition(&position);
		m_camera->m_flags |= GolCamera::c_flagBit0;

		GolVec3 right;
		GolVec3 forward;
		right.m_x = -m_unk0x048.m_rows[2].m_x;
		right.m_y = -m_unk0x048.m_rows[2].m_y;
		right.m_z = m_unk0x048.m_rows[2].m_z;
		forward.m_x = -m_unk0x048.m_rows[1].m_x;
		forward.m_y = -m_unk0x048.m_rows[1].m_y;
		forward.m_z = m_unk0x048.m_rows[1].m_z;
		transform->VTable0x24(&right, &forward);
		m_camera->m_flags |= GolCamera::c_flagBit0;
		return;
	}

	if (m_unk0x002 == 2 && m_unk0x004) {
		transform->SetPosition(&m_unk0x06c);
		m_camera->m_flags |= GolCamera::c_flagBit0;

		GolVec3 right;
		GolVec3 forward;
		right.m_x = -m_unk0x048.m_rows[2].m_x;
		right.m_y = -m_unk0x048.m_rows[2].m_y;
		right.m_z = -m_unk0x048.m_rows[2].m_z;
		forward = m_unk0x048.m_rows[1];
		transform->VTable0x24(&right, &forward);
		m_camera->m_flags |= GolCamera::c_flagBit0;
		return;
	}

	transform->SetPosition(&m_unk0x06c);
	m_camera->m_flags |= GolCamera::c_flagBit0;
	transform->VTable0x24(&m_unk0x048.m_rows[2], &m_unk0x048.m_rows[1]);
	m_camera->m_flags |= GolCamera::c_flagBit0;
}

extern LegoU16 g_unk0x004befec[1024];
extern LegoU32 g_unk0x004c6ee4;

// STUB: LEGORACERS 0x00427e80
void RaceCameraController::FUN_00427e80()
{
	if (static_cast<LegoU32>(m_unk0x0d0) <= m_unk0x140) {
		m_unk0x140 -= m_unk0x0d0;
	}
	else {
		m_unk0x140 = 0;
	}

	if (m_unk0x0d4->m_unk0xd04 & 0x10) {
		m_unk0x140 = 0;
	}
	else if (!m_unk0x140) {
		m_unk0x140 = 500;
		m_unk0x138 = m_camera->m_fov;

		if (!(m_unk0x0d4->m_unk0xd04 & 0x800)) {
			if (m_camera->m_fov != m_unk0x134) {
				m_unk0x13c = (m_unk0x138 - m_unk0x134) * 0.5f;
			}
			else {
				m_unk0x13c = 0.0f;
				m_unk0x140 = 0;
			}
		}
		else if (m_unk0x13c <= 0.0f && m_unk0x138 > 40.0f || m_unk0x138 >= 80.0f) {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
			m_unk0x13c =
				static_cast<LegoFloat>(
					static_cast<LegoU16>(g_unk0x004befec[g_unk0x004c6ee4]) % static_cast<LegoS32>(m_unk0x138 - 40.0f)
				) *
				0.5f;
		}
		else {
			g_unk0x004c6ee4 = (g_unk0x004c6ee4 + 1) & 0x3ff;
			m_unk0x13c =
				-static_cast<LegoFloat>(
					static_cast<LegoU16>(g_unk0x004befec[g_unk0x004c6ee4]) % static_cast<LegoS32>(80.0f - m_unk0x138)
				) *
				0.5f;
		}
	}

	if (m_unk0x140) {
		LegoFloat angle = static_cast<LegoFloat>(cos((500 - m_unk0x140) * 0.02f * 0.1f * 3.1415927f));
		m_camera->m_fov = angle * m_unk0x13c + (m_unk0x138 - m_unk0x13c);
		m_camera->m_flags |= GolCamera::c_flagBit1;
		m_renderer->VTable0x5c();
	}
	else if (m_camera->m_fov != m_unk0x134) {
		m_camera->m_fov = m_unk0x134;
		m_camera->m_flags |= GolCamera::c_flagBit1;
		m_renderer->VTable0x5c();
	}
}

// STUB: LEGORACERS 0x004280a0
undefined4 RaceCameraController::FUN_004280a0()
{
	GolMatrix34 basis;
	basis.m_m[0][0] = m_unk0x008.m_m[0][0];
	basis.m_m[0][1] = m_unk0x008.m_m[0][1];
	basis.m_m[0][2] = m_unk0x008.m_m[0][2];
	basis.m_m[1][0] = m_unk0x008.m_m[1][0];
	basis.m_m[1][1] = m_unk0x008.m_m[1][1];
	basis.m_m[1][2] = m_unk0x008.m_m[1][2];
	basis.m_m[2][0] = m_unk0x008.m_m[2][0];
	basis.m_m[2][1] = m_unk0x008.m_m[2][1];
	basis.m_m[2][2] = m_unk0x008.m_m[2][2];
	GolMath::FUN_1002f5a0(basis, &m_unk0x038);

	if (m_unk0x001 & 1) {
		m_unk0x048 = m_unk0x008;
		m_unk0x06c = m_unk0x02c;
		m_unk0x078 = m_unk0x038;
	}
	else {
		LegoFloat positionAmount = 1.0f / (m_unk0x0f8 * m_unk0x0cc + 1.0f);
		m_unk0x06c.m_x = (m_unk0x0ac.m_x - m_unk0x02c.m_x) * positionAmount + m_unk0x02c.m_x;
		m_unk0x06c.m_y = (m_unk0x0ac.m_y - m_unk0x02c.m_y) * positionAmount + m_unk0x02c.m_y;
		m_unk0x06c.m_z = (m_unk0x0ac.m_z - m_unk0x02c.m_z) * positionAmount + m_unk0x02c.m_z;

		LegoFloat rotationAmount = 1.0f / (m_unk0x0fc * m_unk0x0cc + 1.0f);
		GolMath::FUN_1002f890(m_unk0x038, m_unk0x0b8, rotationAmount, &m_unk0x078);
		GolMath::FUN_00449340(&m_unk0x078, &m_unk0x048.m_m[0][0]);
	}

	FUN_00427d30();
	return FUN_00427c00();
}

// FUNCTION: LEGORACERS 0x004281b0
void RaceCameraController::Reset()
{
	m_unk0x0d4 = NULL;
	m_unk0x000 = TRUE;
	FUN_004283f0(0, FALSE);
	m_unk0x100 = 0.09f;
	m_unk0x104 = 0.0044444446f;
	m_unk0x108 = 0.016666668f;
	m_unk0x140 = 0;
	m_unk0x14c = NULL;
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

// FUNCTION: LEGORACERS 0x00428230
void RaceCameraController::FUN_00428230(RaceState::Racer* p_unk0x04)
{
	if (m_unk0x0d4 != p_unk0x04) {
		m_unk0x0d4 = p_unk0x04;
		m_unk0x0d4->m_unk0x018.m_unk0x044->VTable0x04(&m_unk0x0e4);
		LegoU32 flags = m_unk0x0d4->m_unk0xc70.m_unk0x014;
		m_unk0x120 = 1.0f;
		m_unk0x11c = flags & 1;
		GolAnimatedEntity* entity = m_unk0x0d4->m_unk0x018.m_unk0x044;
		m_unk0x0d8.m_x = entity->GetOrientation().m_rows[0].m_x;
		m_unk0x0d8.m_y = entity->GetOrientation().m_rows[0].m_y;
		m_unk0x0d8.m_z = entity->GetOrientation().m_rows[0].m_z;
	}
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

// STUB: LEGORACERS 0x00428500
GolVec3* RaceCameraController::FUN_00428500(GolVec3* p_unk0x04)
{
	GolVec3* result = p_unk0x04;

	if (m_unk0x002 == 3) {
		GolVec3* source = &m_unk0x0d8;
		p_unk0x04->m_x = source->m_x;
		p_unk0x04->m_y = source->m_y;
		p_unk0x04->m_z = source->m_z;
	}
	else {
		p_unk0x04->m_x = m_unk0x048.m_rows[2].m_x;
		p_unk0x04->m_y = m_unk0x048.m_rows[2].m_y;
		p_unk0x04->m_z = m_unk0x048.m_rows[2].m_z;
	}

	return result;
}

// STUB: LEGORACERS 0x00428540
void RaceCameraController::FUN_00428540(LegoFloat p_unk0x04)
{
	if (m_unk0x0d4 == NULL) {
		m_unk0x000 = TRUE;
		return;
	}

	if (m_camera->m_trackedEntity) {
		m_camera->UpdateFromTrackedEntity();
		return;
	}

	if (p_unk0x04 <= 0.0f) {
		if (!(m_unk0x000 & 1)) {
			return;
		}
		p_unk0x04 = 0.0f;
	}

	m_unk0x001 = m_unk0x000;
	m_unk0x000 &= 0xf0;
	if (p_unk0x04 <= 100.0f) {
		m_unk0x0cc = p_unk0x04;
	}
	else {
		m_unk0x0cc = 100.0f;
	}

	m_unk0x0d0 = static_cast<LegoS32>(m_unk0x0cc);
	FUN_00427e80();

	if (m_unk0x002) {
		m_unk0x088 = m_unk0x048;
		m_unk0x0ac = m_unk0x06c;
		m_unk0x0b8 = m_unk0x078;
	}

	switch (m_unk0x002) {
	case 0: {
		m_unk0x0d4->m_unk0x018.m_unk0x044->VTable0x04(&m_unk0x0e4);

		if (m_unk0x0c8 == 0.0f) {
			GolMatrix34 previousBasis;
			previousBasis.m_m[0][0] = m_unk0x088.m_m[0][0];
			previousBasis.m_m[0][1] = m_unk0x088.m_m[0][1];
			previousBasis.m_m[0][2] = m_unk0x088.m_m[0][2];
			previousBasis.m_m[1][0] = m_unk0x088.m_m[1][0];
			previousBasis.m_m[1][1] = m_unk0x088.m_m[1][1];
			previousBasis.m_m[1][2] = m_unk0x088.m_m[1][2];
			previousBasis.m_m[2][0] = m_unk0x088.m_m[2][0];
			previousBasis.m_m[2][1] = m_unk0x088.m_m[2][1];
			previousBasis.m_m[2][2] = m_unk0x088.m_m[2][2];
			GolMath::FUN_1002f5a0(previousBasis, &m_unk0x0b8);

			GolMatrix34 currentBasis;
			currentBasis.m_m[0][0] = m_unk0x008.m_m[0][0];
			currentBasis.m_m[0][1] = m_unk0x008.m_m[0][1];
			currentBasis.m_m[0][2] = m_unk0x008.m_m[0][2];
			currentBasis.m_m[1][0] = m_unk0x008.m_m[1][0];
			currentBasis.m_m[1][1] = m_unk0x008.m_m[1][1];
			currentBasis.m_m[1][2] = m_unk0x008.m_m[1][2];
			currentBasis.m_m[2][0] = m_unk0x008.m_m[2][0];
			currentBasis.m_m[2][1] = m_unk0x008.m_m[2][1];
			currentBasis.m_m[2][2] = m_unk0x008.m_m[2][2];
			GolMath::FUN_1002f5a0(currentBasis, &m_unk0x038);
		}

		m_unk0x0c8 += m_unk0x0cc;
		LegoFloat amount;
		if (m_unk0x0c8 <= 2000.0f) {
			amount = m_unk0x0c8 * 0.00050000002f;
		}
		else {
			m_unk0x0c8 = 2000.0f;
			amount = 1.0f;
		}

		m_unk0x06c.m_x = (m_unk0x02c.m_x - m_unk0x0ac.m_x) * amount + m_unk0x0ac.m_x;
		m_unk0x06c.m_y = (m_unk0x02c.m_y - m_unk0x0ac.m_y) * amount + m_unk0x0ac.m_y;
		m_unk0x06c.m_z = (m_unk0x02c.m_z - m_unk0x0ac.m_z) * amount + m_unk0x0ac.m_z;
		GolMath::FUN_1002f890(m_unk0x0b8, m_unk0x038, amount, &m_unk0x078);
		GolMath::FUN_00449340(&m_unk0x078, &m_unk0x048.m_m[0][0]);
		FUN_00427d30();
		FUN_00427c00();
		return;
	}
	case 1:
	case 3: {
		RaceState::Racer* racer = m_unk0x0d4;
		GolAnimatedEntity* entity = racer->m_unk0x018.m_unk0x044;
		GolVec3 targetPosition;
		entity->VTable0x04(&targetPosition);

		GolVec3 desiredDirection = entity->GetOrientation().m_rows[0];
		if (desiredDirection.m_x == 0.0f && desiredDirection.m_y == 0.0f) {
			if (m_unk0x0d8.m_x == 0.0f && m_unk0x0d8.m_y == 0.0f) {
				m_unk0x0d8.m_x = 1.0f;
				m_unk0x0d8.m_y = 0.0f;
				m_unk0x0d8.m_z = 0.0f;
			}
			desiredDirection = m_unk0x0d8;
		}
		desiredDirection.m_z = 0.0f;

		GolVec2 desiredDirection2D;
		desiredDirection2D.m_x = desiredDirection.m_x;
		desiredDirection2D.m_y = desiredDirection.m_y;
		GolMath::NormalizeVector2(desiredDirection2D, &desiredDirection2D);
		desiredDirection.m_x = desiredDirection2D.m_x;
		desiredDirection.m_y = desiredDirection2D.m_y;

		if (m_unk0x0d8.m_z != 0.0f) {
			m_unk0x0d8.m_z = 0.0f;
			GolVec2 direction2D;
			direction2D.m_x = m_unk0x0d8.m_x;
			direction2D.m_y = m_unk0x0d8.m_y;
			GolMath::NormalizeVector2(direction2D, &direction2D);
			m_unk0x0d8.m_x = direction2D.m_x;
			m_unk0x0d8.m_y = direction2D.m_y;
		}

		if (m_unk0x001 & 1) {
			m_unk0x0f4 = 0.0f;
			m_unk0x0d8 = desiredDirection;
		}
		else {
			if (racer->m_unk0x3e8.m_flags0x6c0 & RaceState::Racer::Field0x3e8::c_flags0x6c0Bit1) {
				desiredDirection = m_unk0x0d8;
			}
			else {
				LegoFloat turnAmount;
				if (racer->m_unk0x3e8.m_unk0x64c == 0.0f) {
					turnAmount = 0.0f;
				}
				else {
					turnAmount = racer->m_unk0x3e8.m_unk0x618 * 80.0f / racer->m_unk0x3e8.m_unk0x64c;
					if (turnAmount < -0.30000001f) {
						turnAmount = -0.30000001f;
					}
					else if (turnAmount > 0.30000001f) {
						turnAmount = 0.30000001f;
					}
				}

				m_unk0x0f4 = turnAmount + 1.0f / (m_unk0x104 * m_unk0x0cc + 1.0f) * (m_unk0x0f4 - turnAmount);

				LegoFloat turnSin;
				LegoFloat turnCos;
				GolMath::FUN_00449170(m_unk0x0f4, &turnSin, &turnCos);

				LegoFloat oldX = desiredDirection.m_x;
				desiredDirection.m_x = turnCos * desiredDirection.m_x - turnSin * desiredDirection.m_y;
				desiredDirection.m_y = turnCos * desiredDirection.m_y + turnSin * oldX;

				LegoFloat currentAngle = FUN_00428f40(m_unk0x0d8.m_x, m_unk0x0d8.m_y);
				LegoFloat desiredAngle = FUN_00428f40(desiredDirection.m_x, desiredDirection.m_y);
				LegoFloat delta = currentAngle - desiredAngle;
				if (delta < -0.014f || delta > 0.014f) {
					while (delta < -3.1415927f) {
						delta += 6.2831855f;
					}
					while (delta > 3.1415927f) {
						delta -= 6.2831855f;
					}

					LegoFloat angleAmount = 1.0f / (m_unk0x108 * m_unk0x0cc + 1.0f);
					LegoFloat angle = delta * angleAmount + desiredAngle;
					GolMath::FUN_00449170(angle, &desiredDirection.m_y, &desiredDirection.m_x);
				}
			}

			LegoFloat positionAmount = 1.0f / (m_unk0x100 * m_unk0x0cc + 1.0f);
			targetPosition.m_x = (m_unk0x0e4.m_x - targetPosition.m_x) * positionAmount + targetPosition.m_x;
			targetPosition.m_y = (m_unk0x0e4.m_y - targetPosition.m_y) * positionAmount + targetPosition.m_y;
			targetPosition.m_z = (m_unk0x0e4.m_z - targetPosition.m_z) * positionAmount + targetPosition.m_z;
		}
		m_unk0x0e4 = targetPosition;

		if (m_unk0x11c) {
			m_unk0x11c = racer->m_unk0xc70.m_unk0x014 & RaceState::Racer::Field0xc70::c_flags0x014Bit0;
		}
		else {
			m_unk0x11c = racer->m_unk0xc70.m_unk0x014 & RaceState::Racer::Field0xc70::c_flags0x014Bit0;
			if (m_unk0x11c) {
				switch (racer->m_unk0xd68) {
				case 0:
					m_unk0x120 = -0.2f;
					break;
				case 1:
					m_unk0x120 = -0.4f;
					break;
				case 2:
					m_unk0x120 = -0.6f;
					break;
				case 3:
					m_unk0x120 = 1.0f;
					break;
				default:
					break;
				}
			}
		}

		LegoFloat cameraDistance;
		if (m_unk0x120 >= 1.0f) {
			cameraDistance = m_unk0x118;
		}
		else {
			LegoFloat transitionStep;
			if (m_unk0x005) {
				transitionStep = m_unk0x0cc * 0.0040000002f;
			}
			else {
				transitionStep = m_unk0x0cc * 0.0020000001f;
			}
			m_unk0x120 += transitionStep;

			if (m_unk0x120 <= 1.0f) {
				cameraDistance = m_unk0x120 * m_unk0x118;
				if (m_unk0x120 < 0.0f) {
					cameraDistance = -cameraDistance;
				}
				if (cameraDistance < 12.0f) {
					cameraDistance = 12.0f;
				}
			}
			else {
				m_unk0x120 = 1.0f;
				cameraDistance = m_unk0x118;
			}
		}

		if (desiredDirection.m_x != 0.0f || desiredDirection.m_y != 0.0f) {
			m_unk0x0d8 = desiredDirection;
		}

		GolVec3 up;
		up.m_x = 0.0f;
		up.m_y = 0.0f;
		up.m_z = -1.0f;
		m_unk0x0d8.m_z = 0.0f;

		GolVec2 direction2D;
		direction2D.m_x = m_unk0x0d8.m_x;
		direction2D.m_y = m_unk0x0d8.m_y;
		GolMath::NormalizeVector2(direction2D, &direction2D);
		m_unk0x0d8.m_x = direction2D.m_x;
		m_unk0x0d8.m_y = direction2D.m_y;

		LegoFloat verticalOffset = m_unk0x10c;
		LegoFloat height;
		GolVec3 cameraOffset;
		if (m_unk0x002 == 3) {
			m_unk0x0c8 += m_unk0x0cc;
			if (m_unk0x0c8 <= 2000.0f) {
				LegoFloat profileAmount = 1.0f - m_unk0x0c8 * 0.00050000002f;
				cameraDistance = m_unk0x130 * profileAmount + m_unk0x118;
				height = m_unk0x128 * profileAmount + m_unk0x110;
				verticalOffset = m_unk0x124 * profileAmount + m_unk0x10c;
				LegoFloat sideDistance = m_unk0x12c * profileAmount + m_unk0x114;

				LegoFloat turnSin;
				LegoFloat turnCos;
				GolMath::FUN_00449170(m_unk0x0c8 * 0.0015707964f, &turnSin, &turnCos);
				cameraOffset.m_x = (m_unk0x0d8.m_x * turnCos - m_unk0x0d8.m_y * turnSin) * sideDistance;
				cameraOffset.m_y = (m_unk0x0d8.m_x * turnSin + m_unk0x0d8.m_y * turnCos) * sideDistance;
			}
			else {
				m_unk0x0c8 = 2000.0f;
				cameraDistance = m_unk0x118;
				cameraOffset.m_x = -(m_unk0x114 * m_unk0x0d8.m_x);
				cameraOffset.m_y = -(m_unk0x0d8.m_y * m_unk0x114);
				height = m_unk0x110;
			}
		}
		else {
			cameraOffset.m_x = m_unk0x114 * m_unk0x0d8.m_x;
			cameraOffset.m_y = m_unk0x0d8.m_y * m_unk0x114;
			height = m_unk0x110;
		}

		cameraOffset.m_z = -height;
		if (m_unk0x001 & 1) {
			m_unk0x02c.m_x = m_unk0x0e4.m_x - cameraOffset.m_x * cameraDistance;
			m_unk0x02c.m_y = m_unk0x0e4.m_y - cameraOffset.m_y * cameraDistance;
			m_unk0x02c.m_z = m_unk0x0e4.m_z - (cameraOffset.m_z - verticalOffset) * cameraDistance;
		}
		else {
			m_unk0x02c.m_x = m_unk0x0e4.m_x - m_unk0x088.m_rows[2].m_x * cameraDistance;
			m_unk0x02c.m_y = m_unk0x0e4.m_y - m_unk0x088.m_rows[2].m_y * cameraDistance;
			m_unk0x02c.m_z = m_unk0x0e4.m_z - (m_unk0x088.m_rows[2].m_z - verticalOffset) * cameraDistance;
		}

		FUN_004282d0(&cameraOffset, &up, &m_unk0x008);
		FUN_004280a0();
		return;
	}
	case 2: {
		RaceState::Racer* racer = m_unk0x0d4;
		GolAnimatedEntity* entity = racer->m_unk0x018.m_unk0x044;
		entity->VTable0x04(&m_unk0x0e4);

		GolVec3 right = entity->GetOrientation().m_rows[0];
		GolVec3 up = entity->GetOrientation().m_rows[2];
		up.m_x = -up.m_x;
		up.m_y = -up.m_y;
		up.m_z = -up.m_z;
		FUN_004282d0(&right, &up, &m_unk0x008);

		entity->VTable0x04(&m_unk0x02c);
		if (m_unk0x005) {
			m_unk0x02c.m_z += 6.0f;
		}
		else {
			m_unk0x02c.m_z += 10.0f;
		}

		FUN_004280a0();
		return;
	}
	default:
		return;
	}
}

// STUB: LEGORACERS 0x00428f40
LegoFloat RaceCameraController::FUN_00428f40(LegoFloat p_unk0x04, LegoFloat p_unk0x08)
{
	LegoFloat absY = p_unk0x08;
	if (absY < 0.0f) {
		absY = -absY;
	}

	LegoFloat absX = p_unk0x04;
	if (absX < 0.0f) {
		absX = -absX;
	}

	if (absY >= absX) {
		if (p_unk0x08 <= 0.0f) {
			return -static_cast<LegoFloat>(acos(p_unk0x04));
		}
		return static_cast<LegoFloat>(acos(p_unk0x04));
	}

	if (p_unk0x04 <= 0.0f) {
		return static_cast<LegoFloat>(acos(p_unk0x08)) + 1.5707964f;
	}
	return 1.5707964f - static_cast<LegoFloat>(acos(p_unk0x08));
}
