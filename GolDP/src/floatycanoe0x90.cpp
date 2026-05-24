#include "floatycanoe0x90.h"

#include "igdbmodel0x40.h"
#include "whitefalcon0x140.h"

#include <float.h>

DECOMP_SIZE_ASSERT(FloatyCanoe0x90, 0x90)

// GLOBAL: GOLDP 0x1005726c
static LegoFloat g_negativeOneFloat = -1.0f;

// GLOBAL: GOLDP 0x10057268
static const LegoFloat g_maxFloat = FLT_MAX;

// FUNCTION: GOLDP 0x10027b50
FloatyCanoe0x90::FloatyCanoe0x90()
{
	LegoU32 i;

	m_unk0x58 = 1.0f;
	m_v1.m_x = -1.0f;
	m_flags = 0;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	for (i = 0; i < 3; i++) {
		m_unk0x78[i] = NULL;
		m_unk0x84[i] = g_negativeOneFloat;
		m_unk0x6c[i] = NULL;
	}
}

// FUNCTION: GOLDP 0x10027bb0
void FloatyCanoe0x90::VTable0x50(IGdbModel0x40* p_value, LegoFloat p_scalar)
{
	if (m_flags & c_flagBit0) {
		VTable0x54();
	}
	m_unk0x78[0] = p_value;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	m_unk0x84[0] = p_scalar;
	m_unk0x58 = 1.0f;
	m_v1.m_x = -1.0f;
	m_flags |= c_flagBit0;
}

// FUNCTION: GOLDP 0x10027c00
void FloatyCanoe0x90::VTable0x54()
{
	LegoU32 i;

	m_unk0x58 = 1.0f;
	m_flags = 0;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	for (i = 0; i < 3; i++) {
		m_unk0x78[i] = NULL;
		m_unk0x84[i] = g_negativeOneFloat;
		m_unk0x6c[i] = NULL;
	}
	FloatyBuoy0x58::Reset();
}

// FUNCTION: GOLDP 0x10027c50
void FloatyCanoe0x90::FUN_10027c50(IGdbModel0x40* p_value, LegoFloat p_scalar)
{
	LegoU32 i;
	LegoU32 j;

	i = 0;
	for (; i < 2; i++) {
		if (!m_unk0x78[i]) {
			break;
		}
		if (p_scalar >= m_unk0x84[i]) {
			continue;
		}
		for (j = 2; j > i; j--) {
			m_unk0x78[j] = m_unk0x78[j - 1];
			m_unk0x84[j] = m_unk0x84[j - 1];
		}
		break;
	}
	m_unk0x78[i] = p_value;
	m_unk0x84[i] = p_scalar;
}

// FUNCTION: GOLDP 0x10027cc0
void FloatyCanoe0x90::FUN_10027cc0(const GolVec3& p_vector, FloatyCanoe0x90::ResultStruct* p_result)
{
	LegoU32 i;
	LegoFloat* threshold;

	i = 0;
	threshold = m_unk0x84;
	p_result->m_lodIndex = 0;

	if (*threshold != g_maxFloat) {
		GolVec3 v3;
		VTable0x04(&v3);
		LegoFloat distanceSquared = GOLVECTOR3_DISTANCE_SQUARED(p_vector, v3);

		for (; distanceSquared > *threshold;) {
			i++;
			threshold++;
			if (i >= 3) {
				p_result->m_lodIndex = 3;
				p_result->m_visibility = 0;
				return;
			}
		}
	}

	p_result->m_lodIndex = i;
	if (!m_unk0x78[i]) {
		p_result->m_visibility = 0;
	}
}

// FUNCTION: GOLDP 0x10027d80
void FloatyCanoe0x90::VTable0x14(const WhiteFalconView0xcc& p_view, ResultStruct* p_result)
{
	LegoU32 i;
	LegoFloat* threshold;
	GolVec3 position;

	i = 0;
	threshold = m_unk0x84;
	if (*threshold != g_maxFloat) {
		VTable0x04(&position);
		LegoFloat distanceSquared = position.DistanceSquaredTo(p_view.m_position);

		for (; distanceSquared > *threshold;) {
			i++;
			threshold++;
			if (i >= 3) {
				p_result->m_visibility = 0;
				return;
			}
		}
	}

	p_result->m_lodIndex = i;
	if (m_unk0x78[i] == NULL) {
		p_result->m_visibility = 0;
		return;
	}

	FUN_100286d0(&position);
	p_result->m_visibility = p_view.FUN_1002bc20(position, FUN_10028710());
}

// FUNCTION: GOLDP 0x10027e70
void FloatyCanoe0x90::FUN_10027e70(GolMatrix4* p_dest, LegoU32 p_index)
{
	IGdbModel0x40* model = m_unk0x78[p_index];
	FUN_10026fc0(p_dest, model->GetScale() * m_unk0x58);
}

// FUNCTION: GOLDP 0x10027e90
void FloatyCanoe0x90::VTable0x00()
{
	VTable0x4c(0);
}

// FUNCTION: GOLDP 0x10027ea0
void FloatyCanoe0x90::VTable0x4c(LegoU32 p_index)
{
	IGdbModel0x40* model = m_unk0x78[p_index];
	if (model == NULL) {
		FUN_10026fa0(0.0f);
		return;
	}

	LegoFloat scale = m_unk0x58;
	GolVec3 center = model->GetCenter();
	LegoFloat radius = model->GetRadius();
	center.m_x *= scale;
	center.m_y *= scale;
	center.m_z *= scale;
	GolVec3 position;
	VTable0x2c(center, &position);
	FUN_10026f70(position);
	FUN_10026fa0(m_unk0x58 * radius);
}

// FUNCTION: GOLDP 0x10027f40
void FloatyCanoe0x90::VTable0x10(LegoS32 p_scalar)
{
	GolVec3 v;
	VTable0x04(&v);
	LegoFloat f = static_cast<LegoFloat>(p_scalar);
	v += m_v2 * f;
	VTable0x08(v);
	m_v1.m_x = -1.0f;
	if (m_unk0x64 != 0 || m_unk0x68 != 0) {
		m_unk0x60 += m_unk0x64 * p_scalar;
		m_unk0x62 += m_unk0x68 * p_scalar;
	}
}

// FUNCTION: GOLDP 0x10027fe0
void FloatyCanoe0x90::FUN_10027fe0(undefined4 p_arg1, GolVec3* p_destVec, LegoFloat* p_destScalar)
{
	if (!p_arg1) {
		FUN_100286d0(p_destVec);
		*p_destScalar = FUN_10028710();
	}
	else {
		VTable0x4c(p_arg1);
		p_destVec->m_x = m_v0.m_x;
		p_destVec->m_y = m_v0.m_y;
		p_destVec->m_z = m_v0.m_z;
		*p_destScalar = m_v1.m_x;
	}
}

// FUNCTION: GOLDP 0x10028030
void FloatyCanoe0x90::VTable0x1c(WhiteFalcon0x140& p_renderer)
{
	if (m_flags & (c_flagBit3 | c_flagBit2)) {
		if (m_unk0x60 == 0 && m_unk0x62 == 0) {
			if (m_flags & c_flagBit2) {
				p_renderer.VTable0xa4(this);
				return;
			}
		}
		else {
			p_renderer.VTable0xa8(
				this,
				m_unk0x60 / static_cast<LegoFloat>(1 << 16),
				m_unk0x62 / static_cast<LegoFloat>(1 << 16)
			);
			return;
		}
	}
	p_renderer.VTable0x94(this);
}

// STUB: GOLDP 0x100280c0
void FloatyCanoe0x90::VTable0x24(TransformPayload0x20*)
{
	// TODO
	STUB(0x100280c0);
}

// STUB: GOLDP 0x100280f0
void FloatyCanoe0x90::VTable0x28()
{
	STUB(0x100280f0);

	LegoU32 i = 0;
	IGdbModel0x40** model = m_unk0x78;

	do {
		if (*model == NULL) {
			break;
		}
		(*model)->VTable0x40();
		i++;
		model++;
	} while (i < 3);
}

// FUNCTION: GOLDP 0x10028110
void FloatyCanoe0x90::FUN_10028110(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
	m_unk0x64 = static_cast<undefined4>(p_arg * 65.536f);
}

// FUNCTION: GOLDP 0x10028140
void FloatyCanoe0x90::FUN_10028140(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
	m_unk0x68 = static_cast<undefined4>(p_arg * 65.536f);
}

// STUB: GOLDP 0x10028170
undefined4 FloatyCanoe0x90::VTable0x20()
{
	// TODO
	STUB(0x10028170);
	return 0;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
WhiteFalconNode0x18* FloatyCanoe0x90::VTable0x58(undefined4)
{
	return 0;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
void FloatyCanoe0x90::VTable0x5c(undefined4)
{
	// empty
}
