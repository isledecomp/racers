#include "scene/golbillboardex.h"

#include "duskwindbananarelic0x24.h"
#include "render/gold3drenderdevice.h"

// GLOBAL: GOLDP 0x10063570
GolVec3 GolBillboard::g_billboardPositions[4];

// GLOBAL: GOLDP 0x100635a0
GolVec2 GolBillboard::g_billboardTexCoords[4];

// GLOBAL: GOLDP 0x1005ca4c
LegoU32 GolBillboard::g_billboardColors[4] = {0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff};

// GLOBAL: GOLDP 0x1005ca5c
LegoU8 GolBillboard::g_billboardTriangleIndices[8] = {1, 2, 0, 0, 3, 2, 1, 0};

// GLOBAL: GOLDP 0x1005675c
extern const LegoFloat g_unk0x1005675c = 1.0f;

#pragma data_seg(".CRT$XCU")
// GLOBAL: GOLDP 0x1005c010
GolBillboardInitializerFunction g_unk0x1005c010 = &GolBillboard::FUN_10014e20;
#pragma data_seg()

// FUNCTION: GOLDP 0x10014e20
void GolBillboard::FUN_10014e20()
{
	g_billboardTexCoords[1].m_y = g_unk0x1005675c;
	g_billboardTexCoords[2].m_x = g_unk0x1005675c;
	g_billboardTexCoords[2].m_y = 0.0f;
	g_billboardTexCoords[3].m_x = g_unk0x1005675c;
	g_billboardTexCoords[3].m_y = g_unk0x1005675c;
}

// FUNCTION: GOLDP 0x10014e50
LegoBool32 GolBillboard::FUN_10014e50(const GolVec3* p_arg1, const GolVec3* p_arg2, GolMatrix4* p_matrix)
{
	GolVec3 row0;
	GolVec3 row1;
	GolVec3 position;
	const GolVec3* row2;

	FUN_100286d0(&position);

	row0.m_x = -p_arg1->m_x;
	row0.m_y = -p_arg1->m_y;
	row0.m_z = -p_arg1->m_z;

	if (m_flags & c_flagBit1) {
		row2 = &m_unk0x30;
		LegoFloat dot = row2->m_z;
		dot *= row0.m_z;
		dot += row0.m_y * row2->m_y;
		dot += row0.m_x * row2->m_x;
		row0.m_x -= dot * row2->m_x;
		LegoFloat projection = row2->m_y;
		projection *= dot;
		row0.m_y -= projection;
		projection = row2->m_z;
		projection *= dot;
		row0.m_z -= projection;
	}
	else {
		row2 = p_arg2;
	}

	GolMath::NormalizeVector3(row0, &row0);

	row1.m_x = row0.m_z;
	row1.m_x *= row2->m_y;
	LegoFloat term = row2->m_z;
	term *= row0.m_y;
	row1.m_x -= term;
	row1.m_y = row2->m_z;
	row1.m_y *= row0.m_x;
	row1.m_y -= row0.m_z * row2->m_x;
	row1.m_z = row0.m_y;
	row1.m_z *= row2->m_x;
	term = row2->m_y;
	term *= row0.m_x;
	row1.m_z -= term;

	p_matrix->m_m[0][0] = row0.m_x;
	p_matrix->m_m[0][1] = row0.m_y;
	p_matrix->m_m[0][2] = row0.m_z;
	p_matrix->m_m[0][3] = 0.0f;

	p_matrix->m_m[1][0] = row1.m_x;
	p_matrix->m_m[1][1] = row1.m_y;
	p_matrix->m_m[1][2] = row1.m_z;
	p_matrix->m_m[1][3] = 0.0f;

	p_matrix->m_m[2][0] = row2->m_x;
	p_matrix->m_m[2][1] = row2->m_y;
	p_matrix->m_m[2][2] = row2->m_z;
	p_matrix->m_m[2][3] = 0.0f;

	LegoFloat halfWidth = m_width / 2.0f;
	LegoFloat halfHeight = m_height / 2.0f;
	p_matrix->m_m[3][0] = position.m_x - halfWidth * row1.m_x - halfHeight * row2->m_x;
	LegoFloat offset = row2->m_y;
	offset *= halfHeight;
	p_matrix->m_m[3][1] = position.m_y - halfWidth * row1.m_y - offset;
	offset = row2->m_z;
	offset *= halfHeight;
	p_matrix->m_m[3][2] = position.m_z - halfWidth * row1.m_z - offset;
	p_matrix->m_m[3][3] = 1.0f;

	return TRUE;
}

// FUNCTION: GOLDP 0x10014fd0
void GolBillboardEx::VTable0x4c(
	DuskwindBananaRelic0x24* p_position,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoFloat p_maxDistanceSquared
)
{
	GolBillboard::VTable0x4c(p_position, p_width, p_height, p_maxDistanceSquared);
}

// FUNCTION: GOLDP 0x10014ff0
void GolBillboard::FUN_10014ff0(GolD3DRenderDevice* p_renderer)
{
	DuskwindBananaRelic0x24* material = FUN_1002a020();
	(p_renderer->*p_renderer->m_unk0xc876c)(material);
	p_renderer->FUN_1000ac00(material->GetUnk0x04());

	p_renderer->m_unk0xc4c0c = g_billboardPositions;
	p_renderer->m_unk0xc4c10 = g_billboardTexCoords;
	p_renderer->m_unk0xc4c14 = g_billboardColors;
	p_renderer->m_unk0xc4c18 = g_billboardTriangleIndices;
	p_renderer->m_unk0xc854c.m_indices = g_billboardTriangleIndices;

	g_billboardPositions[0].m_z = m_height;
	g_billboardPositions[2].m_y = m_width;
	g_billboardPositions[2].m_z = m_height;
	g_billboardPositions[3].m_y = m_width;

	(p_renderer->*p_renderer->m_drawTriangleFn1)(0, 0, 4);
	(p_renderer->*p_renderer->m_drawTriangleFn2)(0, 2, 3);
}
