#include "util/decalgeometry.h"

#include "core/gol.h"
#include "decomp.h"
#include "golmodelbase.h"
#include "render/golrenderdevice.h"

#include <float.h>

DECOMP_SIZE_ASSERT(DecalGeometry, 0x114)

// GLOBAL: LEGORACERS 0x004af90c
const LegoFloat g_decalGeometryMaxFloat = FLT_MAX;

// GLOBAL: LEGORACERS 0x004af910
const LegoFloat g_decalGeometryDefaultDepth = 20.0f;

// GLOBAL: LEGORACERS 0x004af914
const LegoFloat g_decalGeometryDefaultLift = 0.4f;

extern LegoFloat g_decalWAxisX;
extern LegoFloat g_decalWAxisY;
extern LegoFloat g_decalWAxisZ;
extern LegoFloat g_decalWOffset;

// FUNCTION: LEGORACERS 0x00414850
DecalGeometry::DecalGeometry()
{
	m_golExport = NULL;
	m_model = NULL;
	m_vertices = NULL;
	m_indexBytes = NULL;
	m_vertexCapacity = 0;
	m_triangleCapacity = 0;
	m_vertexCount = 0;
	m_triangleCount = 0;
	m_batchVertexCount = 0;
	m_batchTriangleCount = 0;
	m_groupIndex = 0;
	m_batchFirstVertex = 0;
	m_batchFirstTriangle = 0;
	m_depth = g_decalGeometryDefaultDepth;
	m_widthAxis.m_x = 1.0f;
	m_widthAxis.m_y = 0.0f;
	m_widthAxis.m_z = 0.0f;
	m_lengthAxis.m_x = 0.0f;
	m_lengthAxis.m_y = 1.0f;
	m_lengthAxis.m_z = 0.0f;
	m_normal.m_x = 0.0f;
	m_normal.m_y = 0.0f;
	m_normal.m_z = 1.0f;
	m_center.m_x = 0.0f;
	m_center.m_y = 0.0f;
	m_center.m_z = 0.0f;
	m_width = 1.0f;
	m_length = 1.0f;
	m_color.m_red = 0xff;
	m_color.m_grn = 0xff;
	m_color.m_blu = 0xff;
	m_color.m_alp = 0xff;
	g_decalWAxisX = 0.0f;
	g_decalWAxisY = 0.0f;
	g_decalWAxisZ = 0.0f;
	g_decalWOffset = 1.0f;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00414940
DecalGeometry::~DecalGeometry()
{
	Destroy();
}

// FUNCTION: LEGORACERS 0x00414950
void DecalGeometry::Initialize(GolExport* p_golExport, GolRenderDevice* p_renderer, LegoU32 p_count)
{
	if (m_flags & c_initialized) {
		Destroy();
	}

	m_golExport = p_golExport;
	m_model = p_golExport->VTable0x14();
	m_triangleCapacity = p_count;
	m_vertexCapacity = p_count * 3;
	m_model->VTable0x18(p_renderer, 1, m_vertexCapacity, p_count, p_count * 2 + 2, 1);
	m_entity.SetPrimaryModel(m_model, g_decalGeometryMaxFloat);
	m_position.m_x = 0.0f;
	m_position.m_y = 0.0f;
	m_position.m_z = g_decalGeometryDefaultLift;
	m_entity.SetPosition(m_position);
	m_flags = c_initialized;
}

// FUNCTION: LEGORACERS 0x004149f0
void DecalGeometry::Destroy()
{
	m_entity.ResetModelState();

	if (m_golExport != NULL) {
		if (m_model != 0) {
			m_golExport->VTable0x48(m_model);
		}
		m_golExport = NULL;
	}

	m_model = 0;
	m_vertices = 0;
	m_indexBytes = 0;
	m_flags = 0;
}

// FUNCTION: LEGORACERS 0x00415a40
void DecalGeometry::Draw(GolRenderDevice* p_renderer)
{
	if (m_flags & c_hasGeometry) {
		p_renderer->VTable0x94(&m_entity);
	}
}

// FUNCTION: LEGORACERS 0x00415bf0
LegoU8 DecalGeometry::SetColor(const ColorRGBA* p_color)
{
	m_color.m_red = p_color->m_red;
	m_color.m_grn = p_color->m_grn;
	m_color.m_blu = p_color->m_blu;
	LegoU8 result = p_color->m_alp;
	m_color.m_alp = result;

	return result;
}
