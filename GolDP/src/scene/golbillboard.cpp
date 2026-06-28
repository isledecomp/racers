#include "scene/golbillboard.h"

#include "duskwindbananarelic0x24.h"
#include "render/golrenderdevice.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(GolBillboard, 0x4c)
DECOMP_SIZE_ASSERT(GolBillboard::Field0x2c, 0x0c)

// GLOBAL: GOLDP 0x100574fc
float g_pontoonMaxFloat = FLT_MAX;

// FUNCTION: GOLDP 0x10029df0
GolBillboard::GolBillboard()
{
	m_position = NULL;
	m_positionContainer = NULL;
	m_unk0x30.m_x = 0.0f;
	m_unk0x30.m_y = 0.0f;
	m_unk0x30.m_z = 1.0f;
	m_flags = 0;
	m_positionIndex = 0;
	m_width = 0.0f;
	m_height = 0.0f;
	m_maxDistanceSquared = g_pontoonMaxFloat; // std::numeric_limits<float>::max();
}

// FUNCTION: GOLDP 0x10029e30
void GolBillboard::VTable0x4c(
	DuskwindBananaRelic0x24* p_position,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoFloat p_maxDistanceSquared
)
{
#define SQR(V) ((V) * (V))
	LegoFloat len = sqrtf(SQR(p_width / 2.0f) + SQR(p_height / 2.0f));
#undef SQR

	m_position = p_position;
	m_width = p_width;
	m_height = p_height;
	m_flags = 1;
	m_maxDistanceSquared = p_maxDistanceSquared;
	FUN_10026fa0(len);
}

// FUNCTION: GOLDP 0x10029e90
void GolBillboard::FUN_10029e90(
	MaterialTable0x0c* p_container,
	LegoS32 p_index,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoFloat p_maxDistanceSquared
)
{
	m_positionContainer = p_container;
	m_positionIndex = static_cast<LegoU16>(p_index);
	VTable0x4c(
		static_cast<DuskwindBananaRelic0x24*>(p_container->GetPosition(p_index)),
		p_width,
		p_height,
		p_maxDistanceSquared
	);
	m_flags |= c_flagBit2;
}

// FUNCTION: GOLDP 0x10029ed0
void GolBillboard::VTable0x50()
{
	m_position = NULL;
	m_flags = 0;
	m_width = 0;
	m_height = 0;
}

// FUNCTION: GOLDP 0x10029ee0
void GolBillboard::VTable0x14(const GolViewFrustum& p_view, ResultStruct* p_result)
{
	GolVec3 position;
	FUN_100286d0(&position);
	p_result->m_lodIndex = 0;

	if (m_maxDistanceSquared != g_pontoonMaxFloat) {
		LegoFloat distanceSquared = position.DistanceSquaredTo(p_view.m_position);
		if (distanceSquared == 0.0f || distanceSquared > m_maxDistanceSquared) {
			p_result->m_visibility = 0;
			return;
		}
	}

	p_result->m_visibility = p_view.ClassifySphere(position, FUN_10028710());
}

// FUNCTION: GOLDP 0x10026fa0 FOLDED
void GolBillboard::FUN_10026fa0(LegoFloat p_scalar)
{
	m_radius = p_scalar;
	m_minX = m_center.m_x - p_scalar;
	m_maxX = p_scalar + m_center.m_x;
}

// FUNCTION: GOLDP 0x10029fa0
void GolBillboard::FUN_10029fa0(const GolVec3& p_arg1, LegoBool32* p_result)
{
	GolVec3 position;

	p_result[1] = FALSE;
	FUN_100286d0(&position);

	LegoFloat distanceSquared = position.DistanceSquaredTo(p_arg1);

	if (distanceSquared != 0.0f && distanceSquared <= m_maxDistanceSquared) {
		p_result[0] = TRUE;
	}
	else {
		p_result[0] = FALSE;
	}
}

// FUNCTION: GOLDP 0x1002a020
DuskwindBananaRelic0x24* GolBillboard::FUN_1002a020()
{
	if (m_flags & c_flagBit2) {
		m_position = static_cast<DuskwindBananaRelic0x24*>(m_positionContainer->GetPosition(m_positionIndex));
	}

	return m_position;
}

// FUNCTION: GOLDP 0x1002a040
void GolBillboard::VTable0x1c(GolRenderDevice& p_renderer)
{
	p_renderer.VTable0xb4(*this);
}

// FUNCTION: GOLDP 0x1002a060
LegoBool32 GolBillboard::VTable0x20()
{
	if (m_flags & c_flagBit2) {
		m_position = static_cast<DuskwindBananaRelic0x24*>(m_positionContainer->GetPosition(m_positionIndex));
	}

	return m_position->GetUnk0x08() & 0x1100;
}
