#include "obscuretome0x3dc.h"

#include "utopianpan0xa4.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ObscureTome0x3fc, 0x3fc)
DECOMP_SIZE_ASSERT(ObscureTome0x3fc::CreateParams0x60, 0x60)
DECOMP_SIZE_ASSERT(ObscureTome0x3fc::CreateParamsPrefix0x38, 0x38)

// FUNCTION: LEGORACERS 0x0046ebb0
ObscureTome0x3fc::ObscureTome0x3fc()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x0046ec50
ObscureTome0x3fc::~ObscureTome0x3fc()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x0046ecd0
LegoBool32 ObscureTome0x3fc::FUN_0046ecd0(CreateParams0x60* p_createParams)
{
	VTable0x08();

	if (FUN_00472a60(p_createParams) && FUN_0046edf0(p_createParams) && FUN_0046ed30(p_createParams)) {
		if (!p_createParams->m_unk0x5c) {
			m_unk0x58.ClearFlags(0x10);
		}

		VTable0x10(&p_createParams->m_rect);
		return TRUE;
	}

	VTable0x08();
	return FALSE;
}

// STUB: LEGORACERS 0x0046ed30
LegoBool32 ObscureTome0x3fc::FUN_0046ed30(CreateParams0x60* p_createParams)
{
	ObscureAnchor0x5c::CreateParams0x3c createParams;
	::memset(&createParams, 0, sizeof(createParams));

	for (LegoS32 i = 0; i < 8; i++) {
		::memcpy(&createParams, p_createParams, 0x38);
		createParams.m_parent = this;
		createParams.m_flags |= 1;
		createParams.m_unk0x20 = 0x400;
		createParams.m_unk0x22 = p_createParams->m_unk0x22;
		createParams.m_unk0x38 = p_createParams->m_images[i];
		m_images[i] = createParams.m_unk0x38;

		if (!m_unk0xfc[i].FUN_0046f150(&createParams)) {
			return FALSE;
		}
	}

	return TRUE;
}

// STUB: LEGORACERS 0x0046edf0
LegoBool32 ObscureTome0x3fc::FUN_0046edf0(CreateParams0x60* p_createParams)
{
	CreateParamsPrefix0x38 createParams;
	::memcpy(&createParams, p_createParams, sizeof(createParams));
	createParams.m_unk0x20 = 0x29a;
	createParams.m_parent = this;
	createParams.m_flags |= 1;
	createParams.m_unk0x22 = p_createParams->m_unk0x58;

	return m_unk0x58.FUN_004735a0(&createParams);
}

// STUB: LEGORACERS 0x0046ee40
void ObscureTome0x3fc::VTable0x10(Rect* p_rect)
{
	ObscureVantage0x58::VTable0x10(p_rect);

	if (m_flags & 1) {
		LegoS32 width = m_unk0x34.m_right - m_unk0x34.m_left;
		LegoS32 height = m_unk0x34.m_bottom - m_unk0x34.m_top;

		Rect rect;
		rect.m_left = 0;
		rect.m_top = 0;
		rect.m_right = m_images[0]->GetWidth();
		rect.m_bottom = m_images[0]->GetHeight();
		m_unk0xfc[0].VTable0x10(&rect);

		rect.m_left = m_images[0]->GetWidth();
		rect.m_top = 0;
		rect.m_right = width - m_images[2]->GetWidth();
		rect.m_bottom = m_images[1]->GetHeight();
		m_unk0xfc[1].VTable0x10(&rect);

		rect.m_left = width - m_images[2]->GetWidth();
		rect.m_top = 0;
		rect.m_right = width;
		rect.m_bottom = m_images[1]->GetHeight();
		m_unk0xfc[2].VTable0x10(&rect);

		rect.m_left = width - m_images[3]->GetWidth();
		rect.m_top = m_images[0]->GetHeight();
		rect.m_right = width;
		rect.m_bottom = height - m_images[4]->GetHeight();
		m_unk0xfc[3].VTable0x10(&rect);

		rect.m_left = width - m_images[4]->GetWidth();
		rect.m_top = height - m_images[4]->GetHeight();
		rect.m_right = width;
		rect.m_bottom = height;
		m_unk0xfc[4].VTable0x10(&rect);

		rect.m_left = m_images[6]->GetWidth();
		rect.m_top = height - m_images[5]->GetHeight();
		rect.m_right = width - m_images[4]->GetWidth();
		rect.m_bottom = height;
		m_unk0xfc[5].VTable0x10(&rect);

		rect.m_left = 0;
		rect.m_top = height - m_images[6]->GetHeight();
		rect.m_right = m_images[6]->GetWidth();
		rect.m_bottom = height;
		m_unk0xfc[6].VTable0x10(&rect);

		rect.m_left = 0;
		rect.m_top = m_unk0xfc[0].GetRect()->m_bottom;
		rect.m_right = m_images[7]->GetWidth();
		rect.m_bottom = m_unk0xfc[6].GetRect()->m_top;
		m_unk0xfc[7].VTable0x10(&rect);

		rect.m_left = m_unk0xfc[0].GetRect()->m_right;
		rect.m_top = m_unk0xfc[0].GetRect()->m_bottom;
		rect.m_right = m_unk0xfc[2].GetRect()->m_left;
		rect.m_bottom = m_unk0xfc[6].GetRect()->m_top;
		m_unk0x58.VTable0x10(&rect);
	}

	STUB(0x0046ee40);
}

// FUNCTION: LEGORACERS 0x0046f050
void ObscureTome0x3fc::FUN_0046f050(VisualState0x4* p_visualState)
{
	for (LegoS32 i = 0; i < 8; i++) {
		m_unk0xfc[i].VTable0x14(p_visualState);
	}
}
