#include "golmodelentity.h"

#include "golmaterial.h"
#include "golmodelbase.h"
#include "material/materialtable.h"
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

// FUNCTION: GOLDP 0x10027b50
// FUNCTION: LEGORACERS 0x00411150
GolModelEntity::GolModelEntity()
{
	LegoU32 i;

	m_scale = 1.0f;
	m_radius = -1.0f;
	m_flags = 0;
	m_textureScrollU = 0;
	m_textureScrollV = 0;
	m_textureScrollSpeedU = 0;
	m_textureScrollSpeedV = 0;
	for (i = 0; i < sizeOfArray(m_models); i++) {
		m_models[i] = NULL;
		m_modelDistances[i] = g_negativeOneFloat;
		m_materialTables[i] = NULL;
	}
}

// FUNCTION: GOLDP 0x10027bb0
// FUNCTION: LEGORACERS 0x004111b0
void GolModelEntity::SetPrimaryModel(GolModelBase* p_model, LegoFloat p_modelDistance)
{
	if (m_flags & c_flagBit0) {
		ResetModelState();
	}

	m_models[0] = p_model;
	m_textureScrollU = 0;
	m_textureScrollV = 0;
	m_textureScrollSpeedU = 0;
	m_textureScrollSpeedV = 0;
	m_modelDistances[0] = p_modelDistance;
	m_scale = 1.0f;
	m_radius = -1.0f;
	m_flags |= c_flagBit0;
}

// FUNCTION: GOLDP 0x10027c00
// FUNCTION: LEGORACERS 0x00411200
void GolModelEntity::ResetModelState()
{
	LegoU32 i;

	m_scale = 1.0f;
	m_flags = 0;
	m_textureScrollU = 0;
	m_textureScrollV = 0;
	m_textureScrollSpeedU = 0;
	m_textureScrollSpeedV = 0;
	for (i = 0; i < sizeOfArray(m_models); i++) {
		m_models[i] = NULL;
		m_modelDistances[i] = g_negativeOneFloat;
		m_materialTables[i] = NULL;
	}

	GolOrientedEntity::Reset();
}

// FUNCTION: GOLDP 0x10027c50
// FUNCTION: LEGORACERS 0x00411250
void GolModelEntity::AddModel(GolModelBase* p_model, LegoFloat p_modelDistance)
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
void GolModelEntity::SelectLod(const GolVec3& p_vector, GolModelEntity::ResultStruct* p_result)
{
	LegoU32 i;
	LegoFloat* threshold;

	i = 0;
	threshold = m_modelDistances;
	p_result->m_lodIndex = 0;

	if (*threshold != g_maxFloat) {
		GolVec3 v3;
		GetPosition(&v3);
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
void GolModelEntity::ComputeVisibility(const GolViewFrustum& p_view, ResultStruct* p_result)
{
	LegoU32 i;
	LegoFloat* threshold;
	GolVec3 position;

	i = 0;
	threshold = m_modelDistances;
	if (*threshold != g_maxFloat) {
		GetPosition(&position);
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

	GetBoundsCenter(&position);
	p_result->m_visibility = p_view.ClassifySphere(position, GetBoundsRadius());
}

// FUNCTION: GOLDP 0x10027e70
void GolModelEntity::BuildModelMatrix(GolMatrix4* p_dest, LegoU32 p_index)
{
	GolModelBase* model = m_models[p_index];
	CopyScaledOrientationTo(p_dest, model->GetScale() * m_scale);
}

// FUNCTION: GOLDP 0x10027e90
// FUNCTION: LEGORACERS 0x004113c0
void GolModelEntity::UpdateBounds()
{
	ComputeBoundsFromModel(0);
}

// FUNCTION: GOLDP 0x10027ea0
// FUNCTION: LEGORACERS 0x004113d0
void GolModelEntity::ComputeBoundsFromModel(LegoU32 p_index)
{
	GolModelBase* model = m_models[p_index];
	if (model == NULL) {
		SetBoundsRadius(0.0f);
		return;
	}

	LegoFloat scale = m_scale;
	GolVec3 center = model->GetCenter();
	LegoFloat radius = model->GetRadius();
	center.m_x *= scale;
	center.m_y *= scale;
	center.m_z *= scale;
	GolVec3 position;
	LocalToWorld(center, &position);
	SetBoundsCenterAndSpan(position);
	SetBoundsRadius(m_scale * radius);
}

// FUNCTION: GOLDP 0x10027f40
// FUNCTION: LEGORACERS 0x00411470
void GolModelEntity::Update(LegoS32 p_elapsed)
{
	GolVec3 v;
	GetPosition(&v);
	LegoFloat f = static_cast<LegoFloat>(p_elapsed);
	v += m_velocity * f;
	SetPosition(v);
	m_radius = -1.0f;
	if (m_textureScrollSpeedU != 0 || m_textureScrollSpeedV != 0) {
		m_textureScrollU += m_textureScrollSpeedU * p_elapsed;
		m_textureScrollV += m_textureScrollSpeedV * p_elapsed;
	}
}

// FUNCTION: GOLDP 0x10027fe0
// FUNCTION: LEGORACERS 0x00411510
void GolModelEntity::GetModelBounds(LegoU32 p_index, GolVec3* p_destVec, LegoFloat* p_destScalar)
{
	if (!p_index) {
		GetBoundsCenter(p_destVec);
		*p_destScalar = GetBoundsRadius();
	}
	else {
		ComputeBoundsFromModel(p_index);
		p_destVec->m_x = m_center.m_x;
		p_destVec->m_y = m_center.m_y;
		p_destVec->m_z = m_center.m_z;
		*p_destScalar = m_radius;
	}
}

// FUNCTION: GOLDP 0x10028030
// FUNCTION: LEGORACERS 0x00411560
void GolModelEntity::Draw(GolRenderDevice& p_renderer)
{
	if (m_flags & (c_flagBit3 | c_flagBit2)) {
		if (m_textureScrollU == 0 && m_textureScrollV == 0) {
			if (m_flags & c_flagBit2) {
				p_renderer.DrawModelEntityEnvironmentMapped(this);
				return;
			}
			else {
				p_renderer.DrawModelEntity(this);
				return;
			}
		}
		else {
			LegoFloat scrollU = GetTextureScrollU();
			LegoFloat scrollV = GetTextureScrollV();
			p_renderer.DrawModelEntityWithUvOffset(this, scrollU, scrollV);
			return;
		}
	}

	p_renderer.DrawModelEntity(this);
}

// FUNCTION: GOLDP 0x100280c0
// FUNCTION: LEGORACERS 0x004115f0
void GolModelEntity::ApplyColorTransform(ColorTransform* p_transform)
{
	for (LegoU32 i = 0; i < sizeOfArray(m_models); i++) {
		GolModelBase* model = m_models[i];
		if (model == NULL) {
			break;
		}
		model->ApplyColorTransform(*p_transform);
	}
}

// FUNCTION: GOLDP 0x100280f0
// FUNCTION: LEGORACERS 0x00411620
void GolModelEntity::ClearColorTransform()
{
	for (LegoU32 i = 0; i < sizeOfArray(m_models); i++) {
		if (m_models[i] == NULL) {
			break;
		}
		m_models[i]->ClearColorTransform();
	}
}

// FUNCTION: LEGORACERS 0x00411640
LegoFloat GolModelEntity::GetTextureScrollU() const
{
#ifdef BUILDING_GOL
	return static_cast<LegoFloat>(m_textureScrollU) * (1.0f / 65536.0f);
#else
	return static_cast<LegoFloat>(m_textureScrollU) * g_unk0x004af7b4;
#endif
}

// FUNCTION: LEGORACERS 0x00411660
LegoFloat GolModelEntity::GetTextureScrollV() const
{
#ifdef BUILDING_GOL
	return static_cast<LegoFloat>(m_textureScrollV) * (1.0f / 65536.0f);
#else
	return static_cast<LegoFloat>(m_textureScrollV) * g_unk0x004af7b4;
#endif
}

// FUNCTION: LEGORACERS 0x00411680
void GolModelEntity::SetTextureScrollU(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
	m_textureScrollU = static_cast<LegoU16>(p_arg * 65536.0f);
}

// FUNCTION: LEGORACERS 0x004116b0
void GolModelEntity::SetTextureScrollV(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
	m_textureScrollV = static_cast<LegoU16>(p_arg * 65536.0f);
}

// FUNCTION: LEGORACERS 0x004116e0
LegoFloat GolModelEntity::GetTextureScrollSpeedU() const
{
	return static_cast<LegoFloat>(static_cast<LegoS32>(m_textureScrollSpeedU)) * g_unk0x004af7b8;
}

// FUNCTION: LEGORACERS 0x004116f0
LegoFloat GolModelEntity::GetTextureScrollSpeedV() const
{
	return static_cast<LegoFloat>(static_cast<LegoS32>(m_textureScrollSpeedV)) * g_unk0x004af7b8;
}

// FUNCTION: GOLDP 0x10028110
// FUNCTION: LEGORACERS 0x00411700
void GolModelEntity::SetTextureScrollSpeedU(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
	m_textureScrollSpeedU = static_cast<LegoS32>(p_arg * 65.536f);
}

// FUNCTION: GOLDP 0x10028140
// FUNCTION: LEGORACERS 0x00411730
void GolModelEntity::SetTextureScrollSpeedV(LegoFloat p_arg)
{
	m_flags |= c_flagBit3;
	m_textureScrollSpeedV = static_cast<LegoS32>(p_arg * 65.536f);
}

// FUNCTION: GOLDP 0x10028170
// FUNCTION: LEGORACERS 0x00411760
LegoBool32 GolModelEntity::GetKind()
{
	MaterialTable* materialTable = m_materialTables[0];
	if (materialTable == NULL) {
		GolModelBase* model = m_models[0];
		if (model == NULL) {
			return FALSE;
		}
		materialTable = model->GetMaterialTable();
	}

	for (LegoU32 i = 0; i < materialTable->m_count; i++) {
		GolMaterial* material = static_cast<GolMaterial*>(materialTable->GetEntry(i));
		if (material != NULL &&
			(material->GetFlags() & (GolMaterial::c_flagAlphaBlend | GolMaterial::c_flagTransparent))) {
			return TRUE;
		}
	}

	return FALSE;
}

// FUNCTION: GOLDP 0x1001d700 FOLDED
// FUNCTION: LEGORACERS 0x004113b0 FOLDED
GolSceneNode* GolModelEntity::GetSceneNode(undefined4)
{
	return NULL;
}

// FUNCTION: GOLDP 0x1002c020 FOLDED
// FUNCTION: LEGORACERS 0x004513d0 FOLDED
void GolModelEntity::ApplyPartAnimation(undefined4)
{
	// empty
}
