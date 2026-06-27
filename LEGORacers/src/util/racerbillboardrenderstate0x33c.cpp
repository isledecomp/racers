#include "util/racerbillboardrenderstate0x33c.h"

#include "device/golpalettebase.h"
#include "golddune0x38.h"
#include "golmodelentity.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(RacerBillboardRenderState0x33c::Field0x038, 0x0c)
DECOMP_SIZE_ASSERT(RacerBillboardRenderState0x33c, 0x33c)

// GLOBAL: LEGORACERS 0x004af55c
LegoU32 g_unk0x004af55c[3] = {1, 2, 0};

// GLOBAL: LEGORACERS 0x004af568
LegoU32 g_unk0x004af568[3] = {2, 0, 1};

// GLOBAL: LEGORACERS 0x004be22c
LegoU32 g_unk0x004be22c = 1;

// GLOBAL: LEGORACERS 0x004be230
LegoU32 g_unk0x004be230 = 2;

// GLOBAL: LEGORACERS 0x004be234
const GolMatrix3 g_unk0x004be234 = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};

// GLOBAL: LEGORACERS 0x004bef68
LegoU32 g_unk0x004bef68 = 1;

// GLOBAL: LEGORACERS 0x004bef6c
LegoU32 g_unk0x004bef6c = 2;

// GLOBAL: LEGORACERS 0x004c67f8
RacerBillboardRenderState0x33c g_racerBillboardRenderState0x33c;

// FUNCTION: LEGORACERS 0x00416030 FOLDED
void RacerBillboardRenderState0x33c::VTable0x00(GolD3DRenderDevice*, GolModelEntity*, LegoU32)
{
	// empty
}

// FUNCTION: LEGORACERS 0x00416030 FOLDED
void RacerBillboardRenderState0x33c::VTable0x04(GolD3DRenderDevice*, GolModelEntity*, LegoU32)
{
	// empty
}

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 RacerBillboardRenderState0x33c::VTable0x10(DrawCommand*)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x00409740
RacerBillboardRenderState0x33c::RacerBillboardRenderState0x33c()
{
	m_unk0x020 = 1.0f;
	m_unk0x024 = 1.0f;
	m_renderer = NULL;
	m_texture = NULL;
	m_unk0x00c = 0;
	m_unk0x010 = 0;
	m_drawFunction0x338 = &RacerBillboardRenderState0x33c::FUN_00409f90;
	m_flags0x014 = 0;
	m_unk0x018 = 0.0f;
	m_unk0x01c = 0.0f;
	m_unk0x030 = NULL;
	m_unk0x034 = 0;
	m_unk0x028 = 0.0f;
	m_unk0x02c = 0.0f;
	::memset(m_unk0x038, 0, sizeof(m_unk0x038));
}

// FUNCTION: LEGORACERS 0x004097b0
RacerBillboardRenderState0x33c::~RacerBillboardRenderState0x33c()
{
	FUN_00409830();
}

// FUNCTION: LEGORACERS 0x004097c0
void RacerBillboardRenderState0x33c::FUN_004097c0(GolD3DRenderDevice* p_renderer, GoldDune0x38* p_texture)
{
	m_renderer = p_renderer;
	m_texture = p_texture;

	switch (p_texture->GetTextureFormat().m_bitsPerPixel) {
	case 4:
		m_drawFunction0x338 = &RacerBillboardRenderState0x33c::FUN_00409b10;
		break;
	case 8:
		m_drawFunction0x338 = &RacerBillboardRenderState0x33c::FUN_00409f90;
		break;
	case 16:
		m_drawFunction0x338 = &RacerBillboardRenderState0x33c::FUN_0040a3e0;
		break;
	}

	m_unk0x028 = static_cast<LegoFloat>(p_texture->GetWidth());
	m_unk0x02c = static_cast<LegoFloat>(p_texture->GetHeight());
}

// FUNCTION: LEGORACERS 0x00409830
void RacerBillboardRenderState0x33c::FUN_00409830()
{
	m_renderer = NULL;
	m_texture = NULL;
	m_unk0x00c = 0;
	m_unk0x010 = 0;
	m_unk0x030 = NULL;
	m_unk0x034 = 0;
}

// FUNCTION: LEGORACERS 0x00409850
void RacerBillboardRenderState0x33c::FUN_00409850(ColorRGBA* p_color)
{
	if (m_texture->GetTextureFormat().m_paletteMask) {
		m_unk0x00c = 0;
		m_texture->GetPalette()->SetEntries(p_color, 0, 1);
	}
	else {
		m_unk0x00c = m_texture->GetTextureFormat().MapRGBA(*p_color);
	}
}

// FUNCTION: LEGORACERS 0x004098a0
void RacerBillboardRenderState0x33c::FUN_004098a0(ColorRGBA* p_color)
{
	if (m_texture->GetTextureFormat().m_paletteMask) {
		m_unk0x010 = 1;
		m_texture->GetPalette()->SetEntries(p_color, 1, 1);
	}
	else {
		m_unk0x010 = m_texture->GetTextureFormat().MapRGBA(*p_color);
	}
}

// FUNCTION: LEGORACERS 0x004098f0
void RacerBillboardRenderState0x33c::FUN_004098f0(
	const LegoFloat* p_origin,
	LegoFloat p_unk0x08,
	LegoFloat p_unk0x0c,
	LegoU32 p_flags
)
{
	m_flags0x014 = p_flags;
	if (g_unk0x004be22c & p_flags) {
		m_texture->Fill(m_unk0x00c);
	}

	m_texture
		->LockPixels(&m_unk0x030, &m_unk0x034, SilverDune0x30::c_lockRequestRead | SilverDune0x30::c_lockRequestWrite);
	LegoFloat halfUnk0x08 = p_unk0x08;
	halfUnk0x08 *= 0.5f;
	m_unk0x018 = halfUnk0x08 - p_origin[0];

	LegoFloat halfUnk0x0c = p_unk0x0c;
	halfUnk0x0c *= 0.5f;
	m_unk0x01c = -p_origin[1] - halfUnk0x0c;
	m_unk0x020 = m_unk0x028 / p_unk0x08;
	m_unk0x024 = -(m_unk0x02c / p_unk0x0c);
}

// FUNCTION: LEGORACERS 0x00409970
void RacerBillboardRenderState0x33c::FUN_00409970(GolModelEntity* p_model, LegoU32 p_lodIndex)
{
	GolMatrix3 orientation;

	if (g_unk0x004be230 & m_flags0x014) {
		p_model->VTable0x44(&orientation);
		p_model->VTable0x3c(g_unk0x004be234);
	}

	m_renderer->VTable0x9c(p_model, this, p_lodIndex);

	if (g_unk0x004be230 & m_flags0x014) {
		p_model->VTable0x3c(orientation);
	}
}

// FUNCTION: LEGORACERS 0x004099d0
void RacerBillboardRenderState0x33c::FUN_004099d0()
{
	m_texture->UnlockPixels();
	m_unk0x030 = NULL;
	m_unk0x034 = 0;
}

// FUNCTION: LEGORACERS 0x004099f0
void RacerBillboardRenderState0x33c::VTable0x08(DrawCommand* p_command)
{
	LegoU32 outputFirst = p_command->m_outputFirst;
	const CommandVertex* vertices = p_command->m_vertices;
	LegoU32 vertexCount = p_command->m_vertexCount;
	const CommandVertex* vertex = vertices + outputFirst;
	const CommandVertex* end = vertex + vertexCount;
	Field0x038* transformed = &m_unk0x038[outputFirst];

	if (vertex < end) {
		do {
			transformed->m_unk0x08 = 0;
			transformed->m_unk0x00 = (m_unk0x018 + vertex->m_x) * m_unk0x020;
			if (transformed->m_unk0x00 < 0.0f || transformed->m_unk0x00 > m_unk0x028) {
				transformed->m_unk0x08 = 1;
			}

			transformed->m_unk0x04 = (vertex->m_y + m_unk0x01c) * m_unk0x024;
			if (transformed->m_unk0x04 < 0.0f || transformed->m_unk0x04 > m_unk0x02c) {
				transformed->m_unk0x08 = 1;
			}
			vertex++;
			transformed++;
		} while (vertex < end);
	}
}

// FUNCTION: LEGORACERS 0x00409a90
void RacerBillboardRenderState0x33c::VTable0x0c(MaterialCommand* p_command)
{
	LegoU8* triangle = p_command->m_indices + p_command->m_firstTriangle * 4;
	LegoU8* end = triangle + p_command->m_triangleCount * 4;
	Field0x038* triangleVertices[3];

	while (triangle < end) {
		triangleVertices[0] = &m_unk0x038[triangle[2]];
		triangle += 4;
		triangleVertices[1] = &m_unk0x038[triangle[-3]];
		triangleVertices[2] = &m_unk0x038[triangle[-4]];

		if (!(triangleVertices[0]->m_unk0x08 | triangleVertices[1]->m_unk0x08 | triangleVertices[2]->m_unk0x08)) {
			(this->*m_drawFunction0x338)(triangleVertices);
		}
	}
}

// STUB: LEGORACERS 0x00409b10
void RacerBillboardRenderState0x33c::FUN_00409b10(Field0x038** p_triangle)
{
	Field0x038** vertices = p_triangle;
	Field0x038* vertex0 = vertices[0];
	Field0x038* vertex2 = vertices[2];
	Field0x038* vertex1 = vertices[1];

	LegoU32 topIndex = 2;
	if (vertex0->m_unk0x04 < vertex1->m_unk0x04) {
		if (vertex0->m_unk0x04 < vertex2->m_unk0x04) {
			topIndex = 0;
		}
	}
	else if (vertex1->m_unk0x04 < vertex2->m_unk0x04) {
		topIndex = 1;
	}

	Field0x038* base0 = vertices[topIndex];
	Field0x038* base1 = base0;
	LegoU32 edge0Index = g_unk0x004af568[topIndex];
	LegoU32 edge1Index = g_unk0x004af55c[topIndex];
	Field0x038* edge0 = vertices[edge0Index];
	Field0x038* edge1 = vertices[edge1Index];
	LegoS32 x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
	LegoS32 x1 = x0;
	LegoBool32 advancedEdge = FALSE;

	LegoFloat deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
	if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
		base0 = edge0;
		edge0Index = g_unk0x004af568[edge0Index];
		edge0 = vertices[edge0Index];
		deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
		if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
			return;
		}
		x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
		advancedEdge = TRUE;
	}

	LegoS32 y = (0xffff - static_cast<LegoS32>(-65536.0f * base0->m_unk0x04)) & 0xffff0000;
	LegoU8* row = m_unk0x030 + ((y >> 16) * m_unk0x034);
	LegoS32 xStep0 = static_cast<LegoS32>(((edge0->m_unk0x00 - base0->m_unk0x00) / deltaY0) * 65536.0f);

	LegoFloat deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
	if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
		base1 = edge1;
		edge1Index = g_unk0x004af55c[edge1Index];
		edge1 = vertices[edge1Index];
		deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
		if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
			return;
		}
		x1 = static_cast<LegoS32>(65536.0f * base1->m_unk0x00);
		advancedEdge = TRUE;
	}

	LegoS32 xStep1 = static_cast<LegoS32>(((edge1->m_unk0x00 - base1->m_unk0x00) / deltaY1) * 65536.0f);
	LegoU8 color = static_cast<LegoU8>(m_unk0x010 & 0x0f);
	LegoU8 colorHigh = static_cast<LegoU8>(color << 4);
	LegoU8 colorPacked = static_cast<LegoU8>(colorHigh | color);

	LegoBool32 edge1EndsFirst;
	LegoS32 yEnd;
	if (edge0->m_unk0x04 <= edge1->m_unk0x04) {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge0->m_unk0x04)) & 0xffff0000;
		edge1EndsFirst = FALSE;
	}
	else {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge1->m_unk0x04)) & 0xffff0000;
		edge1EndsFirst = TRUE;
	}

	for (;;) {
		if (y >= yEnd) {
			if (advancedEdge) {
				return;
			}

			LegoFloat yEndValue;
			if (edge1EndsFirst) {
				base1 = edge1;
				edge1Index = g_unk0x004af55c[edge1Index];
				edge1 = vertices[edge1Index];
				deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
				if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
					return;
				}
				x1 = static_cast<LegoS32>(65536.0f * base1->m_unk0x00);
				xStep1 = static_cast<LegoS32>(((edge1->m_unk0x00 - base1->m_unk0x00) / deltaY1) * 65536.0f);
				yEndValue = edge1->m_unk0x04;
			}
			else {
				base0 = edge0;
				edge0Index = g_unk0x004af568[edge0Index];
				edge0 = vertices[edge0Index];
				deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
				if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
					return;
				}
				x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
				xStep0 = static_cast<LegoS32>(((edge0->m_unk0x00 - base0->m_unk0x00) / deltaY0) * 65536.0f);
				yEndValue = edge0->m_unk0x04;
			}

			yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * yEndValue)) & 0xffff0000;
			if (y >= yEnd) {
				return;
			}
			advancedEdge = TRUE;
		}

		LegoS32 endX = (x1 + 0xffff) >> 16;
		LegoS32 startX = (x0 + 0xffff) >> 16;
		if (startX < endX) {
			LegoS32 width = endX - startX;
			LegoU8* dst = row + (startX >> 1);

			if (startX & 1) {
				*dst = static_cast<LegoU8>(*dst | colorHigh);
				width--;
				dst++;
			}

			LegoS32 byteCount = width >> 1;
			if (byteCount > 0) {
				::memset(dst, colorPacked, byteCount);
				dst += byteCount;
			}

			if (width & 1) {
				*dst = static_cast<LegoU8>(*dst | color);
			}
		}

		y += 0x10000;
		row += m_unk0x034;
		x0 += xStep0;
		x1 += xStep1;
	}
}

// STUB: LEGORACERS 0x00409f90
void RacerBillboardRenderState0x33c::FUN_00409f90(Field0x038** p_triangle)
{
	Field0x038** vertices = p_triangle;
	Field0x038* vertex0 = vertices[0];
	Field0x038* vertex2 = vertices[2];
	Field0x038* vertex1 = vertices[1];

	LegoFloat area = ((vertex0->m_unk0x04 - vertex2->m_unk0x04) * (vertex1->m_unk0x00 - vertex2->m_unk0x00)) -
					 ((vertex0->m_unk0x00 - vertex2->m_unk0x00) * (vertex1->m_unk0x04 - vertex2->m_unk0x04));
	if (area >= 0.0f) {
		return;
	}

	LegoU32 topIndex = 2;
	if (vertex0->m_unk0x04 < vertex1->m_unk0x04) {
		if (vertex0->m_unk0x04 < vertex2->m_unk0x04) {
			topIndex = 0;
		}
	}
	else if (vertex1->m_unk0x04 < vertex2->m_unk0x04) {
		topIndex = 1;
	}

	Field0x038* base0 = vertices[topIndex];
	Field0x038* base1 = base0;
	LegoU32 edge0Index = g_unk0x004af568[topIndex];
	LegoU32 edge1Index = g_unk0x004af55c[topIndex];
	Field0x038* edge0 = vertices[edge0Index];
	Field0x038* edge1 = vertices[edge1Index];
	LegoS32 x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
	LegoS32 x1 = x0;
	LegoBool32 advancedEdge = FALSE;

	LegoFloat deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
	if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
		base0 = edge0;
		edge0Index = g_unk0x004af568[edge0Index];
		edge0 = vertices[edge0Index];
		deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
		if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
			return;
		}
		x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
		advancedEdge = TRUE;
	}

	LegoS32 y = (0xffff - static_cast<LegoS32>(-65536.0f * base0->m_unk0x04)) & 0xffff0000;
	LegoU8* row = m_unk0x030 + ((y >> 16) * m_unk0x034);
	LegoS32 xStep0 = static_cast<LegoS32>(((edge0->m_unk0x00 - base0->m_unk0x00) / deltaY0) * 65536.0f);

	LegoFloat deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
	if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
		base1 = edge1;
		edge1Index = g_unk0x004af55c[edge1Index];
		edge1 = vertices[edge1Index];
		deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
		if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
			return;
		}
		x1 = static_cast<LegoS32>(65536.0f * base1->m_unk0x00);
		advancedEdge = TRUE;
	}

	LegoS32 xStep1 = static_cast<LegoS32>(((edge1->m_unk0x00 - base1->m_unk0x00) / deltaY1) * 65536.0f);
	LegoU8 color = static_cast<LegoU8>(m_unk0x010);

	LegoBool32 edge1EndsFirst;
	LegoS32 yEnd;
	if (edge0->m_unk0x04 <= edge1->m_unk0x04) {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge0->m_unk0x04)) & 0xffff0000;
		edge1EndsFirst = FALSE;
	}
	else {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge1->m_unk0x04)) & 0xffff0000;
		edge1EndsFirst = TRUE;
	}

	for (;;) {
		if (y >= yEnd) {
			if (advancedEdge) {
				return;
			}

			LegoFloat yEndValue;
			if (edge1EndsFirst) {
				base1 = edge1;
				edge1Index = g_unk0x004af55c[edge1Index];
				edge1 = vertices[edge1Index];
				deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
				if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
					return;
				}
				x1 = static_cast<LegoS32>(65536.0f * base1->m_unk0x00);
				xStep1 = static_cast<LegoS32>(((edge1->m_unk0x00 - base1->m_unk0x00) / deltaY1) * 65536.0f);
				yEndValue = edge1->m_unk0x04;
			}
			else {
				base0 = edge0;
				edge0Index = g_unk0x004af568[edge0Index];
				edge0 = vertices[edge0Index];
				deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
				if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
					return;
				}
				x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
				xStep0 = static_cast<LegoS32>(((edge0->m_unk0x00 - base0->m_unk0x00) / deltaY0) * 65536.0f);
				yEndValue = edge0->m_unk0x04;
			}

			yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * yEndValue)) & 0xffff0000;
			if (y >= yEnd) {
				return;
			}
			advancedEdge = TRUE;
		}

		LegoS32 endX = (x1 + 0xffff) >> 16;
		LegoS32 startX = (x0 + 0xffff) >> 16;
		if (startX < endX) {
			::memset(row + startX, color, endX - startX);
		}

		y += 0x10000;
		row += m_unk0x034;
		x0 += xStep0;
		x1 += xStep1;
	}
}

// STUB: LEGORACERS 0x0040a3e0
void RacerBillboardRenderState0x33c::FUN_0040a3e0(Field0x038** p_triangle)
{
	Field0x038** vertices = p_triangle;
	Field0x038* vertex0 = vertices[0];
	Field0x038* vertex2 = vertices[2];
	Field0x038* vertex1 = vertices[1];

	LegoFloat area = ((vertex0->m_unk0x04 - vertex2->m_unk0x04) * (vertex1->m_unk0x00 - vertex2->m_unk0x00)) -
					 ((vertex0->m_unk0x00 - vertex2->m_unk0x00) * (vertex1->m_unk0x04 - vertex2->m_unk0x04));
	if (area >= 0.0f) {
		return;
	}

	LegoU32 topIndex = 2;
	if (vertex0->m_unk0x04 < vertex1->m_unk0x04) {
		if (vertex0->m_unk0x04 < vertex2->m_unk0x04) {
			topIndex = 0;
		}
	}
	else if (vertex1->m_unk0x04 < vertex2->m_unk0x04) {
		topIndex = 1;
	}

	Field0x038* base0 = vertices[topIndex];
	Field0x038* base1 = base0;
	LegoU32 edge0Index = g_unk0x004af568[topIndex];
	LegoU32 edge1Index = g_unk0x004af55c[topIndex];
	Field0x038* edge0 = vertices[edge0Index];
	Field0x038* edge1 = vertices[edge1Index];
	LegoS32 x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
	LegoS32 x1 = x0;
	LegoBool32 advancedEdge = FALSE;

	LegoFloat deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
	if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
		base0 = edge0;
		edge0Index = g_unk0x004af568[edge0Index];
		edge0 = vertices[edge0Index];
		deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
		if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
			return;
		}
		x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
		advancedEdge = TRUE;
	}

	LegoS32 y = (0xffff - static_cast<LegoS32>(-65536.0f * base0->m_unk0x04)) & 0xffff0000;
	LegoU8* row = m_unk0x030 + ((y >> 16) * m_unk0x034);
	LegoS32 xStep0 = static_cast<LegoS32>(((edge0->m_unk0x00 - base0->m_unk0x00) / deltaY0) * 65536.0f);

	LegoFloat deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
	if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
		base1 = edge1;
		edge1Index = g_unk0x004af55c[edge1Index];
		edge1 = vertices[edge1Index];
		deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
		if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
			return;
		}
		x1 = static_cast<LegoS32>(65536.0f * base1->m_unk0x00);
		advancedEdge = TRUE;
	}

	LegoS32 xStep1 = static_cast<LegoS32>(((edge1->m_unk0x00 - base1->m_unk0x00) / deltaY1) * 65536.0f);
	LegoU16 color = static_cast<LegoU16>(m_unk0x010);

	LegoBool32 edge1EndsFirst;
	LegoS32 yEnd;
	if (edge0->m_unk0x04 <= edge1->m_unk0x04) {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge0->m_unk0x04)) & 0xffff0000;
		edge1EndsFirst = FALSE;
	}
	else {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge1->m_unk0x04)) & 0xffff0000;
		edge1EndsFirst = TRUE;
	}

	for (;;) {
		if (y >= yEnd) {
			if (advancedEdge) {
				return;
			}

			LegoFloat yEndValue;
			if (edge1EndsFirst) {
				base1 = edge1;
				edge1Index = g_unk0x004af55c[edge1Index];
				edge1 = vertices[edge1Index];
				deltaY1 = edge1->m_unk0x04 - base1->m_unk0x04;
				if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
					return;
				}
				x1 = static_cast<LegoS32>(65536.0f * base1->m_unk0x00);
				xStep1 = static_cast<LegoS32>(((edge1->m_unk0x00 - base1->m_unk0x00) / deltaY1) * 65536.0f);
				yEndValue = edge1->m_unk0x04;
			}
			else {
				base0 = edge0;
				edge0Index = g_unk0x004af568[edge0Index];
				edge0 = vertices[edge0Index];
				deltaY0 = edge0->m_unk0x04 - base0->m_unk0x04;
				if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
					return;
				}
				x0 = static_cast<LegoS32>(65536.0f * base0->m_unk0x00);
				xStep0 = static_cast<LegoS32>(((edge0->m_unk0x00 - base0->m_unk0x00) / deltaY0) * 65536.0f);
				yEndValue = edge0->m_unk0x04;
			}

			yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * yEndValue)) & 0xffff0000;
			if (y >= yEnd) {
				return;
			}
			advancedEdge = TRUE;
		}

		LegoS32 endX = (x1 + 0xffff) >> 16;
		LegoS32 startX = (x0 + 0xffff) >> 16;
		if (startX < endX) {
			LegoU16* dst = ((LegoU16*) row) + startX;
			LegoU16* end = ((LegoU16*) row) + endX;
			while (dst < end) {
				*dst = color;
				dst++;
			}
		}

		y += 0x10000;
		row += m_unk0x034;
		x0 += xStep0;
		x1 += xStep1;
	}
}
