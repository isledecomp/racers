#include "menu/widgets/obscureglyph0x21c.h"

#include "image/utopianpan0xa4.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ObscureGlyph0x21c, 0x21c)
DECOMP_SIZE_ASSERT(ObscureGlyph0x21c::CreateParams0x9c, 0x9c)

// FUNCTION: LEGORACERS 0x00466260
ObscureGlyph0x21c::ObscureGlyph0x21c()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x004662e0
ObscureGlyph0x21c::~ObscureGlyph0x21c()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00466340
void ObscureGlyph0x21c::Reset()
{
	::memset(m_unk0x1a8, 0, sizeof(m_unk0x1a8));

	m_unk0x1c0.VTable0x08();
	ObscureIcon0x1a8::Reset();
}

// FUNCTION: LEGORACERS 0x00466370
LegoBool32 ObscureGlyph0x21c::FUN_00466370(ObscureAnchor0x5c* p_unk0x04, CreateParams0x9c* p_createParams)
{
	ObscureAnchor0x5c::CreateParams0x3c createParams;
	::memset(&createParams, 0, sizeof(createParams));

	UtopianPan0xa4* image = p_createParams->m_images[0];
	::memcpy(&createParams, p_createParams, sizeof(ObscureVantage0x58::CreateParams0x38));
	createParams.m_unk0x20 = m_unk0x30;
	createParams.m_unk0x22 = m_unk0x174[0];
	createParams.m_parent = this;
	createParams.m_unk0x38 = image;

	return p_unk0x04->FUN_0046f150(&createParams);
}

// FUNCTION: LEGORACERS 0x004663d0
LegoBool32 ObscureGlyph0x21c::FUN_004663d0(
	CreateParams0x9c* p_createParams,
	const ObscureIcon0x1a8::CreateState0x90* p_createState
)
{
	VTable0x08();

	::memcpy(m_unk0x1a8, p_createParams->m_images, sizeof(m_unk0x1a8));

	if (!p_createParams->m_rect.m_right) {
		p_createParams->m_rect.m_right = p_createParams->m_rect.m_left + m_unk0x1a8[0]->GetWidth();
	}

	if (!p_createParams->m_rect.m_bottom) {
		p_createParams->m_rect.m_bottom = p_createParams->m_rect.m_top + m_unk0x1a8[0]->GetHeight();
	}

	if (FUN_00471e30(p_createParams, p_createState)) {
		return FUN_00466370(&m_unk0x1c0, p_createParams);
	}

	return FALSE;
}

// FUNCTION: LEGORACERS 0x00466450
LegoBool32 ObscureGlyph0x21c::VTable0x08()
{
	LegoBool32 result = TRUE;

	if (m_flags & 1) {
		return ObscureIcon0x1a8::VTable0x08();
	}

	return result;
}

// FUNCTION: LEGORACERS 0x00466470
ObscureVantage0x58* ObscureGlyph0x21c::VTable0x38(Rect*, Rect*)
{
	Rect rect;
	rect.m_top = 0;
	rect.m_left = 0;
	rect.m_right = m_unk0x34.m_right - m_unk0x34.m_left;
	rect.m_bottom = m_unk0x34.m_bottom - m_unk0x34.m_top;

	m_unk0x1c0.VTable0x10(&rect);
	m_unk0x1c0.SetUnk0x58(m_unk0x1a8[m_visualStateIndex]);
	m_unk0x1c0.VTable0x14(&m_unk0x174[m_visualStateIndex]);

	return NULL;
}
