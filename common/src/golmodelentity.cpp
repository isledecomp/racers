#include "golmodelentity.h"

#include "material/duskwindbananarelic0x24.h"
#include "mesh/golmodelbase.h"
#include "render/golrenderdevice.h"

#include <float.h>

DECOMP_SIZE_ASSERT(GolModelEntity, 0x90)

// GLOBAL: GOLDP 0x1005726c
// GLOBAL: LEGORACERS 0x004af750
const LegoFloat g_negativeOneFloat = -1.0f;

// GLOBAL: GOLDP 0x10057268
// GLOBAL: LEGORACERS 0x004af74c
const LegoFloat g_maxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004af7b4
const LegoFloat g_unk0x004af7b4 = 1.0f / 65536.0f;

// GLOBAL: LEGORACERS 0x004af7b8
const LegoFloat g_unk0x004af7b8 = 1000.0f / 65536.0f;

// GLOBAL: LEGORACERS 0x004af7bc
const LegoFloat g_unk0x004af7bc = 65.536f;

// FUNCTION: GOLDP 0x10027b50
// FUNCTION: LEGORACERS 0x00411150
GolModelEntity::GolModelEntity()
{
	LegoU32 i;

	m_unk0x58 = 1.0f;
	m_radius = -1.0f;
	m_flags = 0;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	for (i = 0; i < sizeOfArray(m_models); i++) {
		m_models[i] = NULL;
		m_modelDistances[i] = g_negativeOneFloat;
		m_materialTables[i] = NULL;
	}
}

// FUNCTION: GOLDP 0x10027bb0
// FUNCTION: LEGORACERS 0x004111b0
void GolModelEntity::VTable0x50(GolModelBase* p_model, LegoFloat p_modelDistance)
{
	if (m_flags & c_flagBit0) {
		VTable0x54();
	}

	m_models[0] = p_model;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	m_modelDistances[0] = p_modelDistance;
	m_unk0x58 = 1.0f;
	m_radius = -1.0f;
	m_flags |= c_flagBit0;
}

// FUNCTION: GOLDP 0x10027c00
// FUNCTION: LEGORACERS 0x00411200
void GolModelEntity::VTable0x54()
{
	LegoU32 i;

	m_unk0x58 = 1.0f;
	m_flags = 0;
	m_unk0x60 = 0;
	m_unk0x62 = 0;
	m_unk0x64 = 0;
	m_unk0x68 = 0;
	for (i = 0; i < sizeOfArray(m_models); i++) {
		m_models[i] = NULL;
		m_modelDistances[i] = g_negativeOneFloat;
		m_materialTables[i] = NULL;
	}

	GolOrientedEntity::Reset();
}

// FUNCTION: GOLDP 0x10027c50
// FUNCTION: LEGORACERS 0x00411250
void GolModelEntity::FUN_10027c50(GolModelBase* p_model, LegoFloat p_modelDistance)
{
	LegoU32 i;
	LegoU32 j;

	i = 0;
	for (; i < 2; i++) {
		if (!m_models[i]) {
			break;
		}
		if (p_modelDistance >= m_modelDistances[i]) {
			continue;
		}
		for (j = 2; j > i; j--) {
			m_models[j] = m_models[j - 1];
			m_modelDistances[j] = m_modelDistances[j - 1];
		}
		break;
	}
	m_models[i] = p_model;
	m_modelDistances[i] = p_modelDistance;
}

// FUNCTION: GOLDP 0x10027cc0
void GolModelEntity::FUN_10027cc0(const GolVec3& p_vector, GolModelEntity::ResultStruct* p_result)
{
	LegoU32 i;
	LegoFloat* threshold;

	i = 0;
	threshold = m_modelDistances;
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
	if (!m_models[i]) {
		p_result->m_visibility = 0;
	}
}

// FUNCTION: GOLDP 0x10027d80
// FUNCTION: LEGORACERS 0x004112c0
void GolModelEntity::VTable0x14(const GolViewFrustum& p_view, ResultStruct* p_result)
{
	LegoU32 i;
	LegoFloat* threshold;
	GolVec3 position;

	i = 0;
	threshold = m_modelDistances;
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
	if (m_models[i] == NULL) {
		p_result->m_visibility = 0;
		return;
	}

	FUN_100286d0(&position);
	p_result->m_visibility = p_view.FUN_1002bc20(position, FUN_10028710());
}

// FUNCTION: GOLDP 0x10027e70
void GolModelEntity::FUN_10027e70(GolMatrix4* p_dest, LegoU32 p_index)
{
	GolModelBase* model = m_models[p_index];
	FUN_10026fc0(p_dest, model->GetScale() * m_unk0x58);
}

// FUNCTION: GOLDP 0x10027e90
// FUNCTION: LEGORACERS 0x004113c0
void GolModelEntity::VTable0x00()
{
	VTable0x4c(0);
}

// FUNCTION: GOLDP 0x10027ea0
// FUNCTION: LEGORACERS 0x004113d0
void GolModelEntity::VTable0x4c(LegoU32 p_index)
{
	GolModelBase* model = m_models[p_index];
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
// FUNCTION: LEGORACERS 0x00411470
void GolModelEntity::VTable0x10(LegoS32 p_elapsed)
{
	GolVec3 v;
	VTable0x04(&v);
	LegoFloat f = static_cast<LegoFloat>(p_elapsed);
	v += m_velocity * f;
	VTable0x08(v);
	m_radius = -1.0f;
	if (m_unk0x64 != 0 || m_unk0x68 != 0) {
		m_unk0x60 += m_unk0x64 * p_elapsed;
		m_unk0x62 += m_unk0x68 * p_elapsed;
	}
}

// FUNCTION: GOLDP 0x10027fe0
// FUNCTION: LEGORACERS 0x00411510
void GolModelEntity::FUN_10027fe0(LegoU32 p_index, GolVec3* p_destVec, LegoFloat* p_destScalar)
{
	if (!p_index) {
		FUN_100286d0(p_destVec);
		*p_destScalar = FUN_10028710();
	}
	else {
		VTable0x4c(p_index);
		p_destVec->m_x = m_center.m_x;
		p_destVec->m_y = m_center.m_y;
		p_destVec->m_z = m_center.m_z;
		*p_destScalar = m_radius;
	}
}

// FUNCTION: GOLDP 0x10028030
// STUB: LEGORACERS 0x00411560
void GolModelEntity::VTable0x1c(GolRenderDevice& p_renderer)
{
	if (m_flags & (c_flagBit3 | c_flagBit2)) {
		if (m_unk0x60 == 0 && m_unk0x62 == 0) {
			if (m_flags & c_flagBit2) {
				p_renderer.VTable0xa4(this);
				return;
			}
		}
		else {
			LegoFloat value0x60 = FUN_00411640();
			LegoFloat value0x62 = FUN_00411660();
			p_renderer.VTable0xa8(this, value0x60, value0x62);
			return;
		}
	}

	p_renderer.VTable0x94(this);
}

// FUNCTION: GOLDP 0x100280c0
// FUNCTION: LEGORACERS 0x004115f0
void GolModelEntity::VTable0x24(ColorTransform0x20* p_transform)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_models); i++) {
		GolModelBase* model = m_models[i];
		if (model == NULL) {
			break;
		}
		model->VTable0x3c(*p_transform);
	}
}

// FUNCTION: GOLDP 0x100280f0
// FUNCTION: LEGORACERS 0x00411620
void GolModelEntity::VTable0x28()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_models); i++) {
		if (m_models[i] == NULL) {
			break;
		}
		m_models[i]->VTable0x40();
	}
}

// FUNCTION: LEGORACERS 0x00411640
LegoFloat GolModelEntity::FUN_00411640() const
{
#ifdef BUILDING_GOL
	return static_cast<LegoFloat>(m_unk0x60) * (1.0f / 65536.0f);
#else
	return static_cast<LegoFloat>(m_unk0x60) * g_unk0x004af7b4;
#endif
}

// FUNCTION: LEGORACERS 0x00411660
LegoFloat GolModelEntity::FUN_00411660() const
{
#ifdef BUILDING_GOL
	return static_cast<LegoFloat>(m_unk0x62) * (1.0f / 65536.0f);
#else
	return static_cast<LegoFloat>(m_unk0x62) * g_unk0x004af7b4;
#endif
}

// FUNCTION: LEGORACERS 0x00411680
void GolModelEntity::FUN_00411680(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
	m_unk0x60 = static_cast<LegoU16>(p_arg * g_unk0x004af7b8);
}

// FUNCTION: LEGORACERS 0x004116b0
void GolModelEntity::FUN_004116b0(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
	m_unk0x62 = static_cast<LegoU16>(p_arg * g_unk0x004af7b8);
}

// FUNCTION: LEGORACERS 0x004116e0
LegoFloat GolModelEntity::FUN_004116e0() const
{
	return static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x64)) * g_unk0x004af7b8;
}

// FUNCTION: LEGORACERS 0x004116f0
LegoFloat GolModelEntity::FUN_004116f0() const
{
	return static_cast<LegoFloat>(static_cast<LegoS32>(m_unk0x68)) * g_unk0x004af7b8;
}

// FUNCTION: GOLDP 0x10028110
// FUNCTION: LEGORACERS 0x00411700
void GolModelEntity::FUN_00411700(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
#ifdef BUILDING_GOL
	m_unk0x64 = static_cast<LegoS32>(p_arg * 65.536f);
#else
	m_unk0x64 = static_cast<LegoS32>(p_arg * g_unk0x004af7bc);
#endif
}

// FUNCTION: GOLDP 0x10028140
// FUNCTION: LEGORACERS 0x00411730
void GolModelEntity::FUN_00411730(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
#ifdef BUILDING_GOL
	m_unk0x68 = static_cast<LegoS32>(p_arg * 65.536f);
#else
	m_unk0x68 = static_cast<LegoS32>(p_arg * g_unk0x004af7bc);
#endif
}

// FUNCTION: GOLDP 0x10028170
// FUNCTION: LEGORACERS 0x00411760
LegoBool32 GolModelEntity::VTable0x20()
{
	GolModelMaterialTable* materialTable = m_materialTables[0];
	if (materialTable == NULL) {
		GolModelBase* model = m_models[0];
		if (model == NULL) {
			return FALSE;
		}
		materialTable = model->GetMaterialTable();
	}

	for (LegoU32 i = 0; i < materialTable->GetCount(); i++) {
		DuskwindBananaRelic0x24* material = materialTable->GetMaterial(i);
		if (material != NULL && (material->GetUnk0x08() & (DuskwindBananaRelic0x24::c_flag0x08Bit8 |
														   DuskwindBananaRelic0x24::c_flag0x08Bit12))) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
// FUNCTION: LEGORACERS 0x004113b0 FOLDED
GolSceneNode* GolModelEntity::VTable0x58(undefined4)
{
	return NULL;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolModelEntity::VTable0x5c(undefined4)
{
	// empty
}
