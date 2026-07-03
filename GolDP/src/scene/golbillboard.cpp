#include "scene/golbillboard.h"

#include "golmaterial.h"
#include "render/golrenderdevice.h"

#include <float.h>
#include <math.h>

DECOMP_SIZE_ASSERT(GolBillboard, 0x4c)
DECOMP_SIZE_ASSERT(GolBillboard::ManagedMaterialTable, 0x0c)

// GLOBAL: GOLDP 0x100574fc
float g_pontoonMaxFloat = FLT_MAX;

// FUNCTION: GOLDP 0x10029df0
GolBillboard::GolBillboard()
{
	m_material = NULL;
	m_materialTable = NULL;
	m_axis.m_x = 0.0f;
	m_axis.m_y = 0.0f;
	m_axis.m_z = 1.0f;
	m_flags = 0;
	m_materialIndex = 0;
	m_width = 0.0f;
	m_height = 0.0f;
	m_maxDistanceSquared = g_pontoonMaxFloat; // std::numeric_limits<float>::max();
}

// FUNCTION: GOLDP 0x10029e30
void GolBillboard::Configure(
	GolMaterial* p_position,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoFloat p_maxDistanceSquared
)
{
#define SQR(V) ((V) * (V))
	LegoFloat len = sqrtf(SQR(p_width / 2.0f) + SQR(p_height / 2.0f));
#undef SQR

	m_material = p_position;
	m_width = p_width;
	m_height = p_height;
	m_flags = 1;
	m_maxDistanceSquared = p_maxDistanceSquared;
	SetBoundsRadius(len);
}

// FUNCTION: GOLDP 0x10029e90
void GolBillboard::ConfigureFromMaterialTable(
	MaterialTable* p_container,
	LegoS32 p_index,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoFloat p_maxDistanceSquared
)
{
	m_materialTable = p_container;
	m_materialIndex = static_cast<LegoU16>(p_index);
	Configure(static_cast<GolMaterial*>(p_container->GetEntry(p_index)), p_width, p_height, p_maxDistanceSquared);
	m_flags |= c_flagMaterialAssignment;
}

// FUNCTION: GOLDP 0x10029ed0
void GolBillboard::SetPrimaryModel()
{
	m_material = NULL;
	m_flags = 0;
	m_width = 0;
	m_height = 0;
}

// FUNCTION: GOLDP 0x10029ee0
void GolBillboard::ComputeVisibility(const GolViewFrustum& p_view, ResultStruct* p_result)
{
	GolVec3 position;
	GetBoundsCenter(&position);
	p_result->m_lodIndex = 0;

	if (m_maxDistanceSquared != g_pontoonMaxFloat) {
		LegoFloat distanceSquared = position.DistanceSquaredTo(p_view.m_position);
		if (distanceSquared == 0.0f || distanceSquared > m_maxDistanceSquared) {
			p_result->m_visibility = 0;
			return;
		}
	}

	p_result->m_visibility = p_view.ClassifySphere(position, GetBoundsRadius());
}

// FUNCTION: GOLDP 0x10026fa0 FOLDED
void GolBillboard::SetBoundsRadius(LegoFloat p_scalar)
{
	m_radius = p_scalar;
	m_minX = m_center.m_x - p_scalar;
	m_maxX = p_scalar + m_center.m_x;
}

// FUNCTION: GOLDP 0x10029fa0
void GolBillboard::TestVisibility(const GolVec3& p_cameraPosition, LegoBool32* p_visibility)
{
	GolVec3 position;

	p_visibility[1] = FALSE;
	GetBoundsCenter(&position);

	LegoFloat distanceSquared = position.DistanceSquaredTo(p_cameraPosition);

	if (distanceSquared != 0.0f && distanceSquared <= m_maxDistanceSquared) {
		p_visibility[0] = TRUE;
	}
	else {
		p_visibility[0] = FALSE;
	}
}

// FUNCTION: GOLDP 0x1002a020
GolMaterial* GolBillboard::ResolveMaterial()
{
	if (m_flags & c_flagMaterialAssignment) {
		m_material = static_cast<GolMaterial*>(m_materialTable->GetEntry(m_materialIndex));
	}

	return m_material;
}

// FUNCTION: GOLDP 0x1002a040
void GolBillboard::Draw(GolRenderDevice& p_renderer)
{
	p_renderer.DrawBillboard(*this);
}

// FUNCTION: GOLDP 0x1002a060
LegoBool32 GolBillboard::GetKind()
{
	if (m_flags & c_flagMaterialAssignment) {
		m_material = static_cast<GolMaterial*>(m_materialTable->GetEntry(m_materialIndex));
	}

	return m_material->GetFlags() & 0x1100;
}
