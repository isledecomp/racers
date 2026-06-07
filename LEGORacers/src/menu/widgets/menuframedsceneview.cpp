#include "menu/widgets/menuframedsceneview.h"

#include <string.h>

DECOMP_SIZE_ASSERT(MenuFramedSceneView, 0x4d8)
DECOMP_SIZE_ASSERT(MenuFramedSceneView::CreateParams, 0x88)

// FUNCTION: LEGORACERS 0x004660a0
MenuFramedSceneView::MenuFramedSceneView()
{
	Reset();
}

// FUNCTION: LEGORACERS 0x00466120
MenuFramedSceneView::~MenuFramedSceneView()
{
	VTable0x08();
}

// FUNCTION: LEGORACERS 0x00466180
LegoBool32 MenuFramedSceneView::FUN_00466180(CreateParams* p_createParams)
{
	MenuFrame::CreateParams createParams;
	::memset(&createParams, 0, sizeof(createParams));
	::memcpy(&createParams, p_createParams->m_unk0x84, sizeof(createParams));

	createParams.m_rect = p_createParams->m_rect;
	createParams.m_parent = p_createParams->m_parent;

	return m_unk0xdc.FUN_0046ecd0(&createParams);
}

// FUNCTION: LEGORACERS 0x004661f0
LegoBool32 MenuFramedSceneView::FUN_004661f0(CreateParams* p_createParams, undefined4 p_unk0x08)
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

		return MenuSceneView::FUN_00465820(p_createParams, p_unk0x08);
	}

	return FALSE;
}
