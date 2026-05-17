#include "golfont0xa0.h"

#include "bronzefalcon0xc8770.h"
#include "decomp.h"
#include "duskwindbananarelic0x30.h"
#include "purpledune0x7c.h"
#include "rectangle.h"

DECOMP_SIZE_ASSERT(GolFont0xa0, 0xa0)

// FUNCTION: GOLDP 0x100043d0
GolFont0xa0::GolFont0xa0()
{
	m_unk0x90 = NULL;
	m_unk0x9c = NULL;
	m_renderer = NULL;
}

// FUNCTION: GOLDP 0x10004480
GolFont0xa0::~GolFont0xa0()
{
	Clear();
}

// FUNCTION: GOLDP 0x10004520
void GolFont0xa0::Clear()
{
	m_unk0x40.VTable0x38();
	ReleaseSurfaces();
	GolFontBase0x40::Clear();
}

// STUB: GOLDP 0x10004570
void GolFont0xa0::VTable0x00(undefined4, undefined4)
{
	// TODO
	STUB(0x10004570);
}

// FUNCTION: GOLDP 0x100046e0
void GolFont0xa0::ReleaseSurfaces()
{
	if (m_unk0x9c != NULL) {
		delete[] m_unk0x9c;
		m_unk0x9c = NULL;
	}

	if (m_unk0x90 != NULL) {
		delete[] m_unk0x90;
		m_unk0x90 = NULL;
	}
}

// STUB: GOLDP 0x10004720
void GolFont0xa0::RefreshSurfaces(BronzeFalcon0xc8770*)
{
	// TODO
	STUB(0x10004720);
}

// STUB: GOLDP 0x100047b0
void GolFont0xa0::VTable0x04(undefined4)
{
	// TODO
	STUB(0x100047b0);
}

// FUNCTION: GOLDP 0x10004b60
PurpleDune0x7c* GolFont0xa0::VTable0x08(LegoU32 p_index)
{
	return &m_unk0x90[p_index];
}

// FUNCTION: GOLDP 0x10004b80
void GolFont0xa0::VTable0x0c(WhiteFalcon0x140* p_renderer, undefined4)
{
	m_renderer = static_cast<BronzeFalcon0xc8770*>(p_renderer);
}

// FUNCTION: GOLDP 0x10004b90
void GolFont0xa0::VTable0x10(LegoU32 p_index)
{
	LegoU32 index = p_index;
	DuskwindBananaRelic0x30* material = &m_unk0x9c[index];
	(m_renderer->*m_renderer->m_unk0xc876c)(material);

	GoldDune0x38* texture = &m_unk0x90[index];
	m_renderer->FUN_1000ac00(texture);
	m_unk0x94 = 1.0f / static_cast<LegoFloat>(m_unk0x90[index].GetWidth());
	m_unk0x98 = 1.0f / static_cast<LegoFloat>(m_unk0x90[index].GetHeight());
}

// STUB: GOLDP 0x10004c20
void GolFont0xa0::VTable0x14(Rect* p_sourceRect, Rect* p_destRect)
{
	D3DTLVERTEX vertices[4];

	vertices[0].sx = static_cast<LegoFloat>(p_destRect->m_left);
	vertices[0].sy = static_cast<LegoFloat>(p_destRect->m_top);
	vertices[0].sz = 0.0f;
	vertices[0].rhw = 1.0f;

	vertices[1].sx = static_cast<LegoFloat>(p_destRect->m_left);
	vertices[1].sy = static_cast<LegoFloat>(p_destRect->m_bottom);
	vertices[1].sz = 0.0f;
	vertices[1].rhw = 1.0f;

	vertices[2].sx = static_cast<LegoFloat>(p_destRect->m_right);
	vertices[2].sy = static_cast<LegoFloat>(p_destRect->m_top);
	vertices[2].sz = 0.0f;
	vertices[2].rhw = 1.0f;

	vertices[3].sx = static_cast<LegoFloat>(p_destRect->m_right);
	vertices[3].sy = static_cast<LegoFloat>(p_destRect->m_bottom);
	vertices[3].sz = 0.0f;
	vertices[3].rhw = 1.0f;

	vertices[0].tu = static_cast<LegoFloat>(p_sourceRect->m_left) * m_unk0x94 + (m_unk0x94 * 0.25f);
	vertices[0].tv = static_cast<LegoFloat>(p_sourceRect->m_top) * m_unk0x98;
	vertices[1].tu = vertices[0].tu;
	vertices[1].tv = static_cast<LegoFloat>(p_sourceRect->m_bottom - 1) * m_unk0x98;
	vertices[2].tu = static_cast<LegoFloat>(p_sourceRect->m_right) * m_unk0x94 + (m_unk0x94 * 0.25f);
	vertices[2].tv = vertices[0].tv;
	vertices[3].tu = vertices[2].tu;
	vertices[3].tv = vertices[1].tv;

	LegoU32 color =
		(m_color.m_alp << 24) | (m_color.m_red << 16) | (m_color.m_grn << 8) | static_cast<LegoU32>(m_color.m_blu);
	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;

	vertices[0].specular = 0xffffffff;
	vertices[1].specular = 0xffffffff;
	vertices[2].specular = 0xffffffff;
	vertices[3].specular = 0xffffffff;

	LegoU32 vertexCount = sizeOfArray(vertices);
	m_renderer->FUN_10009fd0(vertices, vertexCount);
}

// FUNCTION: GOLDP 0x10029920 FOLDED
void GolFont0xa0::VTable0x18()
{
	// empty
}
