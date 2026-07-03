#include "util/carshadowrenderstate.h"

#include "device/golpalettebase.h"
#include "golmodelentity.h"
#include "goltexture.h"
#include "render/gold3drenderdevice.h"

#include <string.h>

DECOMP_SIZE_ASSERT(CarShadowRenderState::TransformedVertex, 0x0c)
DECOMP_SIZE_ASSERT(CarShadowRenderState, 0x33c)

// GLOBAL: LEGORACERS 0x004af55c
LegoU32 g_nextVertexIndex[3] = {1, 2, 0};

// GLOBAL: LEGORACERS 0x004af568
LegoU32 g_previousVertexIndex[3] = {2, 0, 1};

// GLOBAL: LEGORACERS 0x004be22c
LegoU32 g_silhouetteClearMask = 1;

// GLOBAL: LEGORACERS 0x004be230
LegoU32 g_silhouetteFlattenMask = 2;

// GLOBAL: LEGORACERS 0x004be234
const GolMatrix3 g_identityMatrix = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};

// GLOBAL: LEGORACERS 0x004bef68
LegoU32 g_silhouetteClearFlag = 1;

// GLOBAL: LEGORACERS 0x004bef6c
LegoU32 g_silhouetteFlattenFlag = 2;

// GLOBAL: LEGORACERS 0x004c67f8
CarShadowRenderState g_carShadowRenderState;

// FUNCTION: LEGORACERS 0x00416030 FOLDED
void CarShadowRenderState::Begin(GolD3DRenderDevice*, GolModelEntity*, LegoU32)
{
	// empty
}

// FUNCTION: LEGORACERS 0x00416030 FOLDED
void CarShadowRenderState::End(GolD3DRenderDevice*, GolModelEntity*, LegoU32)
{
	// empty
}

// FUNCTION: LEGORACERS 0x004113b0 FOLDED
undefined4 CarShadowRenderState::ProcessVerticesPrelit(DrawCommand*)
{
	return 0;
}

// FUNCTION: LEGORACERS 0x00409740
CarShadowRenderState::CarShadowRenderState()
{
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_renderer = NULL;
	m_texture = NULL;
	m_fillValue = 0;
	m_silhouetteValue = 0;
	m_drawFunction = &CarShadowRenderState::DrawTriangles8Bpp;
	m_flags = 0;
	m_offsetX = 0.0f;
	m_offsetY = 0.0f;
	m_pixels = NULL;
	m_pitch = 0;
	m_textureWidth = 0.0f;
	m_textureHeight = 0.0f;
	::memset(m_transformed, 0, sizeof(m_transformed));
}

// FUNCTION: LEGORACERS 0x004097b0
CarShadowRenderState::~CarShadowRenderState()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004097c0
void CarShadowRenderState::Initialize(GolD3DRenderDevice* p_renderer, GolTexture* p_texture)
{
	m_renderer = p_renderer;
	m_texture = p_texture;

	switch (p_texture->GetTextureFormat().m_bitsPerPixel) {
	case 4:
		m_drawFunction = &CarShadowRenderState::DrawTriangles4Bpp;
		break;
	case 8:
		m_drawFunction = &CarShadowRenderState::DrawTriangles8Bpp;
		break;
	case 16:
		m_drawFunction = &CarShadowRenderState::DrawTriangles16Bpp;
		break;
	}

	m_textureWidth = static_cast<LegoFloat>(p_texture->GetWidth());
	m_textureHeight = static_cast<LegoFloat>(p_texture->GetHeight());
}

// FUNCTION: LEGORACERS 0x00409830
void CarShadowRenderState::Reset()
{
	m_renderer = NULL;
	m_texture = NULL;
	m_fillValue = 0;
	m_silhouetteValue = 0;
	m_pixels = NULL;
	m_pitch = 0;
}

// FUNCTION: LEGORACERS 0x00409850
void CarShadowRenderState::SetFillColor(ColorRGBA* p_color)
{
	if (m_texture->GetTextureFormat().m_paletteMask) {
		m_fillValue = 0;
		m_texture->GetPalette()->SetEntries(p_color, 0, 1);
	}
	else {
		m_fillValue = m_texture->GetTextureFormat().MapRGBA(*p_color);
	}
}

// FUNCTION: LEGORACERS 0x004098a0
void CarShadowRenderState::SetSilhouetteColor(ColorRGBA* p_color)
{
	if (m_texture->GetTextureFormat().m_paletteMask) {
		m_silhouetteValue = 1;
		m_texture->GetPalette()->SetEntries(p_color, 1, 1);
	}
	else {
		m_silhouetteValue = m_texture->GetTextureFormat().MapRGBA(*p_color);
	}
}

// FUNCTION: LEGORACERS 0x004098f0
void CarShadowRenderState::BeginCapture(
	const LegoFloat* p_origin,
	LegoFloat p_width,
	LegoFloat p_height,
	LegoU32 p_flags
)
{
	m_flags = p_flags;
	if (g_silhouetteClearMask & p_flags) {
		m_texture->Fill(m_fillValue);
	}

	m_texture->LockPixels(&m_pixels, &m_pitch, GolSurface::c_lockRequestRead | GolSurface::c_lockRequestWrite);
	LegoFloat halfWidth = p_width;
	halfWidth *= 0.5f;
	m_offsetX = halfWidth - p_origin[0];

	LegoFloat halfHeight = p_height;
	halfHeight *= 0.5f;
	m_offsetY = -p_origin[1] - halfHeight;
	m_scaleX = m_textureWidth / p_width;
	m_scaleY = -(m_textureHeight / p_height);
}

// FUNCTION: LEGORACERS 0x00409970
void CarShadowRenderState::RenderEntity(GolModelEntity* p_model, LegoU32 p_lodIndex)
{
	GolMatrix3 orientation;

	if (g_silhouetteFlattenMask & m_flags) {
		p_model->CopyOrientation(&orientation);
		p_model->SetOrientationMatrix(g_identityMatrix);
	}

	m_renderer->DrawModelEntityWithScopedState(p_model, this, p_lodIndex);

	if (g_silhouetteFlattenMask & m_flags) {
		p_model->SetOrientationMatrix(orientation);
	}
}

// FUNCTION: LEGORACERS 0x004099d0
void CarShadowRenderState::EndCapture()
{
	m_texture->UnlockPixels();
	m_pixels = NULL;
	m_pitch = 0;
}

// FUNCTION: LEGORACERS 0x004099f0
void CarShadowRenderState::ProcessVertices(DrawCommand* p_command)
{
	LegoU32 outputFirst = p_command->m_outputFirst;
	const CommandVertex* vertices = p_command->m_vertices;
	LegoU32 vertexCount = p_command->m_vertexCount;
	const CommandVertex* vertex = vertices + outputFirst;
	const CommandVertex* end = vertex + vertexCount;
	TransformedVertex* transformed = &m_transformed[outputFirst];

	if (vertex < end) {
		do {
			transformed->m_clipped = 0;
			transformed->m_x = (m_offsetX + vertex->m_x) * m_scaleX;
			if (transformed->m_x < 0.0f || transformed->m_x > m_textureWidth) {
				transformed->m_clipped = 1;
			}

			transformed->m_y = (vertex->m_y + m_offsetY) * m_scaleY;
			if (transformed->m_y < 0.0f || transformed->m_y > m_textureHeight) {
				transformed->m_clipped = 1;
			}
			vertex++;
			transformed++;
		} while (vertex < end);
	}
}

// FUNCTION: LEGORACERS 0x00409a90
void CarShadowRenderState::ProcessMaterial(MaterialCommand* p_command)
{
	LegoU8* triangle = p_command->m_indices + p_command->m_firstTriangle * 4;
	LegoU8* end = triangle + p_command->m_triangleCount * 4;
	TransformedVertex* triangleVertices[3];

	while (triangle < end) {
		triangleVertices[0] = &m_transformed[triangle[2]];
		triangle += 4;
		triangleVertices[1] = &m_transformed[triangle[-3]];
		triangleVertices[2] = &m_transformed[triangle[-4]];

		if (!(triangleVertices[0]->m_clipped | triangleVertices[1]->m_clipped | triangleVertices[2]->m_clipped)) {
			(this->*m_drawFunction)(triangleVertices);
		}
	}
}

// STUB: LEGORACERS 0x00409b10
void CarShadowRenderState::DrawTriangles4Bpp(TransformedVertex** p_triangle)
{
	TransformedVertex** vertices = p_triangle;
	TransformedVertex* vertex0 = vertices[0];
	TransformedVertex* vertex2 = vertices[2];
	TransformedVertex* vertex1 = vertices[1];

	LegoU32 topIndex = 2;
	if (vertex0->m_y < vertex1->m_y) {
		if (vertex0->m_y < vertex2->m_y) {
			topIndex = 0;
		}
	}
	else if (vertex1->m_y < vertex2->m_y) {
		topIndex = 1;
	}

	TransformedVertex* base0 = vertices[topIndex];
	TransformedVertex* base1 = base0;
	LegoU32 edge0Index = g_previousVertexIndex[topIndex];
	LegoU32 edge1Index = g_nextVertexIndex[topIndex];
	TransformedVertex* edge0 = vertices[edge0Index];
	TransformedVertex* edge1 = vertices[edge1Index];
	LegoS32 x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
	LegoS32 x1 = x0;
	LegoBool32 advancedEdge = FALSE;

	LegoFloat deltaY0 = edge0->m_y - base0->m_y;
	if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
		base0 = edge0;
		edge0Index = g_previousVertexIndex[edge0Index];
		edge0 = vertices[edge0Index];
		deltaY0 = edge0->m_y - base0->m_y;
		if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
			return;
		}
		x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
		advancedEdge = TRUE;
	}

	LegoS32 y = (0xffff - static_cast<LegoS32>(-65536.0f * base0->m_y)) & 0xffff0000;
	LegoU8* row = m_pixels + ((y >> 16) * m_pitch);
	LegoS32 xStep0 = static_cast<LegoS32>(((edge0->m_x - base0->m_x) / deltaY0) * 65536.0f);

	LegoFloat deltaY1 = edge1->m_y - base1->m_y;
	if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
		base1 = edge1;
		edge1Index = g_nextVertexIndex[edge1Index];
		edge1 = vertices[edge1Index];
		deltaY1 = edge1->m_y - base1->m_y;
		if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
			return;
		}
		x1 = static_cast<LegoS32>(65536.0f * base1->m_x);
		advancedEdge = TRUE;
	}

	LegoS32 xStep1 = static_cast<LegoS32>(((edge1->m_x - base1->m_x) / deltaY1) * 65536.0f);
	LegoU8 color = static_cast<LegoU8>(m_silhouetteValue & 0x0f);
	LegoU8 colorHigh = static_cast<LegoU8>(color << 4);
	LegoU8 colorPacked = static_cast<LegoU8>(colorHigh | color);

	LegoBool32 edge1EndsFirst;
	LegoS32 yEnd;
	if (edge0->m_y <= edge1->m_y) {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge0->m_y)) & 0xffff0000;
		edge1EndsFirst = FALSE;
	}
	else {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge1->m_y)) & 0xffff0000;
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
				edge1Index = g_nextVertexIndex[edge1Index];
				edge1 = vertices[edge1Index];
				deltaY1 = edge1->m_y - base1->m_y;
				if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
					return;
				}
				x1 = static_cast<LegoS32>(65536.0f * base1->m_x);
				xStep1 = static_cast<LegoS32>(((edge1->m_x - base1->m_x) / deltaY1) * 65536.0f);
				yEndValue = edge1->m_y;
			}
			else {
				base0 = edge0;
				edge0Index = g_previousVertexIndex[edge0Index];
				edge0 = vertices[edge0Index];
				deltaY0 = edge0->m_y - base0->m_y;
				if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
					return;
				}
				x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
				xStep0 = static_cast<LegoS32>(((edge0->m_x - base0->m_x) / deltaY0) * 65536.0f);
				yEndValue = edge0->m_y;
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
		row += m_pitch;
		x0 += xStep0;
		x1 += xStep1;
	}
}

// STUB: LEGORACERS 0x00409f90
void CarShadowRenderState::DrawTriangles8Bpp(TransformedVertex** p_triangle)
{
	TransformedVertex** vertices = p_triangle;
	TransformedVertex* vertex0 = vertices[0];
	TransformedVertex* vertex2 = vertices[2];
	TransformedVertex* vertex1 = vertices[1];

	LegoFloat area = ((vertex0->m_y - vertex2->m_y) * (vertex1->m_x - vertex2->m_x)) -
					 ((vertex0->m_x - vertex2->m_x) * (vertex1->m_y - vertex2->m_y));
	if (area >= 0.0f) {
		return;
	}

	LegoU32 topIndex = 2;
	if (vertex0->m_y < vertex1->m_y) {
		if (vertex0->m_y < vertex2->m_y) {
			topIndex = 0;
		}
	}
	else if (vertex1->m_y < vertex2->m_y) {
		topIndex = 1;
	}

	TransformedVertex* base0 = vertices[topIndex];
	TransformedVertex* base1 = base0;
	LegoU32 edge0Index = g_previousVertexIndex[topIndex];
	LegoU32 edge1Index = g_nextVertexIndex[topIndex];
	TransformedVertex* edge0 = vertices[edge0Index];
	TransformedVertex* edge1 = vertices[edge1Index];
	LegoS32 x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
	LegoS32 x1 = x0;
	LegoBool32 advancedEdge = FALSE;

	LegoFloat deltaY0 = edge0->m_y - base0->m_y;
	if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
		base0 = edge0;
		edge0Index = g_previousVertexIndex[edge0Index];
		edge0 = vertices[edge0Index];
		deltaY0 = edge0->m_y - base0->m_y;
		if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
			return;
		}
		x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
		advancedEdge = TRUE;
	}

	LegoS32 y = (0xffff - static_cast<LegoS32>(-65536.0f * base0->m_y)) & 0xffff0000;
	LegoU8* row = m_pixels + ((y >> 16) * m_pitch);
	LegoS32 xStep0 = static_cast<LegoS32>(((edge0->m_x - base0->m_x) / deltaY0) * 65536.0f);

	LegoFloat deltaY1 = edge1->m_y - base1->m_y;
	if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
		base1 = edge1;
		edge1Index = g_nextVertexIndex[edge1Index];
		edge1 = vertices[edge1Index];
		deltaY1 = edge1->m_y - base1->m_y;
		if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
			return;
		}
		x1 = static_cast<LegoS32>(65536.0f * base1->m_x);
		advancedEdge = TRUE;
	}

	LegoS32 xStep1 = static_cast<LegoS32>(((edge1->m_x - base1->m_x) / deltaY1) * 65536.0f);
	LegoU8 color = static_cast<LegoU8>(m_silhouetteValue);

	LegoBool32 edge1EndsFirst;
	LegoS32 yEnd;
	if (edge0->m_y <= edge1->m_y) {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge0->m_y)) & 0xffff0000;
		edge1EndsFirst = FALSE;
	}
	else {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge1->m_y)) & 0xffff0000;
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
				edge1Index = g_nextVertexIndex[edge1Index];
				edge1 = vertices[edge1Index];
				deltaY1 = edge1->m_y - base1->m_y;
				if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
					return;
				}
				x1 = static_cast<LegoS32>(65536.0f * base1->m_x);
				xStep1 = static_cast<LegoS32>(((edge1->m_x - base1->m_x) / deltaY1) * 65536.0f);
				yEndValue = edge1->m_y;
			}
			else {
				base0 = edge0;
				edge0Index = g_previousVertexIndex[edge0Index];
				edge0 = vertices[edge0Index];
				deltaY0 = edge0->m_y - base0->m_y;
				if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
					return;
				}
				x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
				xStep0 = static_cast<LegoS32>(((edge0->m_x - base0->m_x) / deltaY0) * 65536.0f);
				yEndValue = edge0->m_y;
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
		row += m_pitch;
		x0 += xStep0;
		x1 += xStep1;
	}
}

// STUB: LEGORACERS 0x0040a3e0
void CarShadowRenderState::DrawTriangles16Bpp(TransformedVertex** p_triangle)
{
	TransformedVertex** vertices = p_triangle;
	TransformedVertex* vertex0 = vertices[0];
	TransformedVertex* vertex2 = vertices[2];
	TransformedVertex* vertex1 = vertices[1];

	LegoFloat area = ((vertex0->m_y - vertex2->m_y) * (vertex1->m_x - vertex2->m_x)) -
					 ((vertex0->m_x - vertex2->m_x) * (vertex1->m_y - vertex2->m_y));
	if (area >= 0.0f) {
		return;
	}

	LegoU32 topIndex = 2;
	if (vertex0->m_y < vertex1->m_y) {
		if (vertex0->m_y < vertex2->m_y) {
			topIndex = 0;
		}
	}
	else if (vertex1->m_y < vertex2->m_y) {
		topIndex = 1;
	}

	TransformedVertex* base0 = vertices[topIndex];
	TransformedVertex* base1 = base0;
	LegoU32 edge0Index = g_previousVertexIndex[topIndex];
	LegoU32 edge1Index = g_nextVertexIndex[topIndex];
	TransformedVertex* edge0 = vertices[edge0Index];
	TransformedVertex* edge1 = vertices[edge1Index];
	LegoS32 x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
	LegoS32 x1 = x0;
	LegoBool32 advancedEdge = FALSE;

	LegoFloat deltaY0 = edge0->m_y - base0->m_y;
	if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
		base0 = edge0;
		edge0Index = g_previousVertexIndex[edge0Index];
		edge0 = vertices[edge0Index];
		deltaY0 = edge0->m_y - base0->m_y;
		if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
			return;
		}
		x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
		advancedEdge = TRUE;
	}

	LegoS32 y = (0xffff - static_cast<LegoS32>(-65536.0f * base0->m_y)) & 0xffff0000;
	LegoU8* row = m_pixels + ((y >> 16) * m_pitch);
	LegoS32 xStep0 = static_cast<LegoS32>(((edge0->m_x - base0->m_x) / deltaY0) * 65536.0f);

	LegoFloat deltaY1 = edge1->m_y - base1->m_y;
	if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
		base1 = edge1;
		edge1Index = g_nextVertexIndex[edge1Index];
		edge1 = vertices[edge1Index];
		deltaY1 = edge1->m_y - base1->m_y;
		if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
			return;
		}
		x1 = static_cast<LegoS32>(65536.0f * base1->m_x);
		advancedEdge = TRUE;
	}

	LegoS32 xStep1 = static_cast<LegoS32>(((edge1->m_x - base1->m_x) / deltaY1) * 65536.0f);
	LegoU16 color = static_cast<LegoU16>(m_silhouetteValue);

	LegoBool32 edge1EndsFirst;
	LegoS32 yEnd;
	if (edge0->m_y <= edge1->m_y) {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge0->m_y)) & 0xffff0000;
		edge1EndsFirst = FALSE;
	}
	else {
		yEnd = (0xffff - static_cast<LegoS32>(-65536.0f * edge1->m_y)) & 0xffff0000;
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
				edge1Index = g_nextVertexIndex[edge1Index];
				edge1 = vertices[edge1Index];
				deltaY1 = edge1->m_y - base1->m_y;
				if (deltaY1 < 0.001f && deltaY1 > -0.001f) {
					return;
				}
				x1 = static_cast<LegoS32>(65536.0f * base1->m_x);
				xStep1 = static_cast<LegoS32>(((edge1->m_x - base1->m_x) / deltaY1) * 65536.0f);
				yEndValue = edge1->m_y;
			}
			else {
				base0 = edge0;
				edge0Index = g_previousVertexIndex[edge0Index];
				edge0 = vertices[edge0Index];
				deltaY0 = edge0->m_y - base0->m_y;
				if (deltaY0 < 0.001f && deltaY0 > -0.001f) {
					return;
				}
				x0 = static_cast<LegoS32>(65536.0f * base0->m_x);
				xStep0 = static_cast<LegoS32>(((edge0->m_x - base0->m_x) / deltaY0) * 65536.0f);
				yEndValue = edge0->m_y;
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
		row += m_pitch;
		x0 += xStep0;
		x1 += xStep1;
	}
}
