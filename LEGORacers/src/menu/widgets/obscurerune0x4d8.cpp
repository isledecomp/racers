#include "menu/widgets/obscurerune0x4d8.h"

#include <string.h>

DECOMP_SIZE_ASSERT(ObscureRune0x4d8, 0x4d8)
DECOMP_SIZE_ASSERT(ObscureRune0x4d8::CreateParams0x88, 0x88)

// FUNCTION: LEGORACERS 0x004660a0
ObscureRune0x4d8::ObscureRune0x4d8()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00466120
ObscureRune0x4d8::~ObscureRune0x4d8()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00466180
LegoBool32 ObscureRune0x4d8::FUN_00466180(CreateParams0x88* p_createParams)
{
	ObscureTome0x3fc::CreateParams0x60 createParams;
	::memset(&createParams, 0, sizeof(createParams));
	::memcpy(&createParams, p_createParams->m_unk0x84, sizeof(createParams));

	createParams.m_rect = p_createParams->m_rect;
	createParams.m_parent = p_createParams->m_parent;

	return m_unk0xdc.FUN_0046ecd0(&createParams);
}

// FUNCTION: LEGORACERS 0x004661f0
LegoBool32 ObscureRune0x4d8::FUN_004661f0(CreateParams0x88* p_createParams, undefined4 p_unk0x08)
{
	VTable0x08();

	if (FUN_00466180(p_createParams)) {
		p_createParams->m_rect.m_left = 0;
		p_createParams->m_rect.m_top = 0;
		p_createParams->m_rect.m_right =
			m_unk0xdc.GetUnk0x58()->GetRect()->m_right - m_unk0xdc.GetUnk0x58()->GetRect()->m_left;
		p_createParams->m_rect.m_bottom =
			m_unk0xdc.GetUnk0x58()->GetRect()->m_bottom - m_unk0xdc.GetUnk0x58()->GetRect()->m_top;
		p_createParams->m_parent = m_unk0xdc.GetUnk0x58();

		return ObscureSigil0xdc::FUN_00465820(p_createParams, p_unk0x08);
	}

	return FALSE;
}
